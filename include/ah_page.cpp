#include <vector>
#include <cmath>

#include "ah_page.h"
#include "ah_api.h"

///--------------------------------------------------------------------------------------
int _ah_page_check_mass_frormat__void_array(vector<InfoColum*> &mass_format, struct VoidArray *data_list)
{
    int i;
    if(mass_format.size() == 0 || data_list == NULL)
    { 
        printf("error check_mass_frormat__void_array: 1 %d %d\n", mass_format.size(), data_list == NULL);
        return -1;
    }

    if(mass_format.size() != data_list->len)
    { 
        printf("error check_mass_frormat__void_array: 2\n");
        return -1;
    }

    for(i=0; i < mass_format.size(); i++)
    {
        if( mass_format[i]->mayBeNull == true && data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
        {
            continue;
        }
        
        if( mass_format[i]->type == TYPE_COLUMN_STR && data_list->types_mass[i] != VOID_ARRAY_TYPE_STR)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_STR\n");
            return -1; 
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT8 && data_list->types_mass[i] != VOID_ARRAY_TYPE_INT8)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT8\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT8 && data_list->types_mass[i] != VOID_ARRAY_TYPE_UINT8)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT8\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT16 && data_list->types_mass[i] != VOID_ARRAY_TYPE_INT16)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT16\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT16 && data_list->types_mass[i] != VOID_ARRAY_TYPE_UINT16)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT16\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT32 && data_list->types_mass[i] != VOID_ARRAY_TYPE_INT32)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT32\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT32 && data_list->types_mass[i] != VOID_ARRAY_TYPE_UINT32)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT32\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT64 && data_list->types_mass[i] != VOID_ARRAY_TYPE_INT64)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT64\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT64 && data_list->types_mass[i] != VOID_ARRAY_TYPE_UINT64)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT64\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INTPTR && data_list->types_mass[i] != VOID_ARRAY_TYPE_INTPTR)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INTPTR\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINTPTR && data_list->types_mass[i] != VOID_ARRAY_TYPE_UINTPTR)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINTPTR\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_FLOAT && data_list->types_mass[i] != VOID_ARRAY_TYPE_FLOAT)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_FLOAT\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_DOUBLE && data_list->types_mass[i] != VOID_ARRAY_TYPE_DOUBLE)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_DOUBLE\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_BUFF && data_list->types_mass[i] != VOID_ARRAY_TYPE_BUFFER_DATA)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_BUFF\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR && data_list->types_mass[i] != VOID_ARRAY_TYPE_VCHAR)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_VCHAR\n");
            return -1;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR && mass_format[i]->prop_1 != ((struct VarChar*)data_list->mass[i])->const_len)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_VCHAR 2\n");
            return -1;
        }
    }

    return 0;
}
///--------------------------------------------------------------------------------------
int _ah_page_check_mass_frormat__void_array_2(vector<InfoColum*> &mass_format, struct VoidArray *data_list, vector<uint8_t> mask_update)
{
    int i = 0, k = 0;
    
    if(mass_format.size() == 0 || data_list == NULL)
    { 
        printf("error check_mass_frormat__void_array: 1 %d %d\n", mass_format.size(), data_list == NULL);
        return -1;
    }

    /*if(mass_format.size() != data_list->len)
    { 
        printf("error check_mass_frormat__void_array: 2\n");
        return -1;
    }*/
    
    if( mass_format.size() != mask_update.size() )
    {
        printf("error check_mass_frormat__void_array: 3\n");
        return -1;
    }

    for(i=0, k = 0; i < mass_format.size(); i++)
    {
        if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_STR && data_list->types_mass[k] != VOID_ARRAY_TYPE_STR)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_STR\n");
            return -1; 
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_INT8 && data_list->types_mass[k] != VOID_ARRAY_TYPE_INT8)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT8\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_UINT8 && data_list->types_mass[k] != VOID_ARRAY_TYPE_UINT8)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT8\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_INT16 && data_list->types_mass[k] != VOID_ARRAY_TYPE_INT16)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT16\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_UINT16 && data_list->types_mass[k] != VOID_ARRAY_TYPE_UINT16)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT16\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_INT32 && data_list->types_mass[k] != VOID_ARRAY_TYPE_INT32)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT32\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_UINT32 && data_list->types_mass[k] != VOID_ARRAY_TYPE_UINT32)
        {
            for(int p = 0; p < mass_format.size(); p++)
            {
                mass_format[p]->debug_print();
            }
            
            printf("\n");
            
            for(int p = 0; p < mask_update.size(); p++)
            {
                printf("%d ", mask_update[p]);
            }
            
            printf("\n");
            
            debug_void_array_print(data_list);
            
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT32 %d %d %d %d %d\n"
                    , i
                    , k - 1
                    , mass_format.size()
                    , data_list->len
                    , mask_update.size()
                    );
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_INT64 && data_list->types_mass[k] != VOID_ARRAY_TYPE_INT64)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INT64\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_UINT64 && data_list->types_mass[k] != VOID_ARRAY_TYPE_UINT64)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINT64\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_INTPTR && data_list->types_mass[k] != VOID_ARRAY_TYPE_INTPTR)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_INTPTR\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_UINTPTR && data_list->types_mass[k] != VOID_ARRAY_TYPE_UINTPTR)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_UINTPTR\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_FLOAT && data_list->types_mass[k] != VOID_ARRAY_TYPE_FLOAT)
        { 
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_FLOAT\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_DOUBLE && data_list->types_mass[k] != VOID_ARRAY_TYPE_DOUBLE)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_DOUBLE\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_BUFF && data_list->types_mass[k] != VOID_ARRAY_TYPE_BUFFER_DATA)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_BUFF\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_VCHAR && data_list->types_mass[k] != VOID_ARRAY_TYPE_VCHAR)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_VCHAR\n");
            return -1;
        }
        else if( mask_update[i] == 1 && mass_format[i]->type == TYPE_COLUMN_VCHAR && mass_format[i]->prop_1 != ((struct VarChar*)data_list->mass[k])->const_len)
        {
            printf("error check_mass_frormat__void_array: TYPE_COLUMN_VCHAR 2\n");
            return -1;
        }
        
        if( mask_update[i] == 1 )
        {
            k += 1;
        }
    }

    return 0;
}
///---------------------------------------------------------------------------------
int AHTables::writePageA(    
                               uint32_t prev_ref
                             , uint32_t next_ref
                             , uint8_t status_page
                             , uint8_t type_page
                             , uint8_t type_page_2
                             , vector<InfoColum*> &mass_format
                             , struct VoidArray *data_list )
{
    int i;
    int8_t null_flag;
    int8_t   *int8;
    uint8_t  *uint8;
    int16_t  *int16;
    uint16_t *uint16;
    int32_t  *int32;
    uint32_t *uint32, tlen;
    int64_t  *int64;
    uint64_t *uint64;
    intptr_t *intptr;
    uintptr_t *uintptr;
    float    *_float;
    double   *_double;
    void *data = NULL;
    uint32_t _size_page;
    char _first_tok = '|', _end_tok = '*';

    int _page_fragment_size = PAGE_FRAGMENT_SIZE;
    int _need_add_zero = 0;
    uint8_t _zero = 0;
    // check data list

    if( _ah_page_check_mass_frormat__void_array(mass_format, data_list) != 0)
    {
        printf("!! error format void array !! page_a\n");
        return -1; 
    }

    // calculate all size write page ----------------
    _size_page = 0;

    for(i=0; i < mass_format.size(); i++)
    {
        _size_page += 1; // null flag: 1 - is null; 0 - not null
        
        if( data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
        {
            continue;
        }
        
        //printf("> %s\n", mass_format->mass[i]);
        if( mass_format[i]->type == TYPE_COLUMN_STR )
        {
            data = data_list->mass[i];

            _size_page += sizeof(uint32_t);
            _size_page += strlen( (char*)data );
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT8 )
        {
            _size_page += sizeof(int8_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT8 )
        {
            _size_page += sizeof(uint8_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT16 )
        {
            _size_page += sizeof(int16_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT16 )
        {
            _size_page += sizeof(uint16_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT32 )
        {
            _size_page += sizeof(int32_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT32 )
        {
            _size_page += sizeof(uint32_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT64 )
        {
            _size_page += sizeof(int64_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT64 )
        {
            _size_page += sizeof(uint64_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INTPTR )
        {
             _size_page += sizeof(intptr_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINTPTR )
        {
             _size_page += sizeof(uintptr_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_FLOAT )
        {
            _size_page += sizeof(float);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_DOUBLE )
        {
            _size_page += sizeof(double);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_BUFF )
        {
            data = data_list->mass[i];
            _size_page += sizeof(uint32_t);
            _size_page += (uint32_t)( ((struct buf*)data)->len );
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR )
        {
            data = data_list->mass[i];
            _size_page += sizeof(uint16_t);
            _size_page += mass_format[i]->prop_1;

            //printf("mass_format->vhcar_size[i]: %d\n", mass_format->vhcar_size[i]);
        }
    }

    printf("_size_page: %d\n", _size_page);

    while( _size_page > _page_fragment_size )
    { _page_fragment_size += PAGE_FRAGMENT_SIZE; }

    _need_add_zero = _page_fragment_size - _size_page;

    //printf("_need_add_zero: %d\n", _need_add_zero);

    //printf("\n---------------------------\ncount_write: ");
    // write header page ----------------
    size_t count_write;
    count_write = fwrite(&_first_tok,            1,                  1, _file); //printf("%u ", count_write);
    count_write = fwrite(&prev_ref,              sizeof(uint32_t),   1, _file); //printf("%u ", count_write);
    count_write = fwrite(&next_ref,              sizeof(uint32_t),   1, _file); //printf("%u ", count_write);
    count_write = fwrite(&status_page,           sizeof(uint8_t),    1, _file); //printf("%u ", count_write);
    count_write = fwrite(&type_page,             sizeof(uint8_t),    1, _file); //printf("%u ", count_write);
    count_write = fwrite(&type_page_2,           sizeof(uint8_t),    1, _file); //printf("%u ", count_write);
    count_write = fwrite(&_page_fragment_size,   sizeof(uint32_t),   1, _file); //printf("%u ", count_write);
    count_write = fwrite(&_size_page,            sizeof(uint32_t),   1, _file); //printf("%u ", count_write);
    
    //printf("\n");
    // write - body page
    // -----------------------------------------------------------------------------

    for(i=0; i < mass_format.size(); i++)
    {
        null_flag = 0;
        
        if( data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL )
        {
            null_flag = 1;
            fwrite(&null_flag, 1, 1, _file);
            continue;
        }
        
        fwrite(&null_flag, 1, 1, _file);
        
        //printf("> %s\n", mass_format->mass[i]);
        if( mass_format[i]->type == TYPE_COLUMN_STR )
        {
            data    = data_list->mass[i];

            tlen = (uint32_t)strlen( (char*)data );

            //printf("[%u][%s]\n", tlen, (char*)data);
            //printf("%p\n%p\n", data, &tlen);
            
            fwrite(&tlen, sizeof(uint32_t), 1, _file);
            fwrite((char*)data, 1, tlen, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT8 )
        {
            int8 = (int8_t *)data_list->mass[i];

            fwrite(int8, sizeof(int8_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT8 )
        {
            uint8 = (uint8_t *)data_list->mass[i];

            fwrite(uint8, sizeof(uint8_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT16 )
        {
            int16 = (int16_t *)data_list->mass[i];

            fwrite(int16, sizeof(int16_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT16 )
        {
            uint16 = (uint16_t *)data_list->mass[i];

            fwrite(uint16, sizeof(uint16_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT32 )
        {
            int32 = (int32_t *)data_list->mass[i];

            fwrite(int32, sizeof(int32_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT32 )
        {
            uint32 = (uint32_t *)data_list->mass[i];

            fwrite(uint32, sizeof(uint32_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT64 )
        {
            int64 = (int64_t *)data_list->mass[i];

            fwrite(int64, sizeof(int64_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT64 )
        {
            uint64 = (uint64_t *)data_list->mass[i];

            fwrite(uint64, sizeof(uint64_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INTPTR )
        {
            intptr = (intptr_t *)data_list->mass[i];

            fwrite(intptr, sizeof(intptr_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINTPTR )
        {
            uintptr = (uintptr_t *)data_list->mass[i];

            fwrite(uintptr, sizeof(uintptr_t), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_FLOAT )
        {
            _float = (float *)data_list->mass[i];

            fwrite(_float, sizeof(float), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_DOUBLE )
        {
            _double = (double *)data_list->mass[i];

            fwrite(_double, sizeof(double), 1, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_BUFF )
        {
            data = data_list->mass[i];

            tlen = (uint32_t)( ( (struct buf*)data)->len);

            fwrite(&tlen, sizeof(uint32_t), 1, _file);
            fwrite((char*)((struct buf*)data)->ptr, 1, tlen, _file);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR )
        {
            data = data_list->mass[i];

            tlen = mass_format[i]->prop_1;

            fwrite(&tlen, sizeof(uint16_t), 1, _file);

            fwrite( (char*) ( (struct VarChar*)data)->data->ptr, 1, tlen, _file);
        }
    }

    // --- FILL ZERO -----------------------------------------------------
    fwrite(&_zero, sizeof(uint8_t),    _need_add_zero, _file);
    // -------------------------------------------------------------------
    fwrite(&_end_tok, 1, 1, _file); /// токен окончания страницы = '*'

    return _size_page;
}
///--------------------------------------------------------------------------------------
int AHTables::writePageB(    uint32_t prev_ref
                             , uint32_t next_ref
                             , uint8_t status_page
                             , uint8_t type_page
                             , uint8_t type_page_2
                             , vector<InfoColum*> &mass_format
                             , struct VoidArray *data_list
                             , vector<uint8_t> mask_update )
{
    int i, k;
    int8_t   *int8;
    uint8_t  *uint8;
    int16_t  *int16;
    uint16_t *uint16;
    int32_t  *int32;
    uint32_t *uint32, tlen;
    int64_t  *int64;
    uint64_t *uint64;
    intptr_t *intptr;
    uintptr_t *uintptr;
    float    *_float;
    double   *_double;
    void *data = NULL;
    //uint32_t _size_page;
    //char _first_tok = '|', _end_tok = '*';

    //int _page_fragment_size = PAGE_FRAGMENT_SIZE;
    //int _need_add_zero = 0;
    //uint8_t _zero = 0;
    // check data list

    if(
           mask_update.size() != mass_format.size()
        || std::count(mask_update.begin(), mask_update.end(), 1) != data_list->len
      )
    { 
        printf("!! mask_update count !! %d %d\n", std::count(mask_update.begin(), mask_update.end(), 1), data_list->len);
        return -1;
    }
    
    if( _ah_page_check_mass_frormat__void_array_2(mass_format, data_list, mask_update) != 0)
    { 
        printf("!! error format void array !! page_b\n");
        return -1; 
    }
    
    for(int i = 0; i < data_list->len; i++)
    {
        if(    data_list->types_mass[i] == VOID_ARRAY_TYPE_STR 
            || data_list->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA
            || data_list->types_mass[i] == VOID_ARRAY_TYPE_NULL
          )
        {
            return -1;
        }
    }
    // skip header page ----------------
    fseek(_file, 1 + 4 * sizeof(uint32_t) + 3 * sizeof(uint8_t), SEEK_CUR); // skip
    
    // write - body page
    // -----------------------------------------------------------------------------

    for(i=0, k=0; i < mass_format.size(); i++)
    {
        fseek(_file, 1, SEEK_CUR); // skip null flag
        
        //printf("> %s\n", mass_format->mass[i]);
        if( mass_format[i]->type == TYPE_COLUMN_STR )
        {
            fread(&tlen, sizeof(uint32_t), 1, _file);
            fseek(_file, tlen, SEEK_CUR); // skip
            
            /*data    = data_list->mass[i];

            tlen = (uint32_t)strlen( (char*)data );

            //printf("[%u][%s]\n", tlen, (char*)data);
            //printf("%p\n%p\n", data, &tlen);

            fwrite(&tlen, sizeof(uint32_t), 1, f);
            fwrite((char*)data, 1, tlen, f);*/
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT8 )
        {
            if( mask_update[i] )
            {
                int8 = (int8_t *)data_list->mass[k]; 
                k += 1;

                fwrite(int8, sizeof(int8_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(int8_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT8 )
        {
            if( mask_update[i] )
            {
                uint8 = (uint8_t *)data_list->mass[k];
                k += 1;

                fwrite(uint8, sizeof(uint8_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(uint8_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT16 )
        {
            if( mask_update[i] )
            {
                int16 = (int16_t *)data_list->mass[k];
                k += 1;

                fwrite(int16, sizeof(int16_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(int16_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT16 )
        {
            if( mask_update[i] )
            {
                uint16 = (uint16_t *)data_list->mass[k];
                k += 1;

                fwrite(uint16, sizeof(uint16_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(uint16_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT32 )
        {
            if( mask_update[i] )
            {
                int32 = (int32_t *)data_list->mass[k];
                k += 1;

                fwrite(int32, sizeof(int32_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(int32_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT32 )
        {
            if( mask_update[i] )
            {
                uint32 = (uint32_t *)data_list->mass[k];
                k += 1;

                fwrite(uint32, sizeof(uint32_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(uint32_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT64 )
        {
            if( mask_update[i] )
            {
                int64 = (int64_t *)data_list->mass[k];
                k += 1;

                fwrite(int64, sizeof(int64_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(int64_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT64 )
        {
            if( mask_update[i] )
            {
                uint64 = (uint64_t *)data_list->mass[k];
                k += 1;

                fwrite(uint64, sizeof(uint64_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(uint64_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INTPTR )
        {
            if( mask_update[i] )
            {
                intptr = (intptr_t *)data_list->mass[k];
                k += 1;

                fwrite(intptr, sizeof(intptr_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(intptr_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINTPTR )
        {
            if( mask_update[i] )
            {
                uintptr = (uintptr_t *)data_list->mass[k];
                k += 1;

                fwrite(uintptr, sizeof(uintptr_t), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(uintptr_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_FLOAT )
        {
            if( mask_update[i] )
            {
                _float = (float *)data_list->mass[k];
                k += 1;

                fwrite(_float, sizeof(float), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(float), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_DOUBLE )
        {
            if( mask_update[i] )
            {
                _double = (double *)data_list->mass[k];
                k += 1;

                fwrite(_double, sizeof(double), 1, _file);
            }
            else
            {
                fseek(_file, sizeof(double), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type == TYPE_COLUMN_BUFF )
        {
            fread(&tlen, sizeof(uint32_t), 1, _file);
            fseek(_file, tlen, SEEK_CUR); // skip
            
            /*data = data_list->mass[i];

            tlen = (uint32_t)( ( (struct buf*)data)->len);

            fwrite(&tlen, sizeof(uint32_t), 1, f);
            fwrite((char*)((struct buf*)data)->ptr, 1, tlen, f);*/
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR )
        {
            if( mask_update[i] )
            {
                data = data_list->mass[i];

                tlen = mass_format[i]->prop_1;

                fwrite(&tlen, sizeof(uint16_t), 1, _file);

                fwrite( (char*) ( (struct VarChar*)data)->data->ptr, 1, tlen, _file);
            }
            else
            {
                fread(&tlen, sizeof(uint16_t), 1, _file);
                fseek(_file, tlen, SEEK_CUR); // skip
            }
        }
    }

    // --- FILL ZERO -----------------------------------------------------
    //fwrite(&_zero, sizeof(uint8_t),    _need_add_zero, f);
    // -------------------------------------------------------------------
    //fwrite(&_end_tok, 1, 1, f); /// токен окончания страницы = '*'
    
    fseek(_file, 2, SEEK_CUR); // skip
    
    return 1;
}

int _ah_page_calculate_size_page_data(   vector<InfoColum*> &mass_format
                                       , struct VoidArray *data_list )
{
    int i = 0, _size_page = 0;
    void *data = NULL;

    if( _ah_page_check_mass_frormat__void_array(mass_format, data_list) != 0)
    { return -1; }

    for(i=0; i < mass_format.size(); i++)
    {
        _size_page += 1;
        
        if( mass_format[i]->type == TYPE_COLUMN_STR )
        {
            data = data_list->mass[i];

            _size_page += sizeof(uint32_t);
            _size_page += strlen( (char*)data );
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT8 )
        {
            _size_page += sizeof(int8_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT8 )
        {
            _size_page += sizeof(uint8_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT16 )
        {
            _size_page += sizeof(int16_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT16 )
        {
            _size_page += sizeof(uint16_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT32 )
        {
            _size_page += sizeof(int32_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT32 )
        {
            _size_page += sizeof(uint32_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT64 )
        {
            _size_page += sizeof(int64_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT64 )
        {
            _size_page += sizeof(uint64_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INTPTR )
        {
             _size_page += sizeof(intptr_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINTPTR )
        {
             _size_page += sizeof(uintptr_t);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_FLOAT )
        {
            _size_page += sizeof(float);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_DOUBLE )
        {
            _size_page += sizeof(double);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_BUFF )
        {
            data = data_list->mass[i];
            _size_page += sizeof(uint32_t);
            _size_page += (uint32_t)( ((struct buf*)data)->len );
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR )
        {
            data = data_list->mass[i];
            _size_page += sizeof(uint16_t);
            _size_page += mass_format[i]->type;
        }
    }

    return _size_page;
}

///--------------------------------------------------------------------------------------------------
int AHTables::readHeaderPage(  
                                uint32_t  *prev_ref
                              , uint32_t  *next_ref
                              , uint8_t   *status_page
                              , uint8_t   *type_page
                              , uint8_t   *type_page_2
                              , uint32_t  *total_size_page
                              , uint32_t  *size_data_page)
{
    char _first_tok = ' ';

    if(_file == NULL)
    {
        printf("file == NULL - %d", __LINE__);
        return false;
    }

    // read header page
    fread(&_first_tok, 1, 1, _file);

    //printf("_first_tok: '%c'\n", _first_tok);

    if(_first_tok != '|')
    {
        return false;
    }

    fread(prev_ref,         sizeof(uint32_t),  1, _file);
    fread(next_ref,         sizeof(uint32_t),  1, _file);
    fread(status_page,      sizeof(uint8_t),   1, _file);
    fread(type_page,        sizeof(uint8_t),   1, _file);
    fread(type_page_2,      sizeof(uint8_t),   1, _file);
    fread(total_size_page,  sizeof(uint32_t),  1, _file);
    fread(size_data_page,   sizeof(uint32_t),  1, _file);

    return true;
}
///--------------------------------------------------------------------------------------------------
int _ah_page_read_header_page_1( FILE *f, uint32_t *prev_ref, uint32_t *next_ref )
{
    char _first_tok = ' ';

    if(f == NULL)
    {
        printf("file == NULL - %d", __LINE__);
        return false;
    }

    // read header page
    fread(&_first_tok, 1, 1, f);

    //printf("_first_tok: %c\n", _first_tok);

    if(!(_first_tok == '|'))
    {
        return false;
    }

    fread(prev_ref,         sizeof(uint32_t), 1, f);
    fread(next_ref,         sizeof(uint32_t), 1, f);

    return true;
}
///-----------------------------------------------------------------------------
void _ah_page_read_from_format_a(  FILE *f
                                 , vector<InfoColum*> &mass_format
                                 , struct VoidArray **data_list_res )
{
    int i;
    int8_t null_flag;
    int8_t   int8;
    uint8_t  uint8;
    int16_t  int16;
    uint16_t uint16;
    int32_t  int32;
    uint32_t uint32, len;
    int64_t  int64;
    uint64_t  uint64;
    intptr_t  intptr;
    uintptr_t uintptr;
    float    _float;
    double   _double;
    char *_str;
    struct buf *b;
    //struct VarChar *vchar;
    unsigned char *tmp_buffer;

    /*if(data_list != NULL)
    { VoidArray_free(data_list); }*/

    struct VoidArray *data_list = VoidArray_init();

    for(i=0; i < mass_format.size(); i++)
    {
        fread(&null_flag, 1, 1, f);
        
        if( null_flag == 1 )
        {
            printf("read null\n");
            VoidArray_addNULL(data_list);
            continue;
        }
        
        //printf("> %s\n", mass_format->mass[i]);
        if( mass_format[i]->type == TYPE_COLUMN_STR )
        {
            fread(&len, sizeof(uint32_t), 1, f);

            _str = (char *) malloc( (size_t)len + 1 );

            fread(_str, 1, (size_t)len, f);

            _str[(unsigned int)len] = '\0';

            VoidArray_addStr(data_list, _str);

            free(_str);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT8 )
        {
            fread(&int8, sizeof(int8_t), 1, f);

            VoidArray_addInt8(data_list, int8);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT8 )
        {
            fread(&uint8, sizeof(uint8_t), 1, f);

            VoidArray_addUInt8(data_list, uint8);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT16 )
        {
            fread(&int16, sizeof(int16_t), 1, f);

            VoidArray_addInt16(data_list, int16);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT16 )
        {
            fread(&uint16, sizeof(uint16_t), 1, f);

            VoidArray_addUInt16(data_list, uint16);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT32 )
        {
            fread(&int32, sizeof(int32_t), 1, f);

            VoidArray_addInt32(data_list, int32);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT32 )
        {
            fread(&uint32, sizeof(uint32_t), 1, f);

            VoidArray_addUInt32(data_list, uint32);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INT64 )
        {
            fread(&int64, sizeof(int64_t), 1, f);

            VoidArray_addInt64(data_list, int64);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINT64 )
        {
            fread(&uint64, sizeof(uint64_t), 1, f);

            VoidArray_addUInt64(data_list, uint64);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_INTPTR )
        {
            fread(&intptr, sizeof(intptr_t), 1, f);

            VoidArray_addUIntPtr(data_list, intptr);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_UINTPTR )
        {
            fread(&uintptr, sizeof(uintptr_t), 1, f);

            VoidArray_addUIntPtr(data_list, uintptr);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_FLOAT )
        {
            fread(&_float, sizeof(float), 1, f);

            VoidArray_addFloat(data_list, _float);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_DOUBLE )
        {
            fread(&_double, sizeof(double), 1, f);

            VoidArray_addDouble(data_list, _double);
        }
        else if( mass_format[i]->type == TYPE_COLUMN_BUFF )
        {
            b = (struct buf*) buf_new();

            fread(&len, sizeof(uint32_t), 1, f);

            tmp_buffer = (unsigned char *) malloc( (size_t)len );

            fread(tmp_buffer, 1, (size_t)len, f);

            buf_append_data(b, tmp_buffer, len);

            VoidArray_addBufferData(data_list, b);

            free(tmp_buffer);
            tmp_buffer = NULL;
        }
        else if( mass_format[i]->type == TYPE_COLUMN_VCHAR )
        {
            fread(&len, sizeof(uint16_t), 1, f);

            tmp_buffer = (unsigned char *) malloc( (size_t)len + 1 );

            fread(tmp_buffer, 1, (size_t)len, f);

            tmp_buffer[ len ] = '\0';

            VoidArray_addVChar(data_list, (char *)tmp_buffer, len);

            free(tmp_buffer);
            tmp_buffer = NULL;
        }
    }

    *data_list_res = data_list;
}


/// ------------------------------------------------------------------------------
void _ah_page_read_from_format_b(  FILE *f
                                 , vector<InfoColum*> &mass_format
                                 , struct VoidArray **data_list_res
                                 , vector<uint8_t> &mask_read )
{
    int i;
    int8_t     null_flag;
    int8_t     int8;
    uint8_t    uint8;
    int16_t    int16;
    uint16_t   uint16;
    int32_t    int32;
    uint32_t   uint32,  len;
    int64_t    int64;
    uint64_t   uint64;
    intptr_t   intptr;
    uintptr_t  uintptr;
    float      _float;
    double     _double;
    char *_str;
    struct buf* b;
    unsigned char *tmp_buffer;

    if(
           mask_read.size() == 0
        || mask_read.size() != mass_format.size()
      )
    { return; }

    /*if(data_list != NULL)
    { VoidArray_free(data_list); }*/

    struct VoidArray *data_list = VoidArray_init();

    for(i=0; i < mass_format.size(); i++)
    {
        fread(&null_flag, 1, 1, f);
        
        if( null_flag == 1 )
        {
            if( mask_read[i] )
            {
                printf("- read null\n");
                VoidArray_addNULL(data_list);
            }
            continue;
        }
        
        //printf("> %s\n", mass_format->mass[i]);
        if( mass_format[i]->type ==  TYPE_COLUMN_STR )
        {
            if( mask_read[i] )
            {
                fread(&len, sizeof(uint32_t), 1, f);

                _str = (char *) malloc( (size_t)len + 1 );

                fread(_str, 1, (size_t)len, f);

                _str[(unsigned int)len] = '\0';

                VoidArray_addStr(data_list, _str);

                free(_str);
            }
            else
            {
                fread(&len, sizeof(uint32_t), 1, f);

                fseek(f, len, SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_INT8 )
        {
            if( mask_read[i] )
            {
                fread(&int8, sizeof(int8_t), 1, f);

                VoidArray_addInt8(data_list, int8);
            }
            else
            {
                fseek(f, sizeof(int8_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_UINT8 )
        {
            if( mask_read[i] )
            {
                fread(&uint8, sizeof(uint8_t), 1, f);

                VoidArray_addUInt8(data_list, uint8);
            }
            else
            {
                fseek(f, sizeof(uint8_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_INT16 )
        {
            if( mask_read[i] )
            {
                fread(&int16, sizeof(int16_t), 1, f);

                VoidArray_addInt16(data_list, int16);
            }
            else
            {
                fseek(f, sizeof(int16_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_UINT16 )
        {
            if( mask_read[i] )
            {
                fread(&uint16, sizeof(uint16_t), 1, f);

                VoidArray_addUInt16(data_list, uint16);
            }
            else
            {
                fseek(f, sizeof(uint16_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_INT32 )
        {
            if( mask_read[i] )
            {
                fread(&int32, sizeof(int32_t), 1, f);

                VoidArray_addInt32(data_list, int32);
            }
            else
            {
                fseek(f, sizeof(int32_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_UINT32 )
        {
            if( mask_read[i] )
            {
                fread(&uint32, sizeof(uint32_t), 1, f);

                VoidArray_addUInt32(data_list, uint32);
            }
            else
            {
                fseek(f, sizeof(uint32_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_INT64 )
        {
            if( mask_read[i] )
            {
                fread(&int64, sizeof(int64_t), 1, f);

                VoidArray_addInt64(data_list, int64);
            }
            else
            {
                fseek(f, sizeof(int64_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_UINT64 )
        {
            if( mask_read[i] )
            {
                fread(&uint64, sizeof(uint64_t), 1, f);

                VoidArray_addUInt64(data_list, uint64);
            }
            else
            {
                fseek(f, sizeof(uint64_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_INTPTR )
        {
            if( mask_read[i] )
            {
                fread(&intptr, sizeof(intptr_t), 1, f);

                VoidArray_addUIntPtr(data_list, intptr);
            }
            else
            {
                fseek(f, sizeof(intptr_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_UINTPTR )
        {
            if( mask_read[i] )
            {
                fread(&uintptr, sizeof(uintptr_t), 1, f);

                VoidArray_addUIntPtr(data_list, uintptr);
            }
            else
            {
                fseek(f, sizeof(uintptr_t), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_FLOAT )
        {
            if( mask_read[i] )
            {
                fread(&_float, sizeof(float), 1, f);

                VoidArray_addFloat(data_list, _float);
            }
            else
            {
                fseek(f, sizeof(float), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_DOUBLE )
        {
            if( mask_read[i] )
            {
                fread(&_double, sizeof(double), 1, f);

                VoidArray_addDouble(data_list, _double);
            }
            else
            {
                fseek(f, sizeof(double), SEEK_CUR); // skip
            }
        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_BUFF )
        {
            if( mask_read[i] )
            {
                b = (struct buf*) buf_new();

                fread(&len, sizeof(uint32_t), 1, f);

                tmp_buffer = (unsigned char *) malloc( (size_t)len );

                fread(tmp_buffer, 1, (size_t)len, f);

                buf_append_data(b, tmp_buffer, len);

                VoidArray_addBufferData(data_list, b);

                free(tmp_buffer);
                tmp_buffer = NULL;
            }
            else
            {
                fread(&len, sizeof(uint32_t), 1, f);

                fseek(f, len, SEEK_CUR); // skip
            }

        }
        else if( mass_format[i]->type ==  TYPE_COLUMN_VCHAR )
        {
            if( mask_read[i] )
            {
                fread(&len, sizeof(uint16_t), 1, f);

                tmp_buffer = (unsigned char *) malloc( (size_t)len + 1 );

                fread(tmp_buffer, 1, (size_t)len, f);

                tmp_buffer[ len ] = '\0';

                VoidArray_addVChar(data_list, (char *)tmp_buffer, len);

                free(tmp_buffer);
                tmp_buffer = NULL;
            }
            else
            {
                fread(&len, sizeof(uint16_t), 1, f);

                fseek(f, len, SEEK_CUR); // skip
            }
        }
    }

    *data_list_res = data_list;
}
///--------------------------------------------------------------------------------------
void __set_page_prev_ref(FILE *f, uint32_t fpos, uint32_t prev_ref)
{
    fseek(f, fpos, SEEK_SET);

    fseek(f, sizeof(char), SEEK_CUR);
    fwrite(&prev_ref,    sizeof(uint32_t),  1, f);
}
///--------------------------------------------------------------------------------------
void __set_page_next_ref(FILE *f, uint32_t fpos, uint32_t next_ref)
{
    fseek(f, fpos, SEEK_SET);

    fseek(f, sizeof(char) + sizeof(uint32_t), SEEK_CUR);
    fwrite(&next_ref,    sizeof(uint32_t),  1, f);
}
///--------------------------------------------------------------------------------------
void __set_status_page(FILE *f, uint32_t fpos, uint8_t value)
{
    fseek(f, fpos, SEEK_SET);

    fseek(f, sizeof(char) + sizeof(uint32_t) + sizeof(uint32_t), SEEK_CUR);
    fwrite(&value,    sizeof(uint8_t),  1, f);
}
