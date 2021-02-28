/* 
 * File:   database.h
 * Author: sk
 *
 * Created on February 1, 2021, 5:47 AM
 */

#ifndef DATABASE_H
#define DATABASE_H

#include "ah_api.h"

#define PARSE_QUERY_OK                                                 0x00
#define PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT                 0x01
#define PARSE_QUERY_ERROR                                              0x02
#define PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE           0x03
#define PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE_COLUMN    0x04
#define PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TYPE_COLUMN     0x05
#define PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FILE_EXIST             0x06
#define PARSE_QUERY_ERROR_TABLE_NOT_FOUNT                              0x07
#define PARSE_QUERY_ERROR_TABLE_COUNT_COLUMS_PARAMETERS                0x08
#define PARSE_QUERY_ERROR_COLUM_CONVERT_TYPES                          0x09
#define PARSE_QUERY_ERROR_SELECT                                       0x10
#define PARSE_QUERY_ERROR_DATABASE_NOT_OPENED                          0x11
#define PARSE_QUERY_ERROR_TABLE_NOT_EXIST                              0x12
#define PARSE_QUERY_ERROR_COLUMN_NOT_EXIST                             0x13
#define PARSE_QUERY_ERROR_COLUMN_IN_WHERE_ERROR_NAME                   0x14
#define PARSE_QUERY_ERROR_COLUMN_MOREE_THAN_TWO_TABLES                 0x15

#define SELECT_QUERY_INFO_OK                                           0x16
#define SELECT_QUERY_INFO_STOP                                         0x17
#define SELECT_QUERY_INFO_WHERE_FALSE                                  0x18
#define PARSE_QUERY_ERROR_UPDATE                                       0x19
#define PARSE_QUERY_ERROR_UPDATE_SET_PARAMETERS                        0x20
#define PARSE_QUERY_ERROR_UPDATE_COUNT_TABLES                          0x21
#define PARSE_QUERY_ERROR_UPDATE_FORMAT_SET                            0x22
#define PARSE_QUERY_ERROR_RUNTIME_IN_WHERE                             0x23
#define PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT                  0x24
#define PARSE_QUERY_ERROR_TABLE_NOT_EXIST_IN_SELECT                    0x25
#define PARSE_QUERY_ERROR_ORDER_FORMAT                                 0x26
#define PARSE_QUERY_ERROR_OFFSET_FORMAT                                0x27
#define PARSE_QUERY_ERROR_LIMIT_FORMAT                                 0x28
#define PARSE_QUERY_ERROR_ORDER                                        0x29


struct ResultParseCmd
{
    int value;
    string str_value;
    
    ResultParseCmd()
    {
        value = PARSE_QUERY_OK;
        str_value = "";
    }
    
    void debug_print()
    {
        switch(value)
        {
            case PARSE_QUERY_OK:
                printf("PARSE_QUERY_OK\n");
                break;

            case PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT:
                printf("PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT\n");
                break;

            case PARSE_QUERY_ERROR:
                printf("PARSE_QUERY_ERROR\n");
                break;

            case PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE:
                printf("PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE\n");
                break;

            case PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE_COLUMN:
                printf("PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TABLE_COLUMN\n");
                break;

            case PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TYPE_COLUMN:
                printf("PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FORMAT_TYPE_COLUMN\n");
                break;

            case PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FILE_EXIST:
                printf("PARSE_QUERY_ERROR_CREATE_DATABASE_ERROR_FILE_EXIST\n");
                break;

            case PARSE_QUERY_ERROR_TABLE_NOT_FOUNT:
                printf("PARSE_QUERY_ERROR_TABLE_NOT_FOUNT\n");
                break;

            case PARSE_QUERY_ERROR_TABLE_COUNT_COLUMS_PARAMETERS:
                printf("PARSE_QUERY_ERROR_TABLE_COUNT_COLUMS_PARAMETERS\n");
                break;

            case PARSE_QUERY_ERROR_COLUM_CONVERT_TYPES:
                printf("PARSE_QUERY_ERROR_COLUM_CONVERT_TYPES\n");
                break;

            case PARSE_QUERY_ERROR_SELECT:
                printf("PARSE_QUERY_ERROR_SELECT\n");
                break;

            case PARSE_QUERY_ERROR_DATABASE_NOT_OPENED:
                printf("PARSE_QUERY_ERROR_DATABASE_NOT_OPENED\n");
                break;

            case PARSE_QUERY_ERROR_TABLE_NOT_EXIST:
                printf("PARSE_QUERY_ERROR_TABLE_NOT_EXIST\n");
                break;

            case PARSE_QUERY_ERROR_COLUMN_NOT_EXIST:
                printf("PARSE_QUERY_ERROR_COLUMN_NOT_EXIST\n");
                break;

            case PARSE_QUERY_ERROR_COLUMN_IN_WHERE_ERROR_NAME:
                printf("PARSE_QUERY_ERROR_COLUMN_IN_WHERE_ERROR_NAME\n");
                break;

            case PARSE_QUERY_ERROR_COLUMN_MOREE_THAN_TWO_TABLES:
                printf("PARSE_QUERY_ERROR_COLUMN_MOREE_THAN_TWO_TABLES\n");
                break;

            case SELECT_QUERY_INFO_OK:
                printf("SELECT_QUERY_INFO_OK\n");
                break;

            case SELECT_QUERY_INFO_STOP:
                printf("SELECT_QUERY_INFO_STOP\n");
                break;

            case SELECT_QUERY_INFO_WHERE_FALSE:
                printf("SELECT_QUERY_INFO_WHERE_FALSE\n");
                break;
                
            case PARSE_QUERY_ERROR_UPDATE:
                printf("PARSE_QUERY_ERROR_UPDATE\n");
                break;
                
            case PARSE_QUERY_ERROR_UPDATE_SET_PARAMETERS:
                printf("PARSE_QUERY_ERROR_UPDATE_SET_PARAMETERS\n");
                break;
                
            case PARSE_QUERY_ERROR_UPDATE_COUNT_TABLES:
                printf("PARSE_QUERY_ERROR_UPDATE_COUNT_TABLES\n");
                break;
                
            case PARSE_QUERY_ERROR_UPDATE_FORMAT_SET:
                printf("PARSE_QUERY_ERROR_UPDATE_FORMAT_SET\n");
                break;
                
            case PARSE_QUERY_ERROR_RUNTIME_IN_WHERE:
                printf("PARSE_QUERY_ERROR_RUNTIME_IN_WHERE\n");
                break;
                
            case PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT:
                printf("PARSE_QUERY_ERROR_DIPLICATED_COLUMS_IN_SELECT\n");
                break;
                
            case PARSE_QUERY_ERROR_TABLE_NOT_EXIST_IN_SELECT:
                printf("PARSE_QUERY_ERROR_TABLE_NOT_EXIST_IN_SELECT\n");
                break;
                
            case PARSE_QUERY_ERROR_ORDER_FORMAT:
                printf("PARSE_QUERY_ERROR_ORDER_FORMAT\n");
                break;
                
            case PARSE_QUERY_ERROR_ORDER:
                printf("PARSE_QUERY_ERROR_ORDER\n");
                break;

        }
        
        printf("%s\n", str_value.c_str());
    }
};


class Database {
    
    private:
        
        string pathToDateDir;
        vector<struct AHTables*> listTables;
        struct VoidArray *_buildListConvertTypes(vector<packToken> &list, vector<InfoColum*> columns_table, int *error);
        
        int validate_type_column(const char *v);
        void _setTypeInfo(InfoColum* ic, const char *v);

        bool isOpened;
        
        void close();
        int tableExists(string name);
        
        bool getTableIntoByName(string name, struct AHTables** v1, struct TableInto** v2);
        
    public:

        ResultParseCmd* parseCmd(char *cmd);

