/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   select_query_info.h
 * Author: sk
 *
 * Created on December 29, 2020, 6:37 PM
 */

#ifndef SELECT_QUERY_INFO_H
#define SELECT_QUERY_INFO_H

#include <string>
#include <vector>
#include <map>
#include <regex>

#include "ah_api.h"
#include <stdbool.h>
#include <stdlib.h>


struct SelectQueryInfoRunTime
{
    vector<uint8_t> mask_read_columns;
    bool first_read;
    
    SelectQueryInfoRunTime()
    {
        first_read = false;
    }
    
    ~SelectQueryInfoRunTime()
    {
        
    }
};
    
struct SelectQueryInfo
{
    struct AHBase_DB *db;
    
    vector<TableInto*> tables;
    map <string, InfoColum*> alias_columns;
    map <string, InfoColum*> where_columns;
    
    // table index, mask_read
    map <int, SelectQueryInfoRunTime*> runtime;
    
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    void exec(int index = 0, GlobalScope* vars = NULL)
    {
        if( vars == NULL )
        {
            vars = new GlobalScope();
        }
        
        if( runtime.find(index) != runtime.end() )
        {
            SelectQueryInfoRunTime* item = runtime[index];
            
            if( ! item->first_read )
            {
                struct PAGE_FRAGMENT *p = ah_api_find_first_page(db, item->mask_read_columns, index);
            }
            
            exec(index + 1);
        }
        else
        {
            
        }
    }
    
    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    void buildColumnsRead()
    {
        for(int i = 0; i < tables.size(); i++)
        {
            SelectQueryInfoRunTime* item = new SelectQueryInfoRunTime();
            runtime[ tables[i]->index ] = item;
            
            for(int j = 0; j < tables[i]->columns.size(); j++)
            {
                uint8_t v = 0;
                
                for (std::map<string, InfoColum*>::iterator it = alias_columns.begin(); it != alias_columns.end(); ++it)
                {
                    if( 
                            it->second->index_table == tables[i]->index
                        &&  it->second->index == j
                       )
                    {
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
                            v = 1;
                            break;
                        }
                    }
                }
                
                item->mask_read_columns.push_back(v);
            }
        }
        
        printf("+++ mask read\n");
        
        for (std::map<int, SelectQueryInfoRunTime*>::iterator it = runtime.begin(); it != runtime.end(); ++it)
        {
            printf("[%d] - '", it->first);
            
            for(int i = 0; i < it->second->mask_read_columns.size(); i++)
            {
                printf("%d", it->second->mask_read_columns[i]);
            }
            
            printf("'\n");
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
                    }
                }
                else
                {
                    if( tables[i]->count  >  tables[j]->count )
                    {
                        TableInto* tmp = tables[i];
                        tables[i] = tables[j];
                        tables[j] = tmp;
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
                InfoColum* tmp = getColumnInTables( v[i] );
                
                if(tmp != NULL)
                {
                    where_columns[ v[i] ] = tmp;
                }
            }
        }
        
        return error;
    }
    
    vector<string> testWhere(string where)
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
    }
    
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
    
    SelectQueryInfo()
    {
        
    }
    
    ~SelectQueryInfo()
    {
        
    }
};

#endif /* SELECT_QUERY_INFO_H */

