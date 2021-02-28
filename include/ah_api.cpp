#include "ah_api.h"


/// ------------------------------------------------------------------------------------
/// обновление ссылок на данные в заголовке таблицы
void AHTables::__set_refs(  
                  uint32_t _pos_first
                , uint32_t _pos_end
                , uint32_t _count
                , uint32_t index_table)
{
    // _pos_refs - сохраненная позиция для быстрого перехода в места записи данных
    fseek(_file, _pos_refs, SEEK_SET);

    printf("ftell: %ld %d\n", ftell(_file), index_table );

    fseek(_file, ( sizeof(uint32_t) * 3 ) * index_table, SEEK_CUR );

    //printf("ftell: %d %d\n", ftell(t->f), index_table );

    fwrite(&_pos_first, sizeof(uint32_t), 1, _file);
    fwrite(&_pos_end,   sizeof(uint32_t), 1, _file);
    fwrite(&_count,     sizeof(uint32_t), 1, _file);

    tables[ index_table ]->pos_first  = _pos_first;
    tables[ index_table ]->pos_end    = _pos_end;
    tables[ index_table ]->count      = _count;

    /*printf("pos_first: \t%u\n", tables[ index_table ]->pos_first);
    printf("pos_end: \t%u\n", tables[ index_table ]->pos_end);
    printf("count: \t\t%u\n", tables[ index_table ]->count);*/
}

/// ----------------------------------------------------------------------------
void AHTables::__save_curr_pos_file()
{
    curr_pos_file = ftell(_file);
}

void __writeInFileString(FILE *f, string s)
{
    uint16_t len = s.length();
    
    fwrite(&len, 1, sizeof(uint16_t), f);
    fwrite(s.c_str(), 1, len, f);
}

string __readInFileString(FILE *f)
{
    string result;
    uint16_t len;
    unsigned char *_byff;
    
    fread(&len, sizeof(uint16_t), 1, f);

    _byff = (unsigned char *)calloc( sizeof(char), len + 1 );

    fread(_byff, len, 1, f);

    result = (char*)_byff;

    free(_byff);
    _byff = NULL;
    
    return result;
}