        Database(string _pathToDateDir) 
        {
            isOpened      = false;
            pathToDateDir = _pathToDateDir;
        }

        ~Database()
        {
            close();
        }
    
};

//==============================================================================
struct SelectQueryInfoRunTime
{
    vector<uint8_t> mask_read_columns;
    vector<string> mask_read_columns_names;
    bool first_read;
    int row_index;
    
    struct PAGE_FRAGMENT *pf;
    vector<int> used_row;
    
    int findIndexInColumnsNames(string v)
    {
        for(int i = 0; i < mask_read_columns_names.size(); i++)
        {
            if( icasecmp(v, mask_read_columns_names[i]) )
            {
                return i;
            }
        }
        
        return -1;
    }
    
    SelectQueryInfoRunTime()
    {
        first_read = false;
        row_index = 0;
    }
    
    ~SelectQueryInfoRunTime()
    {
        printf("~SelectQueryInfoRunTime()\n");
        
        if(pf != NULL)
        {
            free_Page_Fragment( pf );
        }
    }
};

enum QueryResultType {
    TABLE,
    INTEGER,
    DOUBLE,
    STRING,
    NO
};

enum SelectQueryOrderType {
    ASC, DESC
};

enum SelectQueryInfoExecReturn {
    STOP, ERROR, NEXT
};

struct QueryResult
{
    int type;
    vector<struct VoidArray *> rows;
    
    QueryResult()
    {
        type = QueryResultType::NO;
    }
    
    ~QueryResult() {}
};

struct SelectQueryOrderInfoItem 
{
    InfoColum* c;
    int typeOrder;
    
    SelectQueryOrderInfoItem()
    {
        typeOrder = SelectQueryOrderType::ASC;
    }
};

struct SelectQueryInfo
{
    uint64_t offset, limit, _append_rows;
    
    vector<struct TableInto*> tables;
    vector<struct AHTables*>  db_lidt;
    vector<struct SelectQueryOrderInfoItem*>  order;
    
    map <string, InfoColum*> alias_columns;
    map <string, InfoColum*> where_columns;
    
    // table index, mask_read
    map <int, SelectQueryInfoRunTime*> runtime;
    
    string where_ex;
    QueryResult* query_results = NULL;
    
