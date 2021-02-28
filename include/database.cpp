#include "database.h"

///=============================================================================
ResultParseCmd* Database::parseCmd(char *cmd)
{
    int len_cmd = strlen(cmd), offset = 0;
    
    ResultParseCmd* result = new ResultParseCmd();
    
    char *cmd0 = NULL;
    
    printf("cmd [%d]: %s\n", len_cmd, cmd);
    
    if( len_cmd == 0 )
    { 
        result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT;
        return result;
    }
    
    //offset = skipSpace(cmd, len_cmd, offset);
    
    cmd0 = _getWordStopSpace(cmd, len_cmd, offset, &offset );
    
    printf("offset now: %d '%c'\n", offset, cmd[offset]);
    printf(">> '%s'\n", cmd0);
    
    if( icasecmp(cmd0, "CREATE_DATABASE") )
    {
        char *path = NULL, *table_name = NULL, *table_info = NULL;
        vector<string> table_info_items, colums_info;
        
        vector<TableInto*> list_tables;
        
        path = _getStringQuoted(cmd, len_cmd, offset, &offset );
        
        string fullPath = string_format("%stables/%s", pathToDateDir.c_str(), path);

        //printf("offset now: %d '%c'\n", offset, cmd[offset]);
        //printf(">> '%s'\n", path_to_save);
        
        while(offset < len_cmd - 1)
        {
            TableInto* new_table = new TableInto();
            
            table_name = _getWordStopSpace(cmd, len_cmd, offset, &offset );
            
            new_table->table_name = table_name;

            //printf("offset now: %d '%c'\n", offset, cmd[offset]);
            //printf(">> '%s'\n", table_name);

            table_info = _getStringCurlyBrackets(cmd, len_cmd, offset, &offset);

            //printf("offset now: %d '%c'\n", offset, cmd[offset]);
            //printf(">> '%s'\n", table_info);

            table_info_items = string_split(table_info, ';');

            printf("table_info_items count: %ld\n", table_info_items.size());

            for (int i = 0; i < table_info_items.size(); i++)
            {
                printf("[%d]-> '%s'\n", i, table_info_items[i].c_str() );
                
                colums_info = string_split(table_info_items[i], '-');
                
                if(colums_info.size() < 2)
                {
                    result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE;
                    break;
                }
                
                //printf(" name->> '%s'\n", colums_info[0] );
                //printf(" type->> '%s'\n", colums_info[1] );
                
                if( strlen( colums_info[ 0 ].c_str() ) == 0 )
                {
                    result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE_COLUMN;
                    break;
                }
                else if( isdigit( colums_info[ 0 ][0] ) ) /// нельзя ничинать название колонки с числа
                {
                    result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE_COLUMN;
                    break;
                }
                else if( colums_info[ 1 ].length() == 0 ) // не задан тип колонки
                {
                    result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TYPE_COLUMN;
                    break;
                }
                else if( validate_type_column( colums_info[ 1 ].c_str() ) == 0 )
                {
                    result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TYPE_COLUMN;
                    break;
                }
                
                InfoColum* ic = new InfoColum();
                ic->name      = colums_info[0];
                ic->index     = i;
                
                _setTypeInfo(ic, colums_info[ 1 ].c_str());
                
                if( colums_info.size() >= 3 )
                {
                    if( icasecmp( colums_info[2], "null") )
                    {
                        ic->mayBeNull = true;
                    }
                }
                
                new_table->columns.push_back( ic );
                
                if( result->value != PARSE_QUERY_OK ) // значит ошибка парсинга
                {
                    printf("line: %d, error parsing: %d \n", __LINE__, result->value);
                    break;
                }
            }

            _cleanup( &table_info );
            _cleanup( &table_name );
            
            if( result->value != PARSE_QUERY_OK )
            {
                break;
            }
            
            list_tables.push_back(new_table);
        }
        
        for(int i=0; i < list_tables.size(); ++i)
        {
            list_tables[i]->debug_print();
        }
        
        if( file_exists(fullPath.c_str()) )
        {
            result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FILE_EXIST;
        }
        else
        {
            bool result_create_base = AHTables::newTables( fullPath.c_str(), list_tables );
        
            printf("result_create_base: %d\n", result_create_base ? 1 : 0);
        }
        
        _cleanup( &path );
    }
    else if( icasecmp(cmd0, "OPEN_DATABASE") )
    {
        char *path = NULL;
        
        path = _getStringQuoted(cmd, len_cmd, offset, &offset );
        
        string fullPath = string_format("%stables/%s", pathToDateDir.c_str(), path);
        
        if( file_exists(fullPath.c_str()) )
        {
            printf("OPEN_DATABASE: %s\n", fullPath.c_str());
            
            AHTables *ah_tables = new AHTables( fullPath.c_str() );
            
            if(ah_tables->getStatus() != AHT_OK)
            {
                delete ah_tables;
            }
            else
            {
                isOpened = true;
            }
            
            listTables.push_back( ah_tables );
        }
        
        free(path);
    }
    else if( icasecmp(cmd0, "CLOSE_DATABASE") )
    {
        if( isOpened )
        {
            close();
        }
    }
    else if( icasecmp(cmd0, "INFO_DATABASE") )
    {
        for(int i = 0; i < listTables.size(); i++)
        {
            for(int i = 0; i < listTables.size(); i++)
            {
                listTables[i]->debug_print_struct_allTable();
            }
        }
    }
    else if( icasecmp(cmd0, "DELETE") )
    {
            SplitByWordList* _list = splitByWordList(cmd, vector<string>{"DELETE", "WHERE", "OFFSET", "LIMIT"});
            debug_print_sub_string_list(_list->result);

            if(    
                       ! _list->isTokenExist("DELETE") 
                    || ! _list->isToken("DELETE", 0)
              )
            {
                result->value = PARSE_QUERY_ERROR_SELECT;
                return result;
            }

            if( _list->isTokenExist("WHERE") && ! _list->isToken("WHERE", 1) )
            {
                result->value = PARSE_QUERY_ERROR_SELECT;
                return result;
            }

            vector<string> list_tables;
            string where = "", _offset = "", _limit = "";

            SubStringInfo* _t = _list->getByToken("DELETE");

            if( _t != NULL )
            {
                list_tables = _splitParametersByChar((char*) _t->value.c_str(), strlen(_t->value.c_str()));

                /*printf("[%d] list_tables = %ld\n", __LINE__, list_tables.size() );

                for(int f = 0; f < list_tables.size(); f++)
                {
                    printf("list_tables[%d] %s\n", f, list_tables[f].c_str() );
                }*/
            }

            _t = _list->getByToken("WHERE");

            if( _t != NULL )
            {
                where = trim(_t->value);
            }

            _t = _list->getByToken("OFFSET");

            if( _t != NULL )
            {
                _offset = _t->value;
            }

            _t = _list->getByToken("LIMIT");

            if( _t != NULL )
            {
                _limit = _t->value;
            }
            
            if(list_tables.size() != 1)
            {
                result->value = PARSE_QUERY_ERROR_UPDATE_COUNT_TABLES;
                return result;
            }
            
            DeleteQueryInfo* dqi = new DeleteQueryInfo();
            //dqi->_table    = this;
            dqi->where     = where;
            dqi->haveWhere = where.length() > 0;
            
            for(int k = 0; k < list_tables.size(); k++)
            {
                string table_name = trim(list_tables[k]);
                
                //printf("table_name: %s\n", table_name.c_str());
                
                if( ! getTableIntoByName(table_name, &dqi->_table, &dqi->table) )
                /*{
                    //printf("add tables in list\n");
                    
                    dqi->table = getTableByName( table_name );
                    break;
                }
                else*/
                {
                    result->value = PARSE_QUERY_ERROR_TABLE_NOT_EXIST;
                    delete dqi;
                    return result;
                }
            }
            
            if( _offset.length() > 0 )
            {
                dqi->offset   = atoll(_offset.c_str());
            }

            if( _limit.length() > 0 )
            {
                dqi->limit    = atoll(_limit.c_str());
            }

            if( where.length() > 0 )
            {
                vector<string> vv = getListWords(where);

                /*printf("[%d] vv = %ld --> ", __LINE__, vv.size() );

                for(int f = 0; f < vv.size(); f++)
                {
                    printf("%s\n", vv[f].c_str() );
                }*/

                int res = dqi->addWhereNewColumn(vv);

                if(res != 0)
                {
                    result->value = res;
                }
            }
            
            if(result->value == PARSE_QUERY_OK)
            {
                dqi->setMaskReadWhereColumns();

                /*printf("\n");
                printf("[%d] mask_read_columns = %ld --> ", __LINE__, dqi->mask_read_columns.size() );

                for(int f = 0; f < dqi->mask_read_columns.size(); f++)
                {
                    printf("%d ", dqi->mask_read_columns[f] );
                }

                printf("\n");*/

                GlobalScope vars;
                dqi->exec(result, vars);
            }
        
    }
    else if( icasecmp(cmd0, "UPDATE") )
    {
        
            SplitByWordList* _list = splitByWordList(cmd, vector<string>{"UPDATE", "SET", "WHERE", "OFFSET", "LIMIT"});
            debug_print_sub_string_list(_list->result);
            
            if(    
                   ! _list->isTokenExist("UPDATE") 
                || ! _list->isToken("UPDATE", 0) 
                || ! _list->isTokenExist("SET") 
                || ! _list->isToken("SET", 1) )
            {
                result->value = PARSE_QUERY_ERROR_SELECT;
                return result;
            }
            
            if( _list->isTokenExist("WHERE") && ! _list->isToken("WHERE", 2) )
            {
                result->value = PARSE_QUERY_ERROR_SELECT;
                return result;
            }
            
            vector<string> list_set, list_tables;
            string where = "", _offset = "", _limit = "";
            
            SubStringInfo* _t = _list->getByToken("UPDATE");

            if( _t != NULL )
            {
                list_tables = _splitParametersByChar((char*) _t->value.c_str(), strlen(_t->value.c_str()));

                /*printf("[%d] list_tables = %ld\n", __LINE__, list_tables.size() );

                for(int f = 0; f < list_tables.size(); f++)
                {
                    printf("list_tables[%d] %s\n", f, list_tables[f].c_str() );
                }*/
            }
            
            _t = _list->getByToken("SET");

            if( _t != NULL )
            {
                list_set = _splitParametersByChar((char*) _t->value.c_str(), strlen(_t->value.c_str()));

                printf("[%d] list_set=%ld\n", __LINE__, list_set.size() );

                for(int f = 0; f < list_set.size(); f++)
                {
                    printf("[%d] %s\n", f, list_set[f].c_str() );
                }
            }
            
            _t = _list->getByToken("WHERE");

            if( _t != NULL )
            {
                where = trim( _t->value );
            }
            
            _t = _list->getByToken("OFFSET");

            if( _t != NULL )
            {
                _offset = _t->value;
            }
            
            _t = _list->getByToken("LIMIT");

            if( _t != NULL )
            {
                _limit = _t->value;
            }
            
            
            if(list_tables.size() != 1)
            {
                result->value = PARSE_QUERY_ERROR_UPDATE_COUNT_TABLES;
                return result;
            }
            
            if(list_set.size() == 0)
            {
                result->value = PARSE_QUERY_ERROR_UPDATE_SET_PARAMETERS;
                return result;
            }
            
            //std::regex _pattern("(\\.+)=(\\.+)");
            std::smatch matches;

            UpdateQueryInfo* uqi = new UpdateQueryInfo();
            //uqi->db        = this;
            uqi->where     = where;
            uqi->haveWhere = where.length() > 0;
            
            //printf("where: %s\n", where.c_str());
            
            for(int k = 0; k < list_tables.size(); k++)
            {
                string table_name = trim(list_tables[k]);
                
                printf("table_name: %s\n", table_name.c_str());
                
                if( ! getTableIntoByName( table_name, &uqi->db, &uqi->table ) )
                /*{
                    //printf("add tables in list\n");
                    
                    uqi->table = getTableByName( table_name );
                    break;
                }*/
                //else
                {
                    result->value = PARSE_QUERY_ERROR_TABLE_NOT_EXIST;
                    delete uqi;
                    return result;
                }
            }
            
            for(int i = 0; i < list_set.size(); i++)
            {
                string name_column = trim(list_set[i]);
                string value;
                //bool regex_r = std::regex_search(name_column, matches, _pattern);
                vector<string> list_set = _splitParametersByChar((char*)name_column.c_str(), name_column.length(), '=');
                
                printf("regex_search: %s %d\n", name_column.c_str(), list_set.size());
                
                if(list_set.size() == 2) 
                {
                    name_column = list_set[0];
                    value       = list_set[1];
                    
                    name_column = trim(name_column);
                    value       = trim(value);
                    
                    printf("list_set[%d]: %s = '%s'\n", i, name_column.c_str(), value.c_str() );
                    
                    InfoColum* c = uqi->table->getColumnInByName(name_column);
                    
                    if( c == NULL )
                    {
                        result->value = PARSE_QUERY_ERROR_COLUMN_NOT_EXIST;
                        delete uqi;
                        return result;
                    }
                    
                    if( c->mayBeNull || c->type == TYPE_COLUMN_STR || c->type == TYPE_COLUMN_BUFF )
                    {
                        uqi->set_columns_is_fix = false;
                    }
                    
                    uqi->set_columns[ name_column ] = c;
                    uqi->set_values[ name_column ]  = value;
                    
                    vector<string> vv = getListWords(value);
                    
                    printf("set_columns .. %s [%s] %s\n", name_column.c_str(), uqi->set_columns[ name_column ]->name.c_str(), value.c_str());
                    
                    printf("[%d] set_values vv = %ld --> ", __LINE__, vv.size() );

                    for(int f = 0; f < vv.size(); f++)
                    {
                        printf("%s\n", vv[f].c_str() );
                    }

                    int res = uqi->addWhereNewColumn(vv);

                    if(res != 0)
                    {
                        result->value = res;
                        break;
                    }
                    
                    /*try
                    {
                        uqi->set_velues[ name_column ]  = calculator::calculate(value.c_str());
                    }
                    catch (const std::exception& e) 
                    {
                        result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                        result->str_value  = e.what();
                        return result;
                    } 
                    catch (const char* c) 
                    {
                        result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                        result->str_value  = c;
                        return result;
                    }*/
                    
                }
                else
                {
                    result->value = PARSE_QUERY_ERROR_UPDATE_FORMAT_SET;
                    delete uqi;
                    return result;
                }
            }
            
            if( result->value == PARSE_QUERY_OK )
            {
                if( _offset.length() > 0 )
                {
                    uqi->offset   = atoll(_offset.c_str());
                }
                
                if( _limit.length() > 0 )
                {
                    uqi->limit    = atoll(_limit.c_str());
                }
                
                if( where.length() > 0 )
                {
                    vector<string> vv = getListWords(where);
                    
                    /*printf("[%d] vv = %ld --> ", __LINE__, vv.size() );

                    for(int f = 0; f < vv.size(); f++)
                    {
                        printf("%s\n", vv[f].c_str() );
                    }*/

                    int res = uqi->addWhereNewColumn(vv);

                    if(res != 0)
                    {
                        result->value = res;
                    }
                }
                
                if( result->value == PARSE_QUERY_OK )
                {
                    uqi->setMaskUpdateColumns();
                    uqi->setMaskReadWhereColumns();

                    printf("[%d] uqi->set_columns_is_fix = %d\n", __LINE__, uqi->set_columns_is_fix ? 1 : 0 );

                    printf("[%d] mask_update_columns = %ld --> ", __LINE__, uqi->mask_update_columns.size() );

                    for(int f = 0; f < uqi->mask_update_columns.size(); f++)
                    {
                        printf("%d ", uqi->mask_update_columns[f] );
                    }

                    printf("\n");
                    printf("[%d] mask_read_columns = %ld --> ", __LINE__, uqi->mask_read_columns.size() );

                    for(int f = 0; f < uqi->mask_read_columns.size(); f++)
                    {
                        printf("%d ", uqi->mask_read_columns[f] );
                    }

                    printf("\n");

                    GlobalScope vars;
                    uqi->exec(result, vars);
                }
            }
            
            delete uqi;
    }
    else if( icasecmp(cmd0, "SELECT") )
    {
            SplitByWordList* _list = splitByWordList(cmd, vector<string>{"SELECT", "FROM", "WHERE", "OFFSET", "LIMIT", "ORDER"});
            debug_print_sub_string_list(_list->result);
            
            if(    
                   ! _list->isTokenExist("SELECT") 
                || ! _list->isToken("SELECT", 0) 
                || ! _list->isTokenExist("FROM") 
                || ! _list->isToken("FROM", 1) )
            {
                result->value = PARSE_QUERY_ERROR_SELECT;
                return result;
            }
            
            if( _list->isTokenExist("WHERE") && ! _list->isToken("WHERE", 2) )
            {
                result->value = PARSE_QUERY_ERROR_SELECT;
                return result;
            }
            
            vector<string> list_colums, list_tables, list_order;
            string where = "", _offset = "", _limit = "";

            SelectQueryInfo* sqi = new SelectQueryInfo();
            //sqi->db = this;
            
            SubStringInfo* _t = _list->getByToken("SELECT");

            if( _t != NULL )
            {
                list_colums = _splitParametersByChar((char*)_t->value.c_str(), strlen(_t->value.c_str()));

                /*printf("[%d] list_colums=%ld\n", __LINE__, list_colums.size() );

                for(int f = 0; f < list_colums.size(); f++)
                {
                    printf("[%d] %s\n", f, list_colums[f].c_str() );
                }*/
            }
            
            _t = _list->getByToken("FROM");

            if( _t != NULL )
            {
                list_tables = _splitParametersByChar((char*)_t->value.c_str(), strlen(_t->value.c_str()));

                /*printf("[%d] list_tables=%ld\n", __LINE__, list_tables.size() );

                for(int f = 0; f < list_tables.size(); f++)
                {
                    printf("[%d] %s\n", f, list_tables[f].c_str() );
                }*/
            }
            
            _t = _list->getByToken("WHERE");

            if( _t != NULL )
            {
                where = trim(_t->value);
            }
            
            _t = _list->getByToken("OFFSET");

            if( _t != NULL )
            {
                _offset = _t->value;
            }
            
            _t = _list->getByToken("LIMIT");

            if( _t != NULL )
            {
                _limit = _t->value;
            }
            
            _t = _list->getByToken("ORDER");

            if( _t != NULL )
            {
                list_order = _splitParametersByChar((char*)_t->value.c_str(), strlen(_t->value.c_str()));
            }
            
            for(int k = 0; k < list_tables.size(); k++)
            {
                string table_name = trim(list_tables[k]);
                
                AHTables* _db;
                TableInto* _t;
                
                if( getTableIntoByName( table_name, &_db, &_t ) != -1 )
                {
                    sqi->db_lidt.push_back( _db );
                    sqi->tables.push_back( _t );
                }
                else
                {
                    result->value = PARSE_QUERY_ERROR_TABLE_NOT_EXIST;
                    break;
                }
            }
            
            if( result->value == PARSE_QUERY_OK )
            {
                sqi->sortTableIndex();
                
                std::regex _pattern("(\\S+)\\s+as\\s+(\\S+)");
                std::regex _pattern2("(\\S+)\\s*\\.\\s*(\\S+)");
                std::smatch matches;
                
                if( list_colums.size() == 1 && list_colums[0] == "*" )
                {
                    for(int i = 0; i < sqi->tables.size(); i++)
                    {
                        for(int j = 0; j < sqi->tables[i]->columns.size(); j++)
                        {
                            InfoColum* c = sqi->tables[i]->columns[j];

                            if( sqi->alias_columns.find( c->name ) == sqi->alias_columns.end() )
                            {
                                sqi->alias_columns[ c->name ] = c;
                            }
                            else if( i > 0 ) // next table
                            {
                                result->value = PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT;
                                delete sqi;
                                return result;
                            }
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < list_colums.size(); i++)
                    {
                        string name_column = trim(list_colums[i]);
                        string as_name;

                        if(std::regex_search(name_column, matches, _pattern) && matches.size() == 3) 
                        {
                            name_column = matches[1];
                            as_name     = matches[2];
                            
                            name_column = trim(name_column);
                            as_name     = trim(as_name);
                        }
                        
                        if(std::regex_search(name_column, matches, _pattern2) && matches.size() == 3) 
                        {
                            string table_name = matches[1];
                            name_column       = matches[2];
                            
                            table_name    = trim(table_name);
                            name_column   = trim(name_column);
                            
                            //printf("\\\\\\ table name: '%s'.'%s'\n", table_name.c_str(), name_column.c_str());
                            
                            if( name_column == "*" )
                            {
                                if( sqi->existInListTables( table_name ) )
                                {
                                    for(int i = 0; i < sqi->tables.size(); i++)
                                    {
                                        if( icasecmp(sqi->tables[i]->table_name, table_name) )
                                        {
                                            for(int j = 0; j < sqi->tables[i]->columns.size(); j++)
                                            {
                                                if( ! sqi->addInAliasColumns( sqi->tables[i]->columns[j]->name, sqi->tables[i]->columns[j] ) )
                                                {
                                                    result->value = PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT;
                                                    result->str_value = string_format(
                                                                      "Error add column '%s' of table: %s"
                                                                    , sqi->tables[i]->columns[j]->name.c_str()
                                                                    , sqi->tables[i]->table_name.c_str()
                                                            );
                                                    delete sqi;
                                                    return result;
                                                }
                                            }
                                            
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    result->value = PARSE_QUERY_ERROR_TABLE_NOT_EXIST_IN_SELECT;
                                    result->str_value = string_format(
                                                                      "Table: %s, not exist in list"
                                                                    , table_name.c_str()
                                                            );
                                    delete sqi;
                                    return result;
                                }
                            }
                            else
                            {
                                InfoColum* tmp = sqi->getColumnInByTableName( table_name, name_column );

                                if( tmp == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_COLUMN_NOT_EXIST;
                                    result->str_value = string_format(
                                                                      "Column: %s, not fount in table: %s"
                                                                    , name_column.c_str()
                                                                    , table_name.c_str()
                                                            );
                                    break;
                                }
                                else
                                {
                                    if( as_name.length() > 0 )
                                    {
                                        if( ! sqi->addInAliasColumns(as_name, tmp) )
                                        {
                                            result->value = PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT;
                                            delete sqi;
                                            return result;
                                        }
                                    }
                                    else
                                    {
                                        if( ! sqi->addInAliasColumns(name_column, tmp) )
                                        {
                                            result->value = PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT;
                                            delete sqi;
                                            return result;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            int countColumnsInTables = sqi->getCountColumnInTables( name_column );

                            if( countColumnsInTables == 0 )
                            {
                                result->value = PARSE_QUERY_ERROR_COLUMN_NOT_EXIST;
                                break;
                            }
                            else if( countColumnsInTables > 1 )
                            {
                                result->value = PARSE_QUERY_ERROR_COLUMN_MOREE_THAN_TWO_TABLES;
                                break;
                            }

                            InfoColum* tmp = sqi->getColumnInTables( name_column );

                            if( tmp == NULL )
                            {
                                result->value = PARSE_QUERY_ERROR_COLUMN_NOT_EXIST;
                                break;
                            }
                            else
                            {
                                if( as_name.length() > 0 )
                                {
                                    if( ! sqi->addInAliasColumns(as_name, tmp) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT;
                                        delete sqi;
                                        return result;
                                    }
                                }
                                else
                                {
                                    if( ! sqi->addInAliasColumns(name_column, tmp) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT;
                                        delete sqi;
                                        return result;
                                    }
                                }
                            }
                        }

                    }
                }
                
                if( result->value == PARSE_QUERY_OK )
                {
                    if( where.length() > 0 )
                    {
                        vector<string> vv = getListWords(where);

                        int res = sqi->addWhereNewColumn(vv);

                        if(res != 0)
                        {
                            result->value = res;
                        }
                    }
                }
            }
            
            if( _offset.length() > 0 )
            {
                sqi->offset = atoll(_offset.c_str());
                
                if( sqi->offset < 0 )
                {
                    result->value      = PARSE_QUERY_ERROR_OFFSET_FORMAT;
                    result->str_value  = "Error offset value. Zero or > 0";
                    delete sqi;
                    return result;
                }
                else if( sqi->offset > 0 )
                {
                    sqi->haveOffset = true;
                }
            }

            if( _limit.length() > 0 )
            {
                sqi->limit = atoll(_limit.c_str());
                
                if( sqi->limit < 0 )
                {
                    result->value      = PARSE_QUERY_ERROR_LIMIT_FORMAT;
                    result->str_value  = "Error limit value. Zero or > 0";
                    delete sqi;
                    return result;
                }
                else if( sqi->limit > 0 )
                {
                    sqi->haveLimit = true;
                }
            }
            
            if( result->value == PARSE_QUERY_OK )
            {
                sqi->where_ex   = where;
                sqi->haveWhere  = where.length() > 0;
                
                if( list_order.size() > 0 && ! sqi->buildOrderList(result, list_order) )
                {
                    result->value = PARSE_QUERY_ERROR_ORDER_FORMAT;
                    delete sqi;
                    return result;
                }    
                
                /*printf("printColumnsInfo\n");
                sqi->printColumnsInfo();*/
                
                //printf("buildColumnsRead\n");
                sqi->buildColumnsRead();
                
                /*printf("where_columns\n");
                for (std::map<string, InfoColum*>::iterator it = sqi->where_columns.begin(); it != sqi->where_columns.end(); ++it)
                {
                    printf("%s %s\n", it->first.c_str(), it->second->name.c_str());
                }*/
                
                vector<struct PAGE_FRAGMENT*> list;
                int result_exec = SELECT_QUERY_INFO_OK;
                GlobalScope vars;
                
                ResultParseCmd* result2 = new ResultParseCmd();
                result2->value          = SELECT_QUERY_INFO_OK;
                
                sqi->exec( result2, vars, 0, list );
                
                if( 
                       sqi->haveOrder = true
                    && sqi->query_results != NULL 
                    && sqi->query_results->type == QueryResultType::TABLE
                    && sqi->query_results->rows.size() > 1
                    && sqi->haveOffset == false
                    && sqi->haveLimit  == false
                    && sqi->order.size() > 0
                  )
                {
                    printf("order run\n");
                    
                    // exec order columns
                    if( ! sqi->execOrderResultTable(result) )
                    {
                        printf("order error\n");
                        
                        delete sqi;
                        return result;
                    }
                }
                
                //printf("sqi->table_results->rows.size() = %d\n", sqi->table_results->rows.size() );
                
                sqi->printTableResult();
            }
            
            delete _list;
            delete sqi;
        
    }
    else if( icasecmp(cmd0, "INSERT") )
    {
        
            char *table_name = _getWordStopSpace(cmd, len_cmd, offset, &offset);
            
            AHTables* _db;
            TableInto* _t;

            if( ! getTableIntoByName(table_name, &_db, &_t))
            {
                //printf("PARSE_QUERY_ERROR_TABLE_NOT_FOUNT: '%s'\n", table_name);
                
                result->value = PARSE_QUERY_ERROR_TABLE_NOT_FOUNT;
                _cleanup( &table_name );

                return result;
            }

            //printf("[%d] INSERT: table_name '%s' %d index=%d\n", __LINE__, table_name, offset, index);

            char *f = _getStringCurlyBrackets2(cmd, len_cmd, offset, &offset);

            vector<string> list_p = _splitParametersByChar(f, strlen(f));

            //printf("[%d] |%s| %d %d\n", __LINE__, f, list_p.size(), current_db->tables[index]->getCountColums() );

            if( list_p.size() != _t->getCountColums() )
            {
                result->value = PARSE_QUERY_ERROR_TABLE_COUNT_COLUMS_PARAMETERS;
                _cleanup( &table_name );

                return result;
            }

            vector<packToken> _l;

            for(int ff = 0; ff < list_p.size(); ff++)
            {
                //printf("[%d] %s\n", ff, list_p[ff].c_str() );

                packToken tk;
                
                try
                {
                    tk = calculator::calculate(list_p[ff].c_str());
                }
                catch (const std::exception& e) 
                {
                    result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                    result->str_value  = e.what();
                    return result;
                } 
                catch (const char* c) 
                {
                    result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                    result->str_value  = c;
                    return result;
                }

                _l.push_back(tk);

                uint8_t type_colum = _t->getColumTypeByIndex(ff);

                _t->columns[ff]->debug_print();

                //printf("[%d] type: %d [%d] cparser: %s\n", __LINE__, tk.getType(), type_colum, tk.str().c_str());
            }

            _cleanup( &table_name );

            int error_value = 0;
            struct VoidArray *list_data = _buildListConvertTypes(_l, _t->columns, &error_value);

            _db->addNewPage(
                              AH_PAGE_STATUS_USED
                            , 0
                            , 0
                            , list_data
                            , _t->index ); // index table

            VoidArray_free(list_data);
        
    }
    else
    {
        result->value = PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT;
    }
    
    _cleanup( &cmd0 );
    
    return result;
}

///=============================================================================
struct VoidArray* Database::_buildListConvertTypes(vector<packToken> &list, vector<InfoColum*> columns_table, int *error)
{
    struct VoidArray *result = VoidArray_init();
    
    for(int i = 0, len = columns_table.size(); i < len; i++)
    {
        if( list[i].getType() == NONE )
        {
            VoidArray_addNULL(result);
            continue;
        }
        
        if( 
                columns_table[i]->type == TYPE_COLUMN_INT8
            ||  columns_table[i]->type == TYPE_COLUMN_UINT8
            ||  columns_table[i]->type == TYPE_COLUMN_INT16
            ||  columns_table[i]->type == TYPE_COLUMN_UINT16 
            ||  columns_table[i]->type == TYPE_COLUMN_INT32
            ||  columns_table[i]->type == TYPE_COLUMN_UINT32
            ||  columns_table[i]->type == TYPE_COLUMN_INT64
            ||  columns_table[i]->type == TYPE_COLUMN_UINT64
            ||  columns_table[i]->type == TYPE_COLUMN_INTPTR
            ||  columns_table[i]->type == TYPE_COLUMN_UINTPTR
          )
        {
            uint8_t type_parse = list[i].getType();
            
            if(    type_parse == tokType::INT 
                || type_parse == tokType::REAL
                || type_parse == tokType::BOOL
            )
            {
                switch(columns_table[i]->type)
                {
                    case TYPE_COLUMN_INT8:      VoidArray_addInt8(result, list[i].asInt()); break;
                    case TYPE_COLUMN_UINT8:     VoidArray_addUInt8(result, list[i].asInt()); break;
                    case TYPE_COLUMN_INT16:     VoidArray_addInt16(result, list[i].asInt()); break;
                    case TYPE_COLUMN_UINT16:    VoidArray_addUInt16(result, list[i].asInt()); break;
                    case TYPE_COLUMN_INT32:     VoidArray_addInt32(result, list[i].asInt()); break;
                    case TYPE_COLUMN_UINT32:    VoidArray_addUInt32(result, list[i].asInt()); break;
                    case TYPE_COLUMN_INT64:     VoidArray_addInt64(result, list[i].asInt()); break;
                    case TYPE_COLUMN_UINT64:    VoidArray_addUInt64(result, list[i].asInt()); break;
                    case TYPE_COLUMN_INTPTR:    VoidArray_addIntPtr(result, list[i].asInt()); break;
                    case TYPE_COLUMN_UINTPTR:   VoidArray_addUIntPtr(result, list[i].asInt()); break;
                }
            }
            else
            {
                *error = PARSE_QUERY_ERROR_COLUM_CONVERT_TYPES;
                break;
            }
        }
        else if( 
                columns_table[i]->type == TYPE_COLUMN_FLOAT
            ||  columns_table[i]->type == TYPE_COLUMN_DOUBLE
          )
        {
            uint8_t type_parse = list[i].getType();
            
            if(    type_parse == tokType::INT 
                || type_parse == tokType::REAL
                || type_parse == tokType::BOOL
            )
            {
                switch(columns_table[i]->type)
                {
                    case TYPE_COLUMN_FLOAT:     VoidArray_addFloat(result, list[i].asDouble()); break;
                    case TYPE_COLUMN_DOUBLE:    VoidArray_addDouble(result, list[i].asDouble()); break;
                }
            }
            else
            {
                *error = PARSE_QUERY_ERROR_COLUM_CONVERT_TYPES;
                break;
            }
        }
        else if( 
                columns_table[i]->type == TYPE_COLUMN_STR
            ||  columns_table[i]->type == TYPE_COLUMN_VCHAR
          )
        {
            switch(columns_table[i]->type)
            {
                case TYPE_COLUMN_STR:      VoidArray_addStr(result, (char *)list[i].asString().c_str()); break;
                case TYPE_COLUMN_VCHAR:    VoidArray_addVChar(result, (char *)list[i].asString().c_str(), columns_table[i]->prop_1); break;
            }
        }
        else 
        {
            *error = PARSE_QUERY_ERROR_COLUM_CONVERT_TYPES;
            break;
        }
    }
    
    return result;
}

///=============================================================================
int Database::validate_type_column(const char *v)
{
    //printf("v = [%d] '%s' '%c'\n", strlen(v), v, v[ strlen(v) ] );
    
    if( 
            strcasecmp(v, "INT8") == 0 
         || strcasecmp(v, "UINT8") == 0 
         || strcasecmp(v, "INT16") == 0 
         || strcasecmp(v, "UINT16") == 0 
         || strcasecmp(v, "INT32") == 0 
         || strcasecmp(v, "UINT32") == 0 
         || strcasecmp(v, "INT64") == 0 
         || strcasecmp(v, "UINT64") == 0 
         || strcasecmp(v, "FLOAT") == 0 
         || strcasecmp(v, "DOUBLE") == 0 
         || strcasecmp(v, "BUFF") == 0 
         || strcasecmp(v, "STR") == 0 
         || strncasecmp(v, "VCHAR", 5) == 0
    )
    { return 1; }
    
    return 0;
}
///=============================================================================
void Database::_setTypeInfo(InfoColum* ic, const char *v)
{
    if( strcasecmp(v, "INT8") == 0 )
    {
        ic->type = TYPE_COLUMN_INT8;
    }
    else if( strcasecmp(v, "UINT8") == 0 )
    {
        ic->type = TYPE_COLUMN_UINT8;
    }
    else if( strcasecmp(v, "INT16") == 0 )
    {
        ic->type = TYPE_COLUMN_INT16;
    }
    else if( strcasecmp(v, "UINT16") == 0 )
    {
        ic->type = TYPE_COLUMN_UINT16;
    }
    else if( strcasecmp(v, "INT32") == 0 )
    {
        ic->type = TYPE_COLUMN_INT32;
    }
    else if( strcasecmp(v, "UINT32") == 0 )
    {
        ic->type = TYPE_COLUMN_UINT32;
    }
    else if( strcasecmp(v, "INT64") == 0 )
    {
        ic->type = TYPE_COLUMN_INT64;
    }
    else if( strcasecmp(v, "UINT64") == 0 )
    {
        ic->type = TYPE_COLUMN_UINT64;
    }
    else if( strcasecmp(v, "FLOAT") == 0 )
    {
        ic->type = TYPE_COLUMN_FLOAT;
    }
    else if( strcasecmp(v, "DOUBLE") == 0 )
    {
        ic->type = TYPE_COLUMN_DOUBLE;
    }
    else if( strcasecmp(v, "BUFF") == 0 )
    {
        ic->type = TYPE_COLUMN_BUFF;
    }
    else if( strcasecmp(v, "STR") == 0 )
    {
        ic->type = TYPE_COLUMN_STR;
    }
    else if( strncasecmp(v, "VCHAR", 5) == 0 )
    {
        ic->type = TYPE_COLUMN_VCHAR;
        
        if( strlen( v ) == 5 )
        {
            ic->prop_1 = 255; // default VARCHAR
        }
        else
        {
            int   _len_str_parse_num = ( strlen( v ) - 5 ) + 1;
            char *_str_parse_num     = (char *) calloc( _len_str_parse_num, sizeof(char) );

            memcpy( _str_parse_num, v + 5, _len_str_parse_num );

            _str_parse_num[ _len_str_parse_num ] = '\0';

            ic->prop_1 = atol( _str_parse_num );

            free( _str_parse_num );
        }
    }
}
//==============================================================================
void Database::close() {

    if( ! isOpened) {
        return;
    }

    for(int i = 0; i < listTables.size(); i++)
    {
        delete listTables[i];
    }

    isOpened = false;
}
//==============================================================================
int Database::tableExists(string name)
{
    for(int i = 0; i < listTables.size(); i++)
    {
        if( listTables[i]->tableExists(name) != -1 )
        {
            return i;
        }
    }

    return -1;
}
//==============================================================================
bool Database::getTableIntoByName(string name, struct AHTables** v1, struct TableInto** v2)
{
    for(int i = 0; i < listTables.size(); i++)
    {
        TableInto* t = listTables[i]->getTableByName(name);
        
        if(t != NULL)
        {
            struct AHTables* f = listTables[i];
            
            *v1 = f;
            *v2 = t;
            return true;
        }
    }
    
    return false;
}