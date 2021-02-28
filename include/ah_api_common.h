/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ah_api_common.h
 * Author: sk
 *
 * Created on January 31, 2021, 4:29 PM
 */

#ifndef AH_API_COMMON_H
#define AH_API_COMMON_H

#include <stdio.h>
#include "utils/void_array.h"
#include "utils/util_string.h"

#define TYPE_COLUMN_INT8        0x01
#define TYPE_COLUMN_UINT8       0x02
#define TYPE_COLUMN_INT16       0x03
#define TYPE_COLUMN_UINT16      0x04
#define TYPE_COLUMN_INT32       0x05
#define TYPE_COLUMN_UINT32      0x06
#define TYPE_COLUMN_INT64       0x07
#define TYPE_COLUMN_UINT64      0x08
#define TYPE_COLUMN_INTPTR      0x09
#define TYPE_COLUMN_UINTPTR     0x10
#define TYPE_COLUMN_FLOAT       0x11
#define TYPE_COLUMN_DOUBLE      0x12
#define TYPE_COLUMN_BUFF        0x13
#define TYPE_COLUMN_STR         0x14
#define TYPE_COLUMN_VCHAR       0x15

struct InfoColum 
{
    string name;
    uint8_t type; 
    uint16_t prop_1;
    uint16_t index;         // номер колонки с 0
    uint16_t index_table;   // номер таблицы с 0
    
    bool mayBeNull;   // может быть NULL
    
    InfoColum()
    {
        name = "";
        prop_1 = type = 0;
        index_table = index = 0;
        
        mayBeNull = false;
    }
    
    void debug_print()
    {
        printf("name: %s\n", name.c_str());
        printf("type: ");
        
             if( type == TYPE_COLUMN_INT8 )    printf("INT8");
        else if( type == TYPE_COLUMN_UINT8 )   printf("UINT8");
        else if( type == TYPE_COLUMN_INT16 )   printf("INT16");
        else if( type == TYPE_COLUMN_UINT16 )  printf("UINT16");
        else if( type == TYPE_COLUMN_INT32 )   printf("INT32");
        else if( type == TYPE_COLUMN_UINT32 )  printf("UINT32");
        else if( type == TYPE_COLUMN_INT64 )   printf("INT64");
        else if( type == TYPE_COLUMN_UINT64 )  printf("UINT64");
        else if( type == TYPE_COLUMN_INTPTR )  printf("INTPTR");
        else if( type == TYPE_COLUMN_UINTPTR ) printf("UINTPTR");
        else if( type == TYPE_COLUMN_FLOAT )   printf("FLOAT");
        else if( type == TYPE_COLUMN_DOUBLE )  printf("DOUBLE");
        else if( type == TYPE_COLUMN_BUFF )    printf("BUFF");
        else if( type == TYPE_COLUMN_STR )     printf("STR");
        else if( type == TYPE_COLUMN_VCHAR )   printf("VCHAR %d", prop_1);
        
        printf("\n");
        printf("mayBeNull: %d\n", mayBeNull ? 1 : 0);
    }
    
    string getStrType()
    {
             if( type == TYPE_COLUMN_INT8 )    return "INT8";
        else if( type == TYPE_COLUMN_UINT8 )   return "UINT8";
        else if( type == TYPE_COLUMN_INT16 )   return "INT16";
        else if( type == TYPE_COLUMN_UINT16 )  return "UINT16";
        else if( type == TYPE_COLUMN_INT32 )   return "INT32";
        else if( type == TYPE_COLUMN_UINT32 )  return "UINT32";
        else if( type == TYPE_COLUMN_INT64 )   return "INT64";
        else if( type == TYPE_COLUMN_UINT64 )  return "UINT64";
        else if( type == TYPE_COLUMN_INTPTR )  return "INTPTR";
        else if( type == TYPE_COLUMN_UINTPTR ) return "UINTPTR";
        else if( type == TYPE_COLUMN_FLOAT )   return "FLOAT";
        else if( type == TYPE_COLUMN_DOUBLE )  return "DOUBLE";
        else if( type == TYPE_COLUMN_BUFF )    return "BUFF";
        else if( type == TYPE_COLUMN_STR )     return "STR";
        else if( type == TYPE_COLUMN_VCHAR )   return string_format("VCHAR %d", prop_1);
    }
};

struct TableInto
{
    uint64_t pos_in_file_refs; /* позиция в фале, где находятся ссылки таблицы */ 
            
    uint32_t pos_first;        /* указатель на позицию начала списка данных */
    uint32_t pos_end;          /* указатель на позицию конца списка данных */
    uint32_t count;            /* кол-во элементов в списке */
    uint16_t index;            // индекс таблицы с 0
    
    string table_name;
    
    vector<InfoColum*> columns;
    
    TableInto() {
        pos_first = pos_end = count = pos_in_file_refs = 0;
        index = 0;
        table_name = "";
    }
    
    ~TableInto() {
        for(int i = 0; i < columns.size(); i++)
        {
            if( columns[i] != NULL )
            {
                delete columns[i];
                columns[i] = NULL;
            }
        }
    }
    
    int getCountColums() {
        return columns.size();
    }
    
    uint8_t getColumTypeByIndex(uint16_t index) {
        if( index < columns.size() )
        {
            return columns[index]->type;
        }
        
        return 0;
    }
    
    InfoColum* getColumByIndex(uint16_t index) {
        if( index < columns.size() )
        {
            return columns[index];
        }
        
        return NULL;
    }
    
    InfoColum* getColumnInByName(string name) {
        for(int j = 0; j < columns.size(); j++)
        {
            if( icasecmp(columns[j]->name, name) )
            {
                return columns[j];
            }
        }
        
        return NULL;
    }
    
    void debug_print() {
        printf("-- debug_print ----------------------------\n");
        printf("table_name: %s\n", table_name.c_str());
        printf("columns: %ld\n", columns.size());
        
        for(int i = 0; i < columns.size(); i++)
        {
            columns[i]->debug_print();
        }
        printf("------------------------------------------\n");
    }
};

struct PAGE_FRAGMENT
{
    uint32_t fpos;           /** указатель файла на начало фрейма */

    /** header info */
    uint32_t prev_ref; // prev
    uint32_t next_ref; // next
    uint8_t   status_page;
    uint8_t   type_page;
    uint8_t   type_page_2;
    uint32_t  total_size_page;
    uint32_t  size_data_page;

    /** info page frame */
    struct VoidArray *data_list;
    
    void debug_print()
    {
        printf("--->> PAGE_FRAGMENT\n");
        printf("fpos: %u\n", fpos);
        printf("prev_ref: %u\n", prev_ref);
        printf("next_ref: %u\n", next_ref);
        printf("total_size_page: %u\n", total_size_page);
        printf("size_data_page:  %u\n", size_data_page);
        printf("----------------\n");
    }
    
    PAGE_FRAGMENT()
    {
        data_list = NULL;
    }
    
    ~PAGE_FRAGMENT()
    {
        printf("~PAGE_FRAGMENT\n");
        
        if( data_list != NULL )
        {
            VoidArray_free( data_list );
            data_list = NULL;
        }
    }
};

struct PAGE_FRAGMENT* __new_Page_Fragment();
void free_Page_Fragment(struct PAGE_FRAGMENT *pf);


#endif /* AH_API_COMMON_H */

