#ifndef AH_API_H_INCLUDED
#define AH_API_H_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <regex>

#include "ah_api_common.h"
#include "ah_page.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils/util_filesys.h"
#include "utils/util_string.h"
#include "utils/utils.h"

#include "cparser/shunting-yard.h"
#include "cparser/shunting-yard-exceptions.h"
#include "jspy/statements.h"

#include "TextTable.h"

using namespace std;

/** заголовок БД */
#define HEADER_FILE_TABLE      "AH_TABLE"
#define AH_API_VERSION         "0.1"

#define AHT_OK                             0x00
#define AHT_ERROR_OPEN_FILE_NOT_EXIST      0x01
#define AHT_ERROR_OPEN_FILE_ERROR          0x02
#define AHT_ERROR_OPEN_ERROR_READ_FORMAT   0x03


struct ResultPageWrite
{
    uint8_t init;
    uint32_t fpos_start_frame;
    int size_data_page;
};

class AHTables
{
    private:

        FILE *_file;
        string path;

        uint32_t curr_pos_file;  /** use only in memory */
        uint32_t _pos_refs;      /** позиция на данные ссылок списка */

        uint16_t count_tables;

        vector<TableInto*> tables;
        
        int status;
        
        void open(const char *path );

        void close();
        
        void save_pos_file();
        void restore_pos_file();
        
        void __set_refs(  
                  uint32_t _pos_first
                , uint32_t _pos_end
                , uint32_t _count
                , uint32_t index_table);
        
        void __save_curr_pos_file();
        
        
    public:
        
        void debug_print_struct_table(uint32_t index_table);
        void debug_print_struct_allTable();
    
        int tableExists(string name)
        {
            for(int i = 0; i < tables.size(); i++)
            {
                if( icasecmp(tables[i]->table_name, name) )
                {
                    return i;
                }
            }

            return -1;
        }

        TableInto* getTableByName(string name)
        {
            for(int i = 0; i < tables.size(); i++)
            {
                if( icasecmp(tables[i]->table_name, name) )
                {
                    return tables[i];
                }
            }

            return NULL;
        }
        
        static bool newTables(const char *path, vector<TableInto*> &list_tables);
        
        /**
            добавить страницу
        */
        struct ResultPageWrite addNewPage(    uint8_t status_page
                                            , uint8_t type_page
                                            , uint8_t type_page_2
                                            , struct VoidArray *data_list
                                            , uint32_t index_table );

        /**
         * rewrite_page_if_possible - перезапись страницы если новые данные входят в текущую страницу по размеру
         */
        struct ResultPageWrite editPageA(  struct PAGE_FRAGMENT *pf
                                                 , struct VoidArray *data_list
                                                 , bool rewrite_page_if_possible
                                                 , uint32_t index_table );

        /**
         * перезапись данных в том же фрейме (только для тех типов данных с фиксированным размером)
         */
        struct ResultPageWrite editPageB( struct PAGE_FRAGMENT *pf
                                        , struct VoidArray *data_list
                                        , vector<uint8_t> mask_edit
                                        , uint32_t index_table );

        void deletePage( struct PAGE_FRAGMENT *pf, uint32_t index_table );

        /**
         * чтение с указанной позиции
         */
        struct PAGE_FRAGMENT* readPageFpos(    uint32_t _fpos
                                            ,  vector<uint8_t> &mask_read
                                            ,  uint32_t index_table );

        struct PAGE_FRAGMENT* findFirstPage(  vector<uint8_t> &mask_read
                                            , uint32_t index_table );

        struct PAGE_FRAGMENT* findLastPage(   vector<uint8_t> &mask_read
                                            , uint32_t index_table );


        struct PAGE_FRAGMENT* findPrevPage(   struct PAGE_FRAGMENT *current_pf
                                            , vector<uint8_t> &mask_read
                                            , uint32_t index_table );

        struct PAGE_FRAGMENT* findNextPage(   struct PAGE_FRAGMENT *current_pf
                                            , vector<uint8_t> &mask_read
                                            , uint32_t index_table );

        uint32_t getCountPages(uint32_t index_table);


        int getIndexTableByName(char* name_table);

        void hook_freePage(struct PAGE_FRAGMENT *pf);
        
        static string getVersion();
        
        int readHeaderPage(  
                          uint32_t  *prev_ref
                        , uint32_t  *next_ref
                        , uint8_t   *status_page
                        , uint8_t   *type_page
                        , uint8_t   *type_page_2
                        , uint32_t  *total_size_page
                        , uint32_t  *size_data_page);
        
        int writePageA(
                          uint32_t prev_ref
                        , uint32_t next_ref
                        , uint8_t  status_page
                        , uint8_t  type_page
                        , uint8_t  type_page_2
                        , vector<InfoColum*> &mass_format
                        , struct VoidArray *data_list );
        
        int writePageB(   uint32_t prev_ref
                        , uint32_t next_ref
                        , uint8_t  status_page
                        , uint8_t  type_page
                        , uint8_t  type_page_2
                        , vector<InfoColum*> &mass_format
                        , struct VoidArray *data_list
                        , vector<uint8_t> mask_update );
    
        int getStatus() { return status; }
        
        string getPath() {
            return path;
        }
        
        AHTables() 
        {
            status = AHT_OK;
        }
        
        AHTables(const char *path)
        {
            status = AHT_OK;
            open(path);
        }

        ~AHTables()
        {
            close();
            
            for(int i = 0; i < tables.size(); i++)
            {
                if( tables[i] != NULL )
                {
                    delete tables[i];
                    tables[i] = NULL;
                }
            }
        }
};

void debug_print_sub_string_list(vector<SubStringInfo*> list);


#endif // AH_API_H_INCLUDED