    bool haveWhere, haveOrder, haveOffset, haveLimit;
    
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    int exec(ResultParseCmd* result, GlobalScope &vars, int index_table, vector<struct PAGE_FRAGMENT*>& list_read_pages)
    {
        //printf("-> exec: index_table: %d %s\n", index_table, db_lidt[index_table]->getPath().c_str());
        
        if( runtime.find(index_table) != runtime.end() )
        {
            SelectQueryInfoRunTime* item = runtime[index_table];
            
            item->first_read = false;
            item->row_index  = 0;
            
            while(true)
            {
                item->row_index += 1;
                printf("--- count_iteration: %d %d %d\n", item->row_index, index_table, list_read_pages.size());
                
                /*for( int t = index_table; t < list_read_pages.size(); t++ )
                {
                    printf("free_Page_Fragment = t: %d\n", t);
                    free_Page_Fragment( list_read_pages[t] );
                }*/
                
                //list_read_pages.erase( list_read_pages.begin() + index_table, list_read_pages.end() );
                //printf("--- count_iteration: %d %d %d\n", item->row_index, index_table, list_read_pages.size());
                
                if( ! item->first_read )
                {
                    item->first_read = true;
                    
                    printf(">>  first_read %d %s %d\n", tables[index_table]->index, tables[index_table]->table_name.c_str(), item->mask_read_columns.size());
                    
                    item->pf = db_lidt[index_table]->findFirstPage(item->mask_read_columns, tables[index_table]->index);
                    
                    if( item->pf == NULL )
                    {
                        printf("[%d] item->pf == NULL\n", __LINE__);
                        
                        result->value = SELECT_QUERY_INFO_STOP;
                        break;
                    }
                    
                    //debug_print_struct_page_fragment(item->pf);
                }
                else
                {
                    printf(">>  next read %d\n", item->mask_read_columns.size());
                    
                    struct PAGE_FRAGMENT *pf_next = db_lidt[index_table]->findNextPage(item->pf, item->mask_read_columns, tables[index_table]->index);

                    if( pf_next == NULL )
                    {
                        printf("[%d] item->pf == NULL\n", __LINE__);
                        
                        break;
                    }

                    free_Page_Fragment( item->pf );
                    item->pf = pf_next;
                }
                
                if (std::find(item->used_row.begin(), item->used_row.end(), item->row_index) != item->used_row.end())
                {
                    continue;
                }
                
                list_read_pages.push_back(item->pf);
                
                
                if( where_columns.size() > 0 )
                {
                    //printf("where_ex: %s\n", where_ex.c_str());
                    
                    int list_index = 0;
                    
                    for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
                    {
                        if(    it->second->index_table == index_table
                            //&& it->second->index == runtime[ index_table ]->findIndexInColumnsNames( it->first )
                            && runtime[ index_table ]->mask_read_columns[ it->second->index ] == 1
                          )
                        {
                            //printf("+add/set var: %s %d\n", it->first.c_str(), list_index);
                            
                            setVar(vars, it->second->index, it->first, it->second, item);
                            list_index += 1;
                        }
                    }
                }
                
                //printf("[%d] c1 = %s\n", __LINE__, vars["c1"].str().c_str());
                
                bool r = exec(result, vars, index_table + 1, list_read_pages);
                
                printf("r = %d\n", r);
                
                if(      
                         r == SelectQueryInfoExecReturn::STOP 
                      || result->value != SELECT_QUERY_INFO_OK 
                  )
                {
                    printf("[%d] return\n", __LINE__);
                    return SelectQueryInfoExecReturn::STOP;
                }
                
                if( index_table != 0 || r == SelectQueryInfoExecReturn::NEXT )
                {
                    printf("[%d] return2 %d\n", __LINE__, index_table);
                    return SelectQueryInfoExecReturn::NEXT;
                }
            }
        }
        else
        {
            printf("END %d %d\n", __LINE__, haveWhere);
            
            if( haveWhere )
            {
                packToken result_exec_where;
                
                try 
                {
                    result_exec_where = calculator::calculate(where_ex.c_str(), vars);
                } 
                catch (const std::exception& e) 
                {
                    result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                    result->str_value  = e.what();
                    return true;
                } 
                catch (const char* c) 
                {
                    result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                    result->str_value  = c;
                    return true;
                }

                if( ! result_exec_where.asBool() )
                {
                    //printf("ok ok\n");
                    //*result = SELECT_QUERY_INFO_WHERE_FALSE;
                    return SelectQueryInfoExecReturn::NEXT;
                }
            }
            
            if(offset == 0 || _append_rows + 1 > offset)
            {
                //printf("list_read_pages.size: %d\n", list_read_pages.size());
            
                for (std::map<int, SelectQueryInfoRunTime*>::iterator it = runtime.begin(); it != runtime.end(); ++it)
                {
                    SelectQueryInfoRunTime* _t = it->second;

                    //printf("! add row_index: [%d] %d\n", it->first, _t->row_index);

                    _t->used_row.push_back( _t->row_index );
                }
                
                struct VoidArray *row = VoidArray_init();
                
                for(int k = 0; k < list_read_pages.size(); k++)
                {
                    //printf("k: %d\n", k);

                    if(    list_read_pages[k] != NULL
                        && list_read_pages[k]->data_list != NULL
                        && list_read_pages[k]->data_list->len > 0 )
                    {
                        VoidArray_append(row, list_read_pages[k]->data_list);
                    }
                }
                
                query_results->rows.push_back(row);
                //debug_void_array_print( row );
            }
            
            list_read_pages.clear();
            _append_rows += 1;
            
            if( limit > 0 && _append_rows > limit )
            {
                printf("--- %d\n", __LINE__);
                result->value = SELECT_QUERY_INFO_STOP;
            }
            
            return SelectQueryInfoExecReturn::NEXT;
        }
        
        return SelectQueryInfoExecReturn::STOP;
    }
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    bool execOrderResultTable(ResultParseCmd* result, int index = 0, int start_index = -1, int end_index = -1)
    {
        bool find_column = false;
        int column_index = 0;
        
        printf("order.size() = %d; query_results->rows.size() = %d\n", order.size(), query_results->rows.size());
        
        if( index >= 0 && index < order.size() )
        {
            SelectQueryOrderInfoItem *order_item = order[index];
            
            InfoColum* c = order_item->c;
            
            for (std::map<string, InfoColum*>::iterator it = alias_columns.begin(); it != alias_columns.end(); ++it)
            {
                printf("[%d] %s %s\n", column_index, it->second->name.c_str(), order_item->c->name.c_str());
                
                if( icasecmp(it->second->name, order_item->c->name) )
                {
                    for(int j = start_index != -1 ? start_index : 0
                          , len2 = end_index != -1 ? end_index : query_results->rows.size(); j < len2 - 1; j++ )
                    {
                        for(int k = j + 1; k < len2; k++ )
                        {
                            if( c->type == TYPE_COLUMN_INT8 )
                            {
                                int8_t *v1 = VoidArray_getInt8( query_results->rows[j], column_index );
                                int8_t *v2 = VoidArray_getInt8( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_UINT8 )
                            {
                                uint8_t *v1 = VoidArray_getUInt8( query_results->rows[j], column_index );
                                uint8_t *v2 = VoidArray_getUInt8( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_INT16 )
                            {
                                int16_t *v1 = VoidArray_getInt16( query_results->rows[j], column_index );
                                int16_t *v2 = VoidArray_getInt16( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_UINT16 )
                            {
                                uint16_t *v1 = VoidArray_getUInt16( query_results->rows[j], column_index );
                                uint16_t *v2 = VoidArray_getUInt16( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_INT32 )
                            {
                                int32_t *v1 = VoidArray_getInt32( query_results->rows[j], column_index );
                                int32_t *v2 = VoidArray_getInt32( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_UINT32 )
                            {
                                uint32_t *v1 = VoidArray_getUInt32( query_results->rows[j], column_index );
                                uint32_t *v2 = VoidArray_getUInt32( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_INT64 )
                            {
                                int64_t *v1 = VoidArray_getInt64( query_results->rows[j], column_index );
                                int64_t *v2 = VoidArray_getInt64( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_UINT64 )
                            {
                                uint64_t *v1 = VoidArray_getUInt64( query_results->rows[j], column_index );
                                uint64_t *v2 = VoidArray_getUInt64( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_INTPTR )
                            {
                                intptr_t *v1 = VoidArray_getIntPtr( query_results->rows[j], column_index );
                                intptr_t *v2 = VoidArray_getIntPtr( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_UINTPTR )
                            {
                                uintptr_t *v1 = VoidArray_getUIntPtr( query_results->rows[j], column_index );
                                uintptr_t *v2 = VoidArray_getUIntPtr( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && *v1 > *v2 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && *v1 < *v2 )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_FLOAT )
                            {
                                float *v1 = VoidArray_getFloat( query_results->rows[j], column_index );
                                float *v2 = VoidArray_getFloat( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && is_float_gt(*v1, *v2, EPSILON) )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && is_float_lt(*v1, *v2, EPSILON) )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_DOUBLE )
                            {
                                double *v1 = VoidArray_getDouble( query_results->rows[j], column_index );
                                double *v2 = VoidArray_getDouble( query_results->rows[k], column_index );
                                
                                if( ! c->mayBeNull && v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( ! c->mayBeNull && v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( 
                                        order_item->typeOrder == SelectQueryOrderType::ASC 
                                     && (
                                              ( v1 != NULL && v2 == NULL )
                                          ||  ( v1 != NULL && v2 != NULL && is_double_gt(*v1, *v2, EPSILON) )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                           order_item->typeOrder == SelectQueryOrderType::DESC 
                                        && (
                                                  ( v1 == NULL && v2 != NULL )
                                              ||  ( v1 != NULL && v2 != NULL && is_double_lt(*v1, *v2, EPSILON) )
                                            )
                                        )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_STR )
                            {
                                char *v1    = VoidArray_getString( query_results->rows[j], column_index );
                                char *v2    = VoidArray_getString( query_results->rows[k], column_index );
                                
                                if( v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                int compare = strcmp(v1, v2);
                                
                                if( 
                                           order_item->typeOrder == SelectQueryOrderType::ASC
                                        && (
                                                ( v1 != NULL && v2 == NULL )
                                            ||  ( v1 != NULL && v2 != NULL && compare > 0 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                               order_item->typeOrder == SelectQueryOrderType::DESC
                                            && (
                                                    ( v1 != NULL && v2 == NULL )
                                                ||  ( v1 != NULL && v2 != NULL && compare < 0 )
                                               )
                                       )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                            else if( c->type == TYPE_COLUMN_VCHAR )
                            {
                                struct VarChar* vv1  = VoidArray_getVarChar( query_results->rows[j], column_index );
                                struct VarChar* vv2  = VoidArray_getVarChar( query_results->rows[k], column_index );
                                
                                char *v1 = (char *) vv1->data->ptr;
                                char *v2 = (char *) vv2->data->ptr;
                                
                                if( v1 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v1 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                if( v2 == NULL )
                                {
                                    result->value = PARSE_QUERY_ERROR_ORDER;
                                    result->str_value = string_format("v2 is NULL %d %d\n", column_index, query_results->rows[j]->len);
                                    return false;
                                }
                                
                                int compare = strcmp(v1, v2);
                                
                                if( 
                                           order_item->typeOrder == SelectQueryOrderType::ASC
                                        && (
                                                ( v1 != NULL && v2 == NULL )
                                            ||  ( v1 != NULL && v2 != NULL && compare > 0 )
                                        )
                                  )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                                else if( 
                                               order_item->typeOrder == SelectQueryOrderType::DESC
                                            && (
                                                    ( v1 != NULL && v2 == NULL )
                                                ||  ( v1 != NULL && v2 != NULL && compare < 0 )
                                               )
                                       )
                                {
                                    if( ! VoidArray_swap(query_results->rows[j], query_results->rows[k]) )
                                    {
                                        result->value = PARSE_QUERY_ERROR_ORDER;
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    
                    find_column = true;
                    break;
                }
                
                column_index += 1;
            }
            
            // поиск дублей в уже отсортированной колонки
            if( find_column )
            {
                for(int j = start_index != -1 ? start_index : 0
                      , len2 = end_index != -1 ? end_index : query_results->rows.size()
                        ; j < len2 - 1
                        ; j++ 
                    )
                {
                    if( c->type == TYPE_COLUMN_INT8 )
                    {
                        int8_t *v1 = VoidArray_getInt8( query_results->rows[j], column_index );
                        
                        int count_eq = 1;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            int8_t *v2 = VoidArray_getInt8( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_UINT8 )
                    {
                        uint8_t *v1 = VoidArray_getUInt8( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            uint8_t *v2 = VoidArray_getUInt8( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_INT16 )
                    {
                        int16_t *v1 = VoidArray_getInt16( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            int16_t *v2 = VoidArray_getInt16( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_UINT16 )
                    {
                        uint16_t *v1 = VoidArray_getUInt16( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            uint16_t *v2 = VoidArray_getUInt16( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_INT32 )
                    {
                        int32_t *v1 = VoidArray_getInt32( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            int32_t *v2 = VoidArray_getInt32( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_UINT32 )
                    {
                        uint32_t *v1 = VoidArray_getUInt32( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            uint32_t *v2 = VoidArray_getUInt32( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_INT64 )
                    {
                        int64_t *v1 = VoidArray_getInt64( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            int64_t *v2 = VoidArray_getInt64( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_UINT64 )
                    {
                        uint64_t *v1 = VoidArray_getUInt64( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            uint64_t *v2 = VoidArray_getUInt64( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_INTPTR )
                    {
                        intptr_t *v1 = VoidArray_getIntPtr( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            intptr_t *v2 = VoidArray_getIntPtr( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_UINTPTR )
                    {
                        uintptr_t *v1 = VoidArray_getUIntPtr( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            uintptr_t *v2 = VoidArray_getUIntPtr( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && *v1 == *v2) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_FLOAT )
                    {
                        float *v1 = VoidArray_getFloat( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            float *v2 = VoidArray_getFloat( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && is_float_eq(*v1, *v2, EPSILON) ) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_DOUBLE )
                    {
                        double *v1 = VoidArray_getDouble( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            double *v2 = VoidArray_getDouble( query_results->rows[k], column_index );

                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && is_double_eq(*v1, *v2, EPSILON) ) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_STR )
                    {
                        char *v1 = VoidArray_getString( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            char *v2 = VoidArray_getString( query_results->rows[k], column_index );
                            
                            if(     
                                    (v1 == NULL && v2 == NULL) 
                                 || (v1 != NULL && v2 != NULL && strcmp(v1, v2) == 0 ) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    else if( c->type == TYPE_COLUMN_VCHAR )
                    {
                        struct VarChar* vv1 = VoidArray_getVarChar( query_results->rows[j], column_index );
                        
                        int count_eq = 0;
                        
                        for(int k = j + 1; k < len2; k++)
                        {
                            struct VarChar* vv2 = VoidArray_getVarChar( query_results->rows[k], column_index );
                            
                            char *v1 = (char *) vv1->data->ptr;
                            char *v2 = (char *) vv2->data->ptr;
                            
                            if(     
                                    (vv1 == NULL && vv2 == NULL) 
                                 || (vv1 != NULL && vv2 != NULL && strcmp(v1, v2) == 0 ) 
                              )
                            {
                                count_eq += 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if( count_eq > 1 )
                        {
                            execOrderResultTable(result, index + 1, j, j + count_eq);
                        }
                    }
                    
                    
                }
            }
            
            
            //execOrderResultTable(result, index + 1);
        }
        
        
        
        
        return true;
    }
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    void setVar(GlobalScope &vars, int i, string name, InfoColum* column, SelectQueryInfoRunTime* item)
    {
        struct VoidArray *v = item->pf->data_list;
        
        if( v->types_mass[i] == VOID_ARRAY_TYPE_INT8)
        {
            int8_t *p = (int8_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("[%d] %s=%lld\n", __LINE__, name.c_str(), *p);
            //printf("VOID_ARRAY_TYPE_INT8: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT8)
        {
            uint8_t *p = (uint8_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINT8: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT16)
        {
            int16_t *p = (int16_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT16)
        {
            uint16_t *p = (uint16_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT32)
        {
            int32_t *p = (int32_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT32)
        {
            uint32_t *p = (uint32_t *) v->mass[i];
            vars[ name ] = packToken( *p );
            //printf("VOID_ARRAY_TYPE_UINT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT64)
        {
            int64_t *p = (int64_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT64)
        {
            uint64_t *p = (uint64_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INTPTR)
        {
            intptr_t *p = (intptr_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINTPTR)
        {
            uintptr_t *p = (uintptr_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_DOUBLE)
        {
            double *p = (double *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_DOUBLE: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_FLOAT)
        {
            float *p = (float *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_FLOAT: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_STR)
        {
            char *p = (char *) v->mass[i];
            vars[ name ] = p;
            //printf("VOID_ARRAY_TYPE_STR: %d %s\n", strlen(p), p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
        {
            struct buf* p = (struct buf*) v->mass[i];
            vars[ name ] = p;
            //printf("VOID_ARRAY_TYPE_BUFFER_DATA: %d\n", p->len);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
        {
            struct VarChar *p = (struct VarChar*) v->mass[i];
            string s;
            s.append((char*)p->data->ptr, p->const_len);
            
            vars[ name ] = s;
            
            //printf("VOID_ARRAY_TYPE_BUFFER_VCHAR: %d %s\n", p->const_len, p->data->ptr);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_NULL)
        {
            vars[ name ] = packToken();
            //printf("VOID_ARRAY_TYPE_NULL\n");
        }
        
        //printf("-setVar: %s -> %d\n", name.c_str(), column->index);
    }
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    void printTableResult()
    {
        //printf("count rows: %d\n", table_results->rows.size());
        
        TextTable t( '-', '|', '+' );
        
        t.add( "row id" );
        
        for (std::map<string, InfoColum*>::iterator it = alias_columns.begin(); it != alias_columns.end(); ++it)
        {
            t.add( string_format("%s-%s", it->first.c_str(), it->second->getStrType().c_str()) );
        }
        
        t.endOfRow();
        
        for(int j = 0; j < query_results->rows.size(); j++)
        {
            struct VoidArray *v = query_results->rows[j];
            
            t.add( string_format("%d", j + 1));
            
            for(int i = 0; i < v->len; i++)
            {
                if( v->types_mass[i] == VOID_ARRAY_TYPE_INT8)
                {
                    int8_t *p = (int8_t *) v->mass[i];
                    
                    t.add( string_format("%d", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT8)
                {
                    uint8_t *p = (uint8_t *) v->mass[i];
                    
                    t.add( string_format("%d", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT16)
                {
                    int16_t *p = (int16_t *) v->mass[i];
                    
                    t.add( string_format("%d", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT16)
                {
                    uint16_t *p = (uint16_t *) v->mass[i];
                    
                    t.add( string_format("%d", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT32)
                {
                    int32_t *p = (int32_t *) v->mass[i];
                    
                    t.add( string_format("%d", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT32)
                {
                    uint32_t *p = (uint32_t *) v->mass[i];
                    
                    t.add( string_format("%lu", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT64)
                {
                    int64_t *p = (int64_t *) v->mass[i];
                    
                    t.add( string_format("%lld", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT64)
                {
                    uint64_t *p = (uint64_t *) v->mass[i];
                    
                    t.add( string_format("%lld", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_INTPTR)
                {
                    intptr_t *p = (intptr_t *) v->mass[i];
                    
                    t.add( string_format("%lld", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINTPTR)
                {
                    uintptr_t *p = (uintptr_t *) v->mass[i];
                    
                    t.add( string_format("%lld", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_DOUBLE)
                {
                    double *p = (double *) v->mass[i];
                    
                    t.add( string_format("%7.7f", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_FLOAT)
                {
                    float *p = (float *) v->mass[i];
                    
                    t.add( string_format("%7.7f", *p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_STR)
                {
                    char *p = (char *) v->mass[i];
                    
                    t.add( string_format("%s", p));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
                {
                    struct buf* p = (struct buf*) v->mass[i];
                    
                    t.add( string_format("%d", p->len));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
                {
                    struct VarChar *p = (struct VarChar*) v->mass[i];
                    
                    t.add( string_format("%s", p->data->ptr));
                }
                else if( v->types_mass[i] == VOID_ARRAY_TYPE_NULL)
                {
                    t.add( string_format("NULL"));
                }
            }
            
            t.endOfRow();
        }
        
        std::cout << t;
    }
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    bool buildOrderList(ResultParseCmd* result, vector<string> &list_order)
    {
        std::regex _pattern("(\\S+)\\s+(\\S+)");
        std::regex _pattern_2("\\s*(\\S+)\\s*");
        std::smatch matches;
        string column_name;
        string type_order;
        
        for(int i = 0; i < list_order.size(); i++)
        {
            if(std::regex_search(list_order[i], matches, _pattern) && matches.size() == 3) 
            {
                column_name  = matches[1];
                type_order   = matches[2];
                type_order   = trim(type_order);
                
                if( ! ( icasecmp(type_order, "ASC") || icasecmp(type_order, "DESC") ) )
                {
                    result->str_value = "Sort value in wrong. Use only 'ASC' or 'DESC'";
                    return false;
                }
                
                if( alias_columns.find( column_name ) == alias_columns.end() )
                {
                    result->str_value = string_format("Column '%s' not found", column_name.c_str());
                    return false;
                }
                
                std::map<string, InfoColum*>::iterator it = alias_columns.find( column_name );
                
                InfoColum* c = it->second;
                
                SelectQueryOrderInfoItem *si = new SelectQueryOrderInfoItem();
                si->c = c;
                
                if( icasecmp(type_order, "ASC") )
                {
                    si->typeOrder = SelectQueryOrderType::ASC;
                }
                else
                {
                    si->typeOrder = SelectQueryOrderType::DESC;
                }
                
                order.push_back(si);
            }
            else if(std::regex_search(list_order[i], matches, _pattern_2) && matches.size() == 2) 
            {
                column_name  = matches[1];
                
                if( alias_columns.find( column_name ) == alias_columns.end() )
                {
                    result->str_value = string_format("Column '%s' not found", column_name.c_str());
                    return false;
                }
                
                std::map<string, InfoColum*>::iterator it = alias_columns.find( column_name );
                
                InfoColum* c = it->second;
                
                SelectQueryOrderInfoItem *si = new SelectQueryOrderInfoItem();
                si->c = c;
                
                order.push_back(si);
            }
        }
        
        haveOrder = order.size() > 0;
        return true;
    }
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    void buildColumnsRead()
    {
        for(int i = 0; i < tables.size(); i++)
        {
            printf("buildColumnsRead tables[i]->index: %d %d %s %d\n", i, tables[i]->index, tables[i]->table_name.c_str(), tables[i]->columns.size());
            
            SelectQueryInfoRunTime* item = new SelectQueryInfoRunTime();
            runtime[ i ] = item;
            
            for(int j = 0; j < tables[i]->columns.size(); j++)
            {
                uint8_t v = 0;
                string column_name = tables[i]->columns[j]->name;
                
                for (std::map<string, InfoColum*>::iterator it = alias_columns.begin(); it != alias_columns.end(); ++it)
                {
                    if( 
                            it->second->index_table == tables[i]->index
                        &&  it->second->index == j
                       )
                    {
                        column_name = it->first;
                        v = 1;
                        break;
                    }
                }
                
                if( v == 0 )
                {
                    for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
                    {
                        if( 
                                it->second->index_table == tables[i]->index
                            &&  it->second->index == j
                           )
                        {
                            column_name = it->first;
                            v = 1;
                            break;
                        }
                    }
                }
                
                printf("column_name: %s = %d %s\n", column_name.c_str(), v, tables[i]->columns[j]->name.c_str());
                
                item->mask_read_columns_names.push_back( column_name );
                item->mask_read_columns.push_back(v);
            }
        }
        
        printf("+++ mask read\n");
        
        for (std::map<int, SelectQueryInfoRunTime*>::iterator it = runtime.begin(); it != runtime.end(); ++it)
        {
            printf("table index: %d\n", it->first);
            
            for(int i = 0; i < it->second->mask_read_columns.size(); i++)
            {
                printf(" '%s' = %d\n", it->second->mask_read_columns_names[i].c_str(), it->second->mask_read_columns[i]);
            }
        }
        
        printf("--- mask read\n");
    }
    
    InfoColum* getColumnInTables(string name)
    {
        for(int i = 0; i < tables.size(); i++)
        {
            for(int j = 0; j < tables[i]->columns.size(); j++)
            {
                if( icasecmp(tables[i]->columns[j]->name, name) )
                {
                    return tables[i]->columns[j];
                }
            }
        }
        
        return NULL;
    }
    
    InfoColum* getColumnInByTableName(string table_name, string name)
    {
        for(int i = 0; i < tables.size(); i++)
        {
            if( icasecmp(tables[i]->table_name, table_name) )
            {
                for(int j = 0; j < tables[i]->columns.size(); j++)
                {
                    if( icasecmp(tables[i]->columns[j]->name, name) )
                    {
                        return tables[i]->columns[j];
                    }
                }
                
                break;
            }
        }
        
        return NULL;
    }
    
    int getCountColumnInTables(string name)
    {
        int result = 0;
        
        for(int i = 0; i < tables.size(); i++)
        {
            for(int j = 0; j < tables[i]->columns.size(); j++)
            {
                if( icasecmp(tables[i]->columns[j]->name, name) )
                {
                    result += 1;
                }
            }
        }
        
        return result;
    }
    
    //по убыванию кол-во элементов в таблицах
    void sortTableIndex(bool sort_descending = false)
    {
        int size = tables.size();
        
        if( size <= 1 )
        {
            return;
        }
        
        for(int i = 0; i < size; i++)
        {
            for(int j = i + 1; j < size; j++)
            {
                if( sort_descending )
                {
                    if( tables[i]->count  <  tables[j]->count )
                    {
                        TableInto* tmp = tables[i];
                        tables[i] = tables[j];
                        tables[j] = tmp;
                        
                        AHTables* tmp2 = db_lidt[i];
                        db_lidt[i] = db_lidt[j];
                        db_lidt[j] = tmp2;
                    }
                }
                else
                {
                    if( tables[i]->count  >  tables[j]->count )
                    {
                        TableInto* tmp = tables[i];
                        tables[i] = tables[j];
                        tables[j] = tmp;
                        
                        AHTables* tmp2 = db_lidt[i];
                        db_lidt[i] = db_lidt[j];
                        db_lidt[j] = tmp2;
                    }
                }
                    
            }
        }
    }
    
    int addWhereNewColumn(vector<string> v)
    {
        int error = 0;
        
        for(int i = 0; i < v.size(); i++)
        {
            bool found = false;
            
            for (std::map<string, InfoColum*>::iterator it = alias_columns.begin(); it != alias_columns.end(); ++it)
            {
                // нашли в списке alias_columns
                if( icasecmp(v[i], it->first) || icasecmp(v[i], it->second->name) )
                {
                    //printf("add where_columns: %s %s\n", v[i].c_str(), it->second->name.c_str());
                    where_columns[ v[i] ] = it->second;
                    found = true;
                    break;
                }
                /*else if( icasecmp(v[i], it->second->name) )
                {
                    printf("error %d %s %s\n", __LINE__, v[i].c_str(), it->second->name.c_str());
                    error = PARSE_QUERY_ERROR_COLUMN_IN_WHERE_ERROR_NAME;
                    break;
                }*/
            }
            
            if( error != 0 )
            {
                break;
            }
            
            if( ! found )
            {
                InfoColum* tmp = getColumnInTables( v[i] );
                
                if(tmp != NULL)
                {
                    where_columns[ v[i] ] = tmp;
                }
            }
        }
        
        return error;
    }
    
    /*vector<string> testWhere(string where)
    {
        int len   = where.length();
        char* str = (char*) where.c_str();
        vector<string> list;
        
        for(int i = 0; i < len; i++)
        {
            _skipSpace(str, len, &i);
            if( skipStringBlock(str, len, &i) )
            {
                continue;
            }
            
            int save_offset;
            char* w = _getWord(str, len, i, "!@#$%^&*()-_+[]{}/=*~`\\\'\"<>?,| \t\n\r\f\v", &save_offset);
            
            if( w != NULL )
            {
                if( ! isdigit(w[0]) )
                {
                    list.push_back( w );
                    printf("w: %s\n", w);
                }
                
                free(w);

                i = save_offset - 1;
            }
        }
        
        std::sort(list.begin(), list.end());
        list.erase(std::unique(list.begin(), list.end()), list.end());
        
        return list;
    }*/
    
    void printColumnsInfo()
    {
        printf("++++ printColumnsInfo\n");
        
        for (std::map<string, InfoColum*>::iterator it = alias_columns.begin(); it != alias_columns.end(); ++it)
        {
            printf("%s = ", it->first.c_str());
            
            InfoColum* c = it->second;
            c->debug_print();
            
            printf("\n");
        }
        
        printf("--- where\n");
        
        for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
        {
            printf("%s = ", it->first.c_str());
            
            InfoColum* c = it->second;
            c->debug_print();
            
            printf("\n");
        }
        
        printf("---- printColumnsInfo\n");
    }
    
    /*void debugPrintResult()
    {
        
    }*/
    
    bool addInAliasColumns(string name, InfoColum* c)
    {
        if( alias_columns.find( name ) == alias_columns.end() )
        {
            alias_columns[ name ] = c;
            return true;
        }
        
        return false;
    }
    
    bool existInListTables(string name)
    {
        for(int i = 0; i < tables.size(); i++)
        {
            if( icasecmp( tables[i]->table_name, name ) )
            {
                return true;
            }
        }
        
        return false;
    }
    
    vector<uint64_t> getListAddressInBatabaseOneColumnOrder(AHTables* db, InfoColum *c, SelectQueryOrderInfoItem *order)
    {
        vector<uint64_t> result;
        
        bool first_read = false;
        struct PAGE_FRAGMENT *pf;
        
        vector<uint8_t> mask_read_columns;
        
        //struct VoidArray *row = VoidArray_init();
        
        while(true)
        {
            if( ! first_read )
            {
                first_read = true;
                
                pf = db->findFirstPage(mask_read_columns, c->index_table);
                    
                if( pf == NULL )
                {
                    printf("[%d] item->pf == NULL\n", __LINE__);
                    break;
                }
            }
            else
            {
                struct PAGE_FRAGMENT *pf_next = db->findNextPage(pf, mask_read_columns, c->index_table);

                if( pf_next == NULL )
                {
                    printf("[%d] item->pf == NULL\n", __LINE__);

                    break;
                }

                free_Page_Fragment( pf );
                pf = pf_next;
            }
            
            //VoidArray_append(row, pf->data_list);
        }
        
        
        
        return result;
    }
    
    SelectQueryInfo()
    {
        haveWhere            = false;
        haveOrder            = false;
        haveOffset           = false;
        haveLimit            = false;
        query_results        = new QueryResult;
        query_results->type  = QueryResultType::TABLE;
        
        offset = limit  = 0;
        _append_rows    = 0;
    }
    
    ~SelectQueryInfo()
    {
        if( query_results != NULL )
        {
            delete query_results;
        }
        
        for(int i = 0; i < order.size(); i++)
        {
            delete order[i];
        }
    }
};
//==============================================================================
struct UpdateQueryInfo
{
    struct AHTables *db;
    struct TableInto* table;
    
    uint64_t offset, limit, _update_rows;
    string where;
    
    map <string, InfoColum*> set_columns;
    map <string, string>     set_values;
    map <string, InfoColum*> read_columns;
    
    //map <string, InfoColum*> vars_in_where;
    
    bool set_columns_is_fix, haveWhere;;
    vector<uint8_t> mask_update_columns, mask_read_columns;
    
    bool exec(ResultParseCmd* result, GlobalScope &vars)
    {
        uint32_t row_index  = 0;
        bool first_read     = true;
        struct PAGE_FRAGMENT *pf = NULL;
        struct VoidArray *update_list = NULL;
        
        /*if( set_columns_is_fix )
        {
            VoidArray_free(update_list);
            
            update_list = buidListBySetColums(result, vars);
            debug_void_array_print(update_list);
        }*/
        
        while(true)
        {
            row_index += 1;
            
            if( first_read )
            {
                first_read = false;
                
                pf = db->findFirstPage(mask_read_columns, table->index);

                if( pf == NULL )
                {
                    //printf("[%d] item->pf == NULL\n", __LINE__);

                    result->value = SELECT_QUERY_INFO_STOP;
                    return true;
                }
            }
            else
            {
                //printf(">> next read\n");

                struct PAGE_FRAGMENT *pf_next = db->findNextPage(pf, mask_read_columns, table->index);

                if( pf_next == NULL )
                {
                    //printf("[%d] item->pf == NULL\n", __LINE__);
                    break;
                }

                free_Page_Fragment( pf );
                pf = pf_next;
            }
            
            if( read_columns.size() )
            {
                if(mask_read_columns.size() == 0)
                {
                    //for(int i = 0, list_index = 0; i < table->columns.size(); i++)
                    {
                        for (std::map<string, InfoColum*>::iterator it = read_columns.begin(); it != read_columns.end(); ++it)
                        {
                            //if( it->second->index == table->columns[i]->index )
                            {
                                printf(" 1 setVar %s %d %d\n", it->first.c_str(), it->second->index, pf->data_list->len);
                                
                                setVar(vars, it->first, it->second, it->second->index, pf->data_list);
                                //list_index += 1;
                                
                                //break;
                            }
                        }
                    }
                }
                else
                {
                    for(int i = 0, list_index = 0; i < table->columns.size(); i++)
                    {
                        if( mask_read_columns[i] )
                        {
                            for (std::map<string, InfoColum*>::iterator it = read_columns.begin(); it != read_columns.end(); ++it)
                            {
                                if( it->second->index == table->columns[i]->index )
                                {
                                    printf(" 2 setVar %s %d %d %d %d\n", it->second->name.c_str(), list_index, it->second->index, pf->data_list->len, read_columns.size());
                                    
                                    setVar(vars, it->first, it->second, list_index, pf->data_list);
                                    
                                    break;
                                }
                            }
                            
                            list_index += 1;
                        }
                    }
                }
                
                if( haveWhere )
                {
                    packToken result_exec_where = calculator::calculate(where.c_str(), vars);

                    if( result_exec_where.asBool() )
                    {
                        printf("result_exec_where: true\n");
                    }
                    else
                    {
                        printf("result_exec_where: false\n");
                        continue;
                    }
                }
            }
            
            if(offset == 0 || _update_rows + 1 > offset)
            {
                if( set_columns_is_fix )
                {
                    VoidArray_free(update_list);
                    update_list = buidListBySetColums(result, vars);
                    
                    printf("[%d] %d %d\n", __LINE__, update_list->len, table->columns.size());
                    
                    db->editPageB(pf, update_list, mask_update_columns, table->index);
                }
                else
                {
                    printf("[%d] %d %d\n", __LINE__, pf->data_list->len, table->columns.size());

                    for (std::map<string, InfoColum*>::iterator it = set_columns.begin(); it != set_columns.end(); ++it)
                    {
                        try
                        {
                            printf("%s\n", set_values[ it->first ].c_str());
                            
                            packToken new_value = calculator::calculate( set_values[ it->first ].c_str(), vars );
                            changeValuePage(pf, it->second, new_value);
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
                        
                        
                    }

                    db->editPageA(pf, pf->data_list, true, table->index);
                }
            }
            _update_rows += 1;
            
            if( limit != 0 && _update_rows > limit )
            {
                break;
            }
        }
        
        return false;
    }
    
    struct VoidArray* buidListBySetColums(ResultParseCmd* result, GlobalScope &vars)
    {
        struct VoidArray* res = VoidArray_init();
        
        for(int j = 0; j < table->columns.size(); j++)
        {
            for (std::map<string, InfoColum*>::iterator it = set_columns.begin(); it != set_columns.end(); ++it)
            {
                if( it->second->index == table->columns[j]->index )
                {
                    try
                    {
                        packToken new_value = calculator::calculate( set_values[ it->first ].c_str(), vars );
                        
                        printf("%d %d %d '%s'\n", __LINE__, new_value.getType(), it->second->index, set_values[ it->first ].c_str());
                        
                        if( new_value.getType() == NONE )
                        {
                            VoidArray_addNULL(res);
                            continue;
                        }

                        if( it->second->type == TYPE_COLUMN_INT8 )
                        {
                            VoidArray_addInt8(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_UINT8 )
                        {
                            VoidArray_addUInt8(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_INT16 )
                        {
                            VoidArray_addInt16(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_UINT16 )
                        {
                            VoidArray_addUInt16(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_INT32 )
                        {
                            VoidArray_addInt32(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_UINT32 )
                        {
                            VoidArray_addUInt32(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_INT64 )
                        {
                            VoidArray_addInt64(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_UINT64 )
                        {
                            VoidArray_addUInt64(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_INTPTR )
                        {
                            VoidArray_addIntPtr(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_UINTPTR )
                        {
                            VoidArray_addUIntPtr(res, new_value.asInt());
                        }
                        else if( it->second->type == TYPE_COLUMN_FLOAT )
                        {
                            VoidArray_addFloat(res, new_value.asDouble());
                        }
                        else if( it->second->type == TYPE_COLUMN_DOUBLE )
                        {
                            VoidArray_addDouble(res, new_value.asDouble());
                        }
                        else if( it->second->type == TYPE_COLUMN_STR )
                        {
                            VoidArray_addStr(res, (char*) new_value.asString().c_str());
                        }
                        else if( it->second->type == TYPE_COLUMN_VCHAR )
                        {
                            VoidArray_addVChar(res, (char*) new_value.asString().c_str(), it->second->prop_1);
                        }
                    }
                    catch (const std::exception& e) 
                    {
                        result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                        result->str_value  = e.what();
                        printf("[%d] error: %s\n", __LINE__, e.what());
                        return res;
                    } 
                    catch (const char* c) 
                    {
                        result->value      = PARSE_QUERY_ERROR_RUNTIME_IN_WHERE;
                        result->str_value  = c;
                        printf("[%d] error: %s\n", __LINE__, c);
                        return res;
                    }
                    
                    //break;
                }
            }
        }
        
        return res;
    }
    
    void changeValuePage(struct PAGE_FRAGMENT *pf, InfoColum* c, packToken &new_value)
    {
        if(new_value.getType() == NONE)
        {
            VoidArray_setNULL(pf->data_list, c->index);
            return;
        }
        
        if( c->type == TYPE_COLUMN_INT8 )
        {
            VoidArray_setInt8(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_UINT8 )
        {
            VoidArray_setUInt8(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_INT16 )
        {
            VoidArray_setInt16(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_UINT16 )
        {
            VoidArray_setUInt16(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_INT32 )
        {
            VoidArray_setInt32(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_UINT32 )
        {
            VoidArray_setUInt32(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_INT64 )
        {
            VoidArray_setInt64(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_UINT64 )
        {
            VoidArray_setUInt64(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_INTPTR )
        {
            VoidArray_setIntPtr(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_UINTPTR )
        {
            VoidArray_setUIntPtr(pf->data_list, new_value.asInt(), c->index);
        }
        else if( c->type == TYPE_COLUMN_FLOAT )
        {
            VoidArray_setFloat(pf->data_list, new_value.asDouble(), c->index);
        }
        else if( c->type == TYPE_COLUMN_DOUBLE )
        {
            VoidArray_setDouble(pf->data_list, new_value.asDouble(), c->index);
        }
        else if( c->type == TYPE_COLUMN_STR )
        {
            VoidArray_setStr(pf->data_list, (char* )new_value.asString().c_str(), c->index);
        }
        else if( c->type == TYPE_COLUMN_VCHAR )
        {
            VoidArray_setVChar(pf->data_list, (char* )new_value.asString().c_str(), c->prop_1, c->index);
        }
    }
    
    void setVar(GlobalScope &vars, string name, InfoColum* column, int i, VoidArray* v)
    {
        //debug_void_array_print(v);
        
        if( v->types_mass[i] == VOID_ARRAY_TYPE_INT8)
        {
            int8_t *p = (int8_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_INT8: %s %d\n", name.c_str(), *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT8)
        {
            uint8_t *p = (uint8_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_UINT8: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT16)
        {
            int16_t *p = (int16_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_INT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT16)
        {
            uint16_t *p = (uint16_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_UINT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT32)
        {
            int32_t *p = (int32_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_INT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT32)
        {
            uint32_t *p = (uint32_t *) v->mass[i];
            vars[ name ] = packToken( *p );
            printf("VOID_ARRAY_TYPE_UINT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT64)
        {
            int64_t *p = (int64_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_INT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT64)
        {
            uint64_t *p = (uint64_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_UINT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INTPTR)
        {
            intptr_t *p = (intptr_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_INTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINTPTR)
        {
            uintptr_t *p = (uintptr_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_UINTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_DOUBLE)
        {
            double *p = (double *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_DOUBLE: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_FLOAT)
        {
            float *p = (float *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_FLOAT: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_STR)
        {
            char *p = (char *) v->mass[i];
            vars[ name ] = packToken(p);
            printf("VOID_ARRAY_TYPE_STR: %d '%s'\n", strlen(p), p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
        {
            struct buf* p = (struct buf*) v->mass[i];
            vars[ name ] = p;
            printf("VOID_ARRAY_TYPE_BUFFER_DATA: %d\n", p->len);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
        {
            struct VarChar *p = (struct VarChar*) v->mass[i];
            string s;
            s.append((char*)p->data->ptr, p->const_len);
            
            vars[ name ] = s;
            
            printf("VOID_ARRAY_TYPE_BUFFER_VCHAR: %d '%s'\n", p->const_len, p->data->ptr);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_NULL)
        {
            vars[ name ] = packToken();
            
            printf("VOID_ARRAY_TYPE_NULL\n");
        }
        
        printf("end setVar: %s -> %d\n", name.c_str(), column->index);
    }
    
    void setMaskUpdateColumns()
    {
        for(int i = 0; i < table->columns.size(); i++)
        {
            uint8_t v = 0;

            for (std::map<string, InfoColum*>::iterator it = set_columns.begin(); it != set_columns.end(); ++it)
            {
                if( 
                        table->index == it->second->index_table
                     && table->columns[i]->index == it->second->index
                  )
                {
                    v = 1;
                    break;
                }
            }

            mask_update_columns.push_back(v);
        }
    }
    
    void setMaskReadWhereColumns()
    {
        if( ! set_columns_is_fix )
        {
            return;
        }
        
        for(int i = 0; i < table->columns.size(); i++)
        {
            if(mask_update_columns[i] == 1)
            {
                mask_read_columns.push_back(1);
                continue;
            }
            
            uint8_t v = 0;

            for (std::map<string, InfoColum*>::iterator it = read_columns.begin(); it != read_columns.end(); ++it)
            {
                if( 
                        table->index == it->second->index_table
                     && table->columns[i]->index == it->second->index
                  )
                {
                    v = 1;
                    break;
                }
            }

            mask_read_columns.push_back(v);
        }
    }
    
    int addWhereNewColumn(vector<string> v)
    {
        int error = 0;
        
        for(int i = 0; i < v.size(); i++)
        {
            bool found = false;
            
            for (std::map<string, InfoColum*>::iterator it = read_columns.begin(); it != read_columns.end(); ++it)
            {
                // нашли в списке alias_columns
                if( icasecmp(v[i], it->first) )
                {
                    found = true;
                    break;
                }
                else if( icasecmp(v[i], it->second->name) )
                {
                    printf("error 270\n");
                    error = PARSE_QUERY_ERROR_COLUMN_IN_WHERE_ERROR_NAME;
                    break;
                }
            }
            
            if( error != 0 )
            {
                break;
            }
            
            if( ! found )
            {
                InfoColum* tmp = table->getColumnInByName( v[i] );
                
                if(tmp != NULL)
                {
                    read_columns[ v[i] ] = tmp;
                }
            }
        }
        
        return error;
    }
    
    /*vector<string> testWhere(string where)
    {
        int len   = where.length();
        char* str = (char*) where.c_str();
        vector<string> list;
        
        for(int i = 0; i < len; i++)
        {
            _skipSpace(str, len, &i);
            if( skipStringBlock(str, len, &i) )
            {
                continue;
            }
            
            int save_offset;
            char* w = _getWord(str, len, i, "!@#$%^&*()-_+[]{}/=*~`\\\'\"<>?,| \t\n\r\f\v", &save_offset);
            
            if( w != NULL )
            {
                if( ! isdigit(w[0]) )
                {
                    list.push_back( w );
                    printf("w: %s\n", w);
                }
                
                free(w);
                
                i = save_offset - 1;
            }
        }
        
        std::sort(list.begin(), list.end());
        list.erase(std::unique(list.begin(), list.end()), list.end());
        
        return list;
    }*/
    
    UpdateQueryInfo()
    {
        haveWhere = false;
        where = "";
        set_columns_is_fix = true;
        
        offset = limit = _update_rows = 0;
    }
    
    ~UpdateQueryInfo()
    {
        
    }
};

//==============================================================================

struct DeleteQueryInfo
{
    struct AHTables *_table;
    struct TableInto* table;
    
    uint64_t offset, limit, _delete_rows;
    string where;
    
    map <string, InfoColum*> where_columns;
    vector<uint8_t> mask_read_columns;
    
    bool haveWhere;
    
    bool exec(ResultParseCmd* result, GlobalScope &vars)
    {
        uint32_t row_index  = 0;
        bool first_read     = true;
        struct PAGE_FRAGMENT *pf = NULL;
        
        while(true)
        {
            row_index += 1;
            
            if( first_read )
            {
                first_read = false;
                
                pf = _table->findFirstPage(mask_read_columns, table->index);

                if( pf == NULL )
                {
                    printf("[%d] item->pf == NULL\n", __LINE__);

                    result->value = SELECT_QUERY_INFO_STOP;
                    return true;
                }
            }
            else
            {
                printf(">> next read\n");

                struct PAGE_FRAGMENT *pf_next = _table->findNextPage(pf, mask_read_columns, table->index);

                if( pf_next == NULL )
                {
                    printf("[%d] item->pf == NULL\n", __LINE__);

                    break;
                }

                free_Page_Fragment( pf );
                pf = pf_next;
            }
            
            if( haveWhere )
            {
                if(mask_read_columns.size() == 0)
                {
                    for(int i = 0, list_index = 0; i < table->columns.size(); i++)
                    {
                        for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
                        {
                            if( it->second->index == table->columns[i]->index )
                            {
                                setVar(vars, it->first, it->second, list_index, pf->data_list);
                                list_index += 1;
                                
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for(int i = 0, list_index = 0; i < table->columns.size(); i++)
                    {
                        if( mask_read_columns[i] )
                        {
                            for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
                            {
                                if( it->second->index == table->columns[i]->index )
                                {
                                    setVar(vars, it->first, it->second, list_index, pf->data_list);
                                    list_index += 1;

                                    break;
                                }
                            }
                        }
                    }
                }
                
                packToken result_exec_where = calculator::calculate(where.c_str(), vars);

                if( result_exec_where.asBool() )
                {
                    printf("result_exec_where: true\n");
                }
                else
                {
                    printf("result_exec_where: false\n");
                    continue;
                }
            }
            
            if(offset == 0 || _delete_rows + 1 > offset)
            {
                printf("+++ __delete page__ +++\n");
                _table->deletePage(pf, table->index);
            }
            _delete_rows += 1;
            
            if( limit != 0 && _delete_rows > limit )
            {
                printf("_delete_rows > limit: %d > %d\n", _delete_rows, limit);
                break;
            }
        }
        
        return false;
    }
    
    void setVar(GlobalScope &vars, string name, InfoColum* column, int i, VoidArray* v)
    {
        debug_void_array_print(v);
        
        if( v->types_mass[i] == VOID_ARRAY_TYPE_INT8)
        {
            int8_t *p = (int8_t *) v->mass[i];
            vars[ name ] = *p;
            printf("VOID_ARRAY_TYPE_INT8: %s %d\n", name.c_str(), *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT8)
        {
            uint8_t *p = (uint8_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINT8: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT16)
        {
            int16_t *p = (int16_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT16)
        {
            uint16_t *p = (uint16_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT32)
        {
            int32_t *p = (int32_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT32)
        {
            uint32_t *p = (uint32_t *) v->mass[i];
            vars[ name ] = packToken( *p );
            //printf("VOID_ARRAY_TYPE_UINT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT64)
        {
            int64_t *p = (int64_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT64)
        {
            uint64_t *p = (uint64_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INTPTR)
        {
            intptr_t *p = (intptr_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_INTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINTPTR)
        {
            uintptr_t *p = (uintptr_t *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_UINTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_DOUBLE)
        {
            double *p = (double *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_DOUBLE: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_FLOAT)
        {
            float *p = (float *) v->mass[i];
            vars[ name ] = *p;
            //printf("VOID_ARRAY_TYPE_FLOAT: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_STR)
        {
            char *p = (char *) v->mass[i];
            vars[ name ] = p;
            //printf("VOID_ARRAY_TYPE_STR: %d %s\n", strlen(p), p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
        {
            struct buf* p = (struct buf*) v->mass[i];
            vars[ name ] = p;
            //printf("VOID_ARRAY_TYPE_BUFFER_DATA: %d\n", p->len);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
        {
            struct VarChar *p = (struct VarChar*) v->mass[i];
            string s;
            s.append((char*)p->data->ptr, p->const_len);
            
            vars[ name ] = s;
            
            //printf("VOID_ARRAY_TYPE_BUFFER_VCHAR: %d %s\n", p->const_len, p->data->ptr);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_NULL)
        {
            vars[ name ] = packToken();
            
            //printf("VOID_ARRAY_TYPE_NULL\n");
        }
        
        printf("setVar: %s -> %d\n", name.c_str(), column->index);
    }
    
    void setMaskReadWhereColumns()
    {
        for(int i = 0; i < table->columns.size(); i++)
        {
            uint8_t v = 0;

            for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
            {
                if( 
                        table->index == it->second->index_table
                     && table->columns[i]->index == it->second->index
                  )
                {
                    v = 1;
                    break;
                }
            }

            mask_read_columns.push_back(v);
        }
    }
    
    int addWhereNewColumn(vector<string> v)
    {
        int error = 0;
        
        for(int i = 0; i < v.size(); i++)
        {
            bool found = false;
            
            for (std::map<string, InfoColum*>::iterator it = where_columns.begin(); it != where_columns.end(); ++it)
            {
                // нашли в списке alias_columns
                if( icasecmp(v[i], it->first) )
                {
                    found = true;
                    break;
                }
                else if( icasecmp(v[i], it->second->name) )
                {
                    printf("error 270\n");
                    error = PARSE_QUERY_ERROR_COLUMN_IN_WHERE_ERROR_NAME;
                    break;
                }
            }
            
            if( error != 0 )
            {
                break;
            }
            
            if( ! found )
            {
                InfoColum* tmp = table->getColumnInByName( v[i] );
                
                if(tmp != NULL)
                {
                    where_columns[ v[i] ] = tmp;
                }
            }
        }
        
        return error;
    }
    
    DeleteQueryInfo()
    {
        haveWhere = false;
        where = "";
        offset = limit = _delete_rows = 0;
    }
    
    ~DeleteQueryInfo()
    {
        
    }
};




#endif /* DATABASE_H */