///=============================================================================
string AHTables::getVersion()
{
    return AH_API_VERSION;
}
///=============================================================================
bool AHTables::newTables(const char *path, vector<TableInto*> &list_tables)
{
    FILE *f;

    for(int i = 0; i < list_tables.size(); i++)
    {
        if(    list_tables[i]->columns.size() == 0
            || list_tables[i]->table_name.length() == 0
          )
        {
            printf("error ah_api_new_base: %d\n", __LINE__);
            return false;
        }
    }

    if(file_exists(path))
    {
        printf("error ah_api_new_base: %d\n", __LINE__);
        return false;
    }

    f = fopen(path, "w+b");
    if(f == NULL)
    {
        printf("error ah_api_new_base: %d\n", __LINE__);
        return false;
    }

    int r = fwrite(HEADER_FILE_TABLE, 1, sizeof(HEADER_FILE_TABLE), f);

    if( r != sizeof(HEADER_FILE_TABLE) )
    {
        printf("error ah_api_new_base: %d\n", __LINE__);
        return false;
    }

    uint16_t count = list_tables.size();
    fwrite(&count, 1, sizeof(uint16_t), f);
    
    for(int i = 0; i < list_tables.size(); i++)
    {
        uint32_t ref = 0;
        
        fwrite(&ref, 1, sizeof(uint32_t), f);  // pos_first
        fwrite(&ref, 1, sizeof(uint32_t), f);  // pos_end
        fwrite(&ref, 1, sizeof(uint32_t), f);  // count
    }
    
    for(int i = 0; i < list_tables.size(); i++)
    {
        __writeInFileString(f, list_tables[i]->table_name);
        
        count = list_tables[i]->columns.size();
        fwrite(&count, 1, sizeof(uint16_t), f);

        for(int j = 0; j < count; j++)
        {
            __writeInFileString(f, list_tables[i]->columns[j]->name);
            
            fwrite(&list_tables[i]->columns[j]->type, 1, sizeof(uint8_t), f);
            fwrite(&list_tables[i]->columns[j]->mayBeNull, 1, sizeof(uint8_t), f);
            
            if( list_tables[i]->columns[j]->type == TYPE_COLUMN_VCHAR )
            {
                fwrite(&list_tables[i]->columns[j]->prop_1, 2, sizeof(uint16_t), f);
            }
        }
    }

    fclose(f);

    return true;
}
///=============================================================================
void AHTables::open(const char *_path)
{
    char str_head_id[ sizeof(HEADER_FILE_TABLE) + 1 ] = "";

    if(! file_exists(_path))
    {
        status = AHT_ERROR_OPEN_FILE_NOT_EXIST;
        return;
    }
    else
    {
        _file = fopen(_path, "r+b");
        
        if(_file == NULL)
        {
            status = AHT_ERROR_OPEN_FILE_ERROR;
            return;
        }
    }

    // reset pos
    fseek(_file, 0, SEEK_SET);

    int r = fread(str_head_id, 1, sizeof(HEADER_FILE_TABLE), _file);

    //printf("str_head_id: %s %d == %d %d\n", str_head_id, r, sizeof(HEADER_FILE_TABLE) , strcmp( HEADER_FILE_TABLE, str_head_id ));

    if(
           r != sizeof(HEADER_FILE_TABLE)
       ||  strcmp( HEADER_FILE_TABLE, str_head_id ) != 0
      )
    {
        status = AHT_ERROR_OPEN_ERROR_READ_FORMAT;
        return;
    }

    if(strcmp(str_head_id, HEADER_FILE_TABLE) != 0)
    {
        status = AHT_ERROR_OPEN_ERROR_READ_FORMAT;
        return;
    }

    path   = _path;

    fread(&count_tables, sizeof(uint16_t), 1, _file);

    //printf("ah_api_open_db -> count_tables: %d\n", count_tables);

    _pos_refs = ftell(_file);

    for(int i = 0; i < count_tables; i++)
    {
        TableInto* ti = new TableInto();
        ti->index = i;
        
        fread(&ti->pos_first, sizeof(uint32_t), 1, _file);
        fread(&ti->pos_end,   sizeof(uint32_t), 1, _file);
        fread(&ti->count,     sizeof(uint32_t), 1, _file);

        /*printf("+pos_first: \t%u\n", ti->pos_first);
        printf("+pos_end:   \t%u\n", ti->pos_end);
        printf("+count:     \t%u\n", ti->count);*/
        
        tables.push_back(ti);
    }

    for(int i = 0; i < count_tables; i++)
    {
        tables[i]->table_name = __readInFileString(_file);
        
        uint16_t count_columns;
        fread(&count_columns, sizeof(uint16_t), 1, _file);

        for(int j = 0; j < count_columns; j++)
        {
            InfoColum* ic   = new InfoColum();
            ic->name        = __readInFileString(_file);
            ic->index       = j;
            ic->index_table = tables[i]->index;

            fread(&ic->type, sizeof(uint8_t), 1, _file);
            fread(&ic->mayBeNull, sizeof(uint8_t), 1, _file);

            if(ic->type == TYPE_COLUMN_VCHAR)
            {
                fread(&ic->prop_1, sizeof(uint16_t), 2, _file);
            }

            tables[i]->columns.push_back(ic);
        }
    }
    
    //fseek(f, result->pos_first, SEEK_SET);
    
    for(int i = 0; i < tables.size(); i++)
    {
        tables[i]->debug_print();
    }
    
    return;
}
///=============================================================================
void AHTables::save_pos_file()
{
    curr_pos_file = ftell(_file);
}
///=============================================================================
void AHTables::restore_pos_file()
{
    fseek(_file, curr_pos_file, SEEK_SET);
}
///=============================================================================
void AHTables::close()
{
    fclose(_file);
    _file = NULL;
}
///=============================================================================
struct PAGE_FRAGMENT* AHTables::findFirstPage(  vector<uint8_t> &mask_read
                                             , uint32_t index_table )
{
    struct PAGE_FRAGMENT *result = NULL;

    if(
          tables[index_table]->pos_first != 0
       && tables[index_table]->pos_end != 0
       && tables[index_table]->count != 0
      )
    {
        result = readPageFpos(  tables[index_table]->pos_first
                                       , mask_read
                                       , index_table );
    }

    return result;
}
///=============================================================================
struct PAGE_FRAGMENT* AHTables::findLastPage(   vector<uint8_t> &mask_read
                                             , uint32_t index_table )
{
    struct PAGE_FRAGMENT *result = NULL;

    if(
          tables[index_table]->pos_first != 0
       && tables[index_table]->pos_end != 0
       && tables[index_table]->count != 0
      )
    {
        result = readPageFpos(  tables[index_table]->pos_end
                                       , mask_read
                                       , index_table );
    }

    return result;
}
///=============================================================================
struct PAGE_FRAGMENT* AHTables::findPrevPage(   
                                               struct PAGE_FRAGMENT *current_pf
                                             , vector<uint8_t> &mask_read
                                             , uint32_t index_table )
{
    struct PAGE_FRAGMENT *result = NULL;

    if(current_pf == NULL || current_pf->prev_ref == 0)
    { return result; }

    result = readPageFpos(  current_pf->prev_ref
                                   , mask_read
                                   , index_table);

    return result;
}
///=============================================================================
struct PAGE_FRAGMENT* AHTables::findNextPage( 
                                               struct PAGE_FRAGMENT *current_pf
                                             , vector<uint8_t> &mask_read
                                             , uint32_t index_table )
{
    struct PAGE_FRAGMENT *result = NULL;

    if(current_pf == NULL || current_pf->next_ref == 0)
    { return result; }

    result = readPageFpos(  current_pf->next_ref
                                   , mask_read
                                   , index_table );

    return result;
}
///=============================================================================
struct PAGE_FRAGMENT* AHTables::readPageFpos( 
                                              uint32_t _fpos
                                            , vector<uint8_t> &mask_read
                                            , uint32_t index_table )
{
    struct PAGE_FRAGMENT *result = NULL;
    uint32_t   fpos;
    uint32_t   prev_ref          = 0; // prev
    uint32_t   next_ref          = 0; // next
    uint8_t    status_page       = 0;
    uint8_t    type_page         = 0;
    uint8_t    type_page_2       = 0;
    uint32_t   total_size_page   = 0;
    uint32_t   size_data_page    = 0;
    int        result_read_page  = 0;

    if( mask_read.size() > 0 && mask_read.size() != tables[index_table]->columns.size() )
    {
        printf("len_mask error len - %d\n", __LINE__);
        return NULL;
    }

    //printf("_fpos: %ld\n", _fpos);
    
    fseek(_file, _fpos, SEEK_SET);

    fpos = _fpos;

    result_read_page = readHeaderPage(  &prev_ref
                                                 , &next_ref
                                                 , &status_page
                                                 , &type_page
                                                 , &type_page_2
                                                 , &total_size_page
                                                 , &size_data_page );

    if( ! result_read_page
       && status_page != AH_PAGE_STATUS_USED )
    {
        printf("result_read_page == %d - %d\n", result_read_page, __LINE__);
        return NULL;
    }

    result = __new_Page_Fragment();

    result->fpos = fpos;

    result->prev_ref           = prev_ref;
    result->next_ref           = next_ref;
    result->status_page        = status_page;
    result->type_page          = type_page;
    result->type_page_2        = type_page_2;
    result->total_size_page    = total_size_page;
    result->size_data_page     = size_data_page;

    if(mask_read.size() == 0)
    {
        _ah_page_read_from_format_a(  _file
                                    , tables[index_table]->columns
                                    , &result->data_list );
    }
    else if( mask_read.size() == tables[index_table]->columns.size() )
    {
        _ah_page_read_from_format_b(  _file
                                    , tables[index_table]->columns
                                    , &result->data_list
                                    , mask_read );
    }

    return result;
}
///=============================================================================
struct ResultPageWrite AHTables::addNewPage(  
                                             uint8_t status_page
                                           , uint8_t type_page
                                           , uint8_t type_page_2
                                           , struct VoidArray *data_list
                                           , uint32_t index_table )
{
    struct ResultPageWrite result;
    uint32_t file_end_pos, prev_pos;

    result.init = 0;
    
    /// это первая страница в списке?
    if(
               tables[index_table]->pos_first == 0
            && tables[index_table]->pos_end == 0
            && tables[index_table]->count == 0
      )
    {
        fseek(_file, 0, SEEK_END);
        file_end_pos = ftell(_file);

        printf("ftell_1: %ld\n", ftell(_file) );
        printf("write first page!\n");

        __set_refs(file_end_pos, file_end_pos, 1, index_table);

        fseek(_file, file_end_pos, SEEK_SET);

        result.fpos_start_frame = ftell(_file);
        result.size_data_page   = writePageA(    0
                                                           , 0
                                                           , status_page
                                                           , type_page    // type 1
                                                           , type_page_2  // type 2
                                                           , tables[index_table]->columns
                                                           , data_list );
    }
    else
    {
        fseek(_file, 0, SEEK_END);
        file_end_pos = ftell(_file);

        prev_pos = tables[index_table]->pos_end;

        __set_refs(tables[index_table]->pos_first, file_end_pos, tables[index_table]->count + 1, index_table );

        if(prev_pos > 0)
        {
            __set_page_next_ref(_file, prev_pos, file_end_pos);
        }

        fseek(_file, file_end_pos, SEEK_SET);

        printf("ftell_2: %ld\n", ftell(_file) );

        debug_void_array_print( data_list );

        result.fpos_start_frame = ftell(_file);
        result.size_data_page   = writePageA(    prev_pos
                                                           , 0
                                                           , status_page
                                                           , type_page      // type 1
                                                           , type_page_2    // type 2
                                                           , tables[index_table]->columns
                                                           , data_list);
    }

    result.init = 1;
    return result;
}
///=============================================================================
void AHTables::deletePage( struct PAGE_FRAGMENT *pf, uint32_t index_table)
{
    fseek(_file, pf->fpos, SEEK_SET);

    if(
               pf->prev_ref == 0
            && pf->next_ref == 0
          )
    {
        this->hook_freePage(pf);
        
        __set_status_page(_file, pf->fpos, AH_PAGE_STATUS_UNUSED);

        __set_refs(0, 0, 0, index_table);
    }
    else if(
               pf->prev_ref == 0
            && pf->next_ref != 0
          )
    {
        this->hook_freePage(pf);
        
        __set_status_page(_file, pf->fpos, AH_PAGE_STATUS_UNUSED);

        __set_page_prev_ref(_file, pf->next_ref, 0);

        __set_refs(pf->next_ref, tables[index_table]->pos_end, tables[index_table]->count - 1, index_table);
    }
    else if(
               pf->prev_ref != 0
            && pf->next_ref == 0
          )
    {
        this->hook_freePage(pf);
        
        __set_status_page(_file, pf->fpos, AH_PAGE_STATUS_UNUSED);

        __set_page_next_ref(_file, pf->prev_ref, 0);

        __set_refs(tables[index_table]->pos_first, pf->prev_ref, 0, index_table);
    }
    else if(
               pf->prev_ref != 0
            && pf->next_ref != 0
          )
    {
        hook_freePage(pf);
        
        __set_status_page(_file, pf->fpos, AH_PAGE_STATUS_UNUSED);

        __set_page_next_ref(_file, pf->prev_ref, pf->next_ref);

        __set_page_prev_ref(_file, pf->next_ref, pf->prev_ref);

        __set_refs(tables[index_table]->pos_first, tables[index_table]->pos_end, tables[index_table]->count - 1, index_table);
    }
}
///=============================================================================
struct ResultPageWrite AHTables::editPageA(   
                                           struct PAGE_FRAGMENT *pf
                                         , struct VoidArray *data_list
                                         , bool rewrite_page_if_possible
                                         , uint32_t index_table )
{
    uint8_t have_null_in_data_list = 0;
    int i = 0;
    uint32_t _fpos = 0;

    struct ResultPageWrite result;
    struct VoidArray *data_list_res = NULL;
    
    int new_size_page = 0;
    
    result.init = 0;
    
    if( data_list == NULL || data_list->len != tables[index_table]->columns.size() )
    {
        return result;
    }
    
    //debug_void_array_print( data_list );
    
    for(i = 0; i < data_list->len; i++)
    {
        if( data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
        {
            have_null_in_data_list = 1;
            break;
        }
    }
    
    if( have_null_in_data_list == 1 )
    {
        fseek(_file, pf->fpos + 20, SEEK_SET);
        
        _ah_page_read_from_format_a( _file, tables[index_table]->columns, &data_list_res );
        
        //debug_void_array_print( data_list_res );
        
        for(i = 0; i < data_list->len; i++)
        {
            if( data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
            {
                data_list->mass[i]       = data_list_res->mass[i];
                data_list->types_mass[i] = data_list_res->types_mass[i];
                
                data_list_res->mass[i]       = NULL;
                data_list_res->types_mass[i] = VOID_ARRAY_TYPE_NULL;
            }
        }
        
        //debug_void_array_print( data_list );
    }
    
    //return result;
    
    new_size_page = _ah_page_calculate_size_page_data( tables[index_table]->columns, data_list );

    //printf("pf->total_size_page: %d\n", pf->total_size_page);
    //printf("new_size_page: %d\n", new_size_page);

    /// размер текущей страницы меньше чем новой?
    if(     rewrite_page_if_possible
         && pf->total_size_page >= new_size_page
      )
    {
        printf("- overwrite page ------\n");

        fseek(_file, pf->fpos, SEEK_SET);

        result.fpos_start_frame = ftell(_file);
        result.size_data_page   = writePageA(    pf->prev_ref
                                                           , pf->next_ref
                                                           , AH_PAGE_STATUS_USED
                                                           , pf->type_page        // type 1
                                                           , pf->type_page_2      // type 2
                                                           , tables[index_table]->columns
                                                           , data_list);
    }
    else   // remove current page
    {
        printf("- edit add new page ------\n");
        //fseek(t->f, pf->fpos, SEEK_SET);
        
        hook_freePage(pf);

        __set_status_page(_file, pf->fpos, AH_PAGE_STATUS_UNUSED);

        fseek(_file, 0, SEEK_END);
        _fpos = ftell(_file);

        if( pf->prev_ref > 0 )
        {
            __set_page_next_ref(_file, pf->prev_ref, _fpos);
        }

        if( pf->next_ref > 0 )
        {
            __set_page_prev_ref(_file, pf->next_ref, _fpos);
        }

        if( tables[index_table]->pos_first == pf->fpos )
        {
            tables[index_table]->pos_first = _fpos;
            __set_refs(_fpos, tables[index_table]->pos_end, tables[index_table]->count, index_table);
        }

        if( tables[index_table]->pos_end == pf->fpos )
        {
            tables[index_table]->pos_end = _fpos;
            __set_refs(tables[index_table]->pos_first, _fpos, tables[index_table]->count, index_table);
        }
        
        // update current_frame
        fseek(_file, 0, SEEK_END);
        pf->fpos = _fpos;

        result.fpos_start_frame = ftell(_file);
        result.size_data_page   = writePageA(    pf->prev_ref
                                                           , pf->next_ref
                                                           , AH_PAGE_STATUS_USED
                                                           , pf->type_page        // type 1
                                                           , pf->type_page_2      // type 2
                                                           , tables[index_table]->columns
                                                           , data_list );
    }

    VoidArray_free( data_list_res );
    
    return result;
}
///=============================================================================
struct ResultPageWrite AHTables::editPageB(   
                                           struct PAGE_FRAGMENT *pf
                                         , struct VoidArray *data_list
                                         , vector<uint8_t> mask_edit
                                         , uint32_t index_table )
{
    uint8_t have_null_in_data_list = 0;
    int i = 0;
    uint32_t _fpos = 0;

    struct ResultPageWrite result;
    struct VoidArray *data_list_res = NULL;
    
    int new_size_page = 0;
    
    result.init = 0;
    
    //debug_void_array_print( data_list );
    
    for(i = 0; i < data_list->len; i++)
    {
        if( data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
        {
            have_null_in_data_list = 1;
            break;
        }
    }
    
    if( have_null_in_data_list == 1 )
    {
        fseek(_file, pf->fpos + 20, SEEK_SET);
        
        _ah_page_read_from_format_a( _file, tables[index_table]->columns, &data_list_res );
        
        //debug_void_array_print( data_list_res );
        
        for(i = 0; i < data_list->len; i++)
        {
            if( data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
            {
                data_list->mass[i]       = data_list_res->mass[i];
                data_list->types_mass[i] = data_list_res->types_mass[i];
                
                data_list_res->mass[i]       = NULL;
                data_list_res->types_mass[i] = VOID_ARRAY_TYPE_NULL;
            }
        }
        
        //debug_void_array_print( data_list );
    }
    //return result;
    
    printf("- overwrite page ------\n");

    fseek(_file, pf->fpos, SEEK_SET);

    result.fpos_start_frame = ftell(_file);
    result.size_data_page   = writePageB(    pf->prev_ref
                                                       , pf->next_ref
                                                       , AH_PAGE_STATUS_USED
                                                       , pf->type_page        // type 1
                                                       , pf->type_page_2      // type 2
                                                       , tables[index_table]->columns
                                                       , data_list
                                                       , mask_edit );

    VoidArray_free( data_list_res );
    return result;
}
///=============================================================================
uint32_t AHTables::getCountPages(uint32_t index_table)
{
    return tables[index_table]->count;
}
///=============================================================================
void AHTables::hook_freePage(struct PAGE_FRAGMENT *pf)
{
    
}
///=============================================================================
int AHTables::getIndexTableByName(char* name_table)
{
    for(int i = 0; i < count_tables; i++)
    {
        if( icasecmp( tables[i]->table_name.c_str(), name_table ) )
        {
            return i;
        }
    }
    
    return -1;
}
///=============================================================================
void AHTables::debug_print_struct_table(uint32_t index_table)
{
    printf("----------------\n");
    printf("table: %s\n", tables[index_table]->table_name.c_str());
    printf("pos_first: \t%u\n", tables[index_table]->pos_first);
    printf("pos_end: \t%u\n", tables[index_table]->pos_end);
    printf("count: \t\t%u\n", tables[index_table]->count);
    printf("----------------\n");
    
    tables[index_table]->debug_print();
}

void AHTables::debug_print_struct_allTable()
{
    for(int i = 0; i < tables.size(); i++)
    {
        debug_print_struct_table(i);
    }
}

void debug_print_sub_string_list(vector<SubStringInfo*> list)
{
    printf("debug_print_sub_string_list: %d\n", list.size());
    
    for(int i = 0; i < list.size(); i++)
    {
        printf("[%s] = '%s'\n", list[i]->find_token.c_str(), list[i]->value.c_str());
    }
}