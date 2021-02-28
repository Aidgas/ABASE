#include "void_array.h"

static void *reallocf(void* ptr, size_t size)
{
    void *newptr = realloc(ptr, size);
    if (NULL == newptr && ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }

    return newptr;
}

struct VoidArray *VoidArray_init()
{
    struct VoidArray *res = (struct VoidArray *) malloc( sizeof(struct VoidArray) );

    if(res == NULL)
    { return NULL; }

    res->len  = 0;
    res->mass = NULL;
    res->types_mass = NULL;

    return res;
}


void VoidArray_free( struct VoidArray *v )
{
    if(v == NULL)
    { return; }

    if(v->mass != NULL)
    {
        int i;
        for(i = 0; i < v->len; i++)
        {
            if( v->mass[i] == NULL )
            {
                continue;
            }
            
            if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
            {
                struct buf* buf = (struct buf*) v->mass[i];

                buf_free(buf);
            }
            else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
            {
                struct VarChar *vchar = (struct VarChar *) v->mass[i];

                if(vchar == NULL)
                {
                    printf("---NULL 52-\n");
                }

                buf_free(vchar->data);
                vchar->data = NULL;
            }

            free(v->mass[i]);
            v->mass[i] = NULL;
        }

        free(v->mass);
    }

    free(v->types_mass);

    free(v);
    v = NULL;
}

void VoidArray_deleteItem(struct VoidArray *v, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index && v->mass[i] != NULL )
        {
            if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
            {
                struct buf* buf = (struct buf *) v->mass[i];
                buf_free(buf);
            }
            else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
            {
                struct VarChar *vchar = (struct VarChar *) v->mass[i];

                if(vchar == NULL)
                {
                    printf("---NULL 52-\n");
                }

                buf_free(vchar->data);
                vchar->data = NULL;
            }

            free(v->mass[i]);
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_NULL;
            v->mass[i] = NULL;
        }
    }
}

int VoidArray_setInt8(struct VoidArray *v, int8_t int8, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            int8_t *ptr_int8 = (int8_t *) malloc( sizeof(int8_t) );
            
            if(ptr_int8 == NULL)
            { return 1; }
            
            *ptr_int8 = int8;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_INT8;
            v->mass[i] = ptr_int8;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addInt8(struct VoidArray *v, int8_t int8)
{
    int8_t *ptr_int8 = NULL;

    v->mass        = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass  = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_INT8;

    ptr_int8 = (int8_t *) malloc( sizeof(int8_t) );

    if(ptr_int8 == NULL)
    { return 1; }

    *ptr_int8 = int8;

    v->mass[ v->len ] = ptr_int8;
    v->len += 1;

    return 0;
}

int VoidArray_setUInt8(struct VoidArray *v, uint8_t uint8, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            uint8_t *ptr_uint8 = (uint8_t *) malloc( sizeof(uint8_t) );
            
            if(ptr_uint8 == NULL)
            { return 1; }
            
            *ptr_uint8 = uint8;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_UINT8;
            v->mass[i] = ptr_uint8;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addUInt8(struct VoidArray *v, uint8_t uint8)
{
    uint8_t *ptr_uint8 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );
    
    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_UINT8;

    ptr_uint8 = (uint8_t *) malloc( sizeof(uint8_t) );

    if(ptr_uint8 == NULL)
    { return 1; }

    *ptr_uint8 = uint8;

    v->mass[ v->len ] = ptr_uint8;
    v->len += 1;

    return 0;
}

int VoidArray_setInt16(struct VoidArray *v, int16_t int16, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            int16_t *ptr_int16 = (int16_t *) malloc( sizeof(int16_t) );
            
            if(ptr_int16 == NULL)
            { return 1; }
            
            *ptr_int16 = int16;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_INT16;
            v->mass[i] = ptr_int16;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addInt16(struct VoidArray *v, int16_t int16)
{
    int16_t *ptr_int16 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_INT16;

    ptr_int16 = (int16_t *) malloc( sizeof(int16_t) );

    if(ptr_int16 == NULL)
    { return 1; }

    *ptr_int16 = int16;

    v->mass[ v->len ] = ptr_int16;
    v->len += 1;

    return 0;
}

int VoidArray_setUInt16(struct VoidArray *v, uint16_t uint16, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            uint16_t *ptr_uint16 = (uint16_t *) malloc( sizeof(uint16_t) );
            
            if(ptr_uint16 == NULL)
            { return 1; }
            
            *ptr_uint16 = uint16;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_UINT16;
            v->mass[i] = ptr_uint16;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addUInt16(struct VoidArray *v, uint16_t uint16)
{
    uint16_t *ptr_uint16 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_UINT16;

    ptr_uint16 = (uint16_t *) malloc( sizeof(uint16_t) );

    if(ptr_uint16 == NULL)
    { return 1; }

    *ptr_uint16 = uint16;

    v->mass[ v->len ] = ptr_uint16;
    v->len += 1;

    return 0;
}

int VoidArray_setInt32(struct VoidArray *v, int32_t int32, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            int32_t *ptr_int32 = (int32_t *) malloc( sizeof(int32_t) );
            
            if(ptr_int32 == NULL)
            { return 1; }
            
            *ptr_int32 = int32;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_INT32;
            v->mass[i] = ptr_int32;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addInt32(struct VoidArray *v, int32_t int32)
{
    int32_t *ptr_int32 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_INT32;

    ptr_int32 = (int32_t *) malloc( sizeof(int32_t) );

    if(ptr_int32 == NULL)
    { return 1; }

    *ptr_int32 = int32;

    v->mass[ v->len ] = ptr_int32;
    v->len += 1;

    return 0;
}

int VoidArray_setUInt32(struct VoidArray *v, uint32_t uint32, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            uint32_t *ptr_uint32 = (uint32_t *) malloc( sizeof(uint32_t) );
            
            if(ptr_uint32 == NULL)
            { return 1; }
            
            *ptr_uint32 = uint32;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_UINT32;
            v->mass[i] = ptr_uint32;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addUInt32(struct VoidArray *v, uint32_t uint32)
{
    uint32_t *ptr_uint32 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_UINT32;

    ptr_uint32 = (uint32_t *) malloc( sizeof(uint32_t) );

    if(ptr_uint32 == NULL)
    { return 1; }

    *ptr_uint32 = uint32;

    v->mass[ v->len ] = ptr_uint32;
    v->len += 1;

    return 0;
}

int VoidArray_setInt64(struct VoidArray *v, int64_t int64, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            int64_t *ptr_int64 = (int64_t *) malloc( sizeof(int64_t) );
            
            if(ptr_int64 == NULL)
            { return 1; }
            
            *ptr_int64 = int64;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_INT64;
            v->mass[i] = ptr_int64;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addInt64(struct VoidArray *v, int64_t int64)
{
    int64_t *ptr_int64 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_INT64;

    ptr_int64 = (int64_t *) malloc( sizeof(int64_t) );

    if(ptr_int64 == NULL)
    { return 1; }

    *ptr_int64 = int64;

    v->mass[ v->len ] = ptr_int64;
    v->len += 1;

    return 0;
}

int VoidArray_setUInt64(struct VoidArray *v, uint64_t uint64, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            uint64_t *ptr_uint64 = (uint64_t *) malloc( sizeof(uint64_t) );
            
            if(ptr_uint64 == NULL)
            { return 1; }
            
            *ptr_uint64 = uint64;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_UINT64;
            v->mass[i] = ptr_uint64;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addUInt64(struct VoidArray *v, uint64_t uint64)
{
    uint64_t *ptr_uint64 = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_UINT64;

    ptr_uint64 = (uint64_t *) malloc( sizeof(uint64_t) );

    if(ptr_uint64 == NULL)
    { return 1; }

    *ptr_uint64 = uint64;

    v->mass[ v->len ] = ptr_uint64;
    v->len += 1;

    return 0;
}

int VoidArray_setIntPtr(struct VoidArray *v, intptr_t intptr, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            intptr_t *ptr_intptr = (intptr_t *) malloc( sizeof(intptr_t) );
            
            if(ptr_intptr == NULL)
            { return 1; }
            
            *ptr_intptr = intptr;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_INTPTR;
            v->mass[i] = ptr_intptr;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addIntPtr(struct VoidArray *v, intptr_t intptr)
{
    intptr_t *ptr_intptr = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_INTPTR;

    ptr_intptr = (intptr_t *) malloc( sizeof(intptr_t) );

    if(ptr_intptr == NULL)
    { return 1; }

    *ptr_intptr = intptr;

    v->mass[ v->len ] = ptr_intptr;
    v->len += 1;

    return 0;
}

int VoidArray_setUIntPtr(struct VoidArray *v, uintptr_t uintptr, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            uintptr_t *ptr_uintptr = (uintptr_t *) malloc( sizeof(uintptr_t) );
            
            if(ptr_uintptr == NULL)
            { return 1; }
            
            *ptr_uintptr = uintptr;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_UINTPTR;
            v->mass[i] = ptr_uintptr;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addUIntPtr(struct VoidArray *v, uintptr_t uintptr)
{
    uintptr_t *ptr_uintptr = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_UINTPTR;

    ptr_uintptr = (uintptr_t *) malloc( sizeof(uintptr_t) );

    if(ptr_uintptr == NULL)
    { return 1; }

    *ptr_uintptr = uintptr;

    v->mass[ v->len ] = ptr_uintptr;
    v->len += 1;

    return 0;
}

int VoidArray_setFloat(struct VoidArray *v, float _float, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            float *f = (float *) malloc( sizeof(float) );
            
            if(f == NULL)
            { return 1; }
            
            *f = _float;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_FLOAT;
            v->mass[i] = f;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addFloat(struct VoidArray *v, float _float)
{
    float *f = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_FLOAT;

    f = (float *) malloc( sizeof(float) );

    if(f == NULL)
    { return 1; }

    *f = _float;

    v->mass[ v->len ] = f;
    v->len += 1;

    return 0;
}

int VoidArray_setDouble(struct VoidArray *v, double _double, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            double *d = (double *) malloc( sizeof(double) );
            
            if(d == NULL)
            { return 1; }
            
            *d = _double;
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_DOUBLE;
            v->mass[i] = d;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addDouble(struct VoidArray *v, double _double)
{
    double *d = NULL;

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_DOUBLE;

    d = (double *) malloc( sizeof(double) );

    if(d == NULL)
    { return 1; }

    *d = _double;

    v->mass[ v->len ] = d;
    v->len += 1;

    return 0;
}

int VoidArray_setStr(struct VoidArray *v, char* _str, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            int len_str_add = strlen(_str);
            char *tmp_str = (char *) calloc( len_str_add + 1, sizeof(char) );
            
            if(tmp_str == NULL)
            { return 1; }
            
            memcpy(tmp_str, _str, len_str_add);
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_STR;
            v->mass[i] = tmp_str;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addStr(struct VoidArray *v, char* _str)
{
    char *tmp_str;
    int len_str_add = strlen(_str);

    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_STR;

    tmp_str = (char *) calloc( len_str_add + 1, sizeof(char) );

    if(tmp_str == NULL)
    { return 1; }

    memcpy(tmp_str, _str, len_str_add);

    tmp_str[ len_str_add ] = '\0';

    v->mass[ v->len ] = tmp_str;
    v->len += 1;

    return 0;
}

int VoidArray_setBufferData(struct VoidArray *v, struct buf* bd, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_BUFFER_DATA;
            v->mass[i] = bd;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addBufferData(struct VoidArray *v, struct buf* bd)
{
    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    if(v->mass == NULL || v->types_mass == NULL)
    { return 1; }

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_BUFFER_DATA;

    v->mass[ v->len ] = bd;
    v->len += 1;

    return 0;
}

int VoidArray_setVChar(struct VoidArray *v, char* _str, unsigned int const_len, int index)
{
    int i = 0, copy_length = 0, len_zero_add = 0, let_str = strlen(_str);
    
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            struct VarChar *vchar = 0;
            if( let_str > const_len )
            {
                copy_length = const_len;
            }
            else
            {
                copy_length = let_str;

                len_zero_add = const_len - copy_length;
            }

            vchar = (struct VarChar *)malloc( sizeof(struct VarChar) );

            vchar->const_len = const_len;
            vchar->data      = (struct buf*) buf_new();

            buf_extend(vchar->data, copy_length);

            buf_append_data(vchar->data, _str, copy_length );

            for(i = 0; i < len_zero_add; i++)
            {
                buf_append_u8(vchar->data, 0);
            }
            
            v->types_mass[ i ] = VOID_ARRAY_TYPE_VCHAR;
            v->mass[i] = vchar;
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addVChar(struct VoidArray *v, char* _str, unsigned int const_len)
{
    struct VarChar *vchar = 0;
    int i = 0, copy_length = 0, len_zero_add = 0, let_str = strlen(_str);

    v->mass         =  (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   =  (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    if(v->mass == NULL || v->types_mass == NULL)
    { return 1; }

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_VCHAR;

    if( let_str > const_len )
    {
        copy_length = const_len;
    }
    else
    {
        copy_length = let_str;

        len_zero_add = const_len - copy_length;
    }

    vchar = (struct VarChar *)malloc( sizeof(struct VarChar) );

    vchar->const_len = const_len;
    vchar->data      = (struct buf*) buf_new();

    buf_extend(vchar->data, copy_length);

    buf_append_data(vchar->data, _str, copy_length );

    for(i = 0; i < len_zero_add; i++)
    {
        buf_append_u8(vchar->data, 0);
    }

    v->mass[ v->len ] = vchar;
    v->len += 1;

    return 0;
}

int VoidArray_setNULL(struct VoidArray *v, int index)
{
    int i = 0;
    for(i =0; i < v->len; i++)
    {
        if( i == index )
        {
            VoidArray_deleteItem(v, i);
            
            break;
        }
    }
    
    return 0;
}

int VoidArray_addNULL(struct VoidArray *v)
{
    v->mass         = (void **) reallocf( v->mass, (v->len + 1) * sizeof(void *) );
    v->types_mass   = (uint8_t *) reallocf(v->types_mass, (v->len + 1) * sizeof(uint8_t) );

    if(v->mass == NULL || v->types_mass == NULL)
    { return 1; }

    v->types_mass[ v->len ] = VOID_ARRAY_TYPE_NULL;

    v->mass[ v->len ] = NULL;
    v->len += 1;

    return 0;
}

void debug_void_array_print(struct VoidArray *v)
{
    int i = 0;

    printf("printf VoidArray: \n");

    if( v == NULL )
    {
        printf("printf VoidArray NULL\n");
        return;
    }

    for(i =0; i < v->len; i++)
    {
        if( v->types_mass[i] == VOID_ARRAY_TYPE_INT8)
        {
            int8_t *p = (int8_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_INT8: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT8)
        {
            uint8_t *p = (uint8_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_UINT8: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT16)
        {
            int16_t *p = (int16_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_INT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT16)
        {
            uint16_t *p = (uint16_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_UINT16: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT32)
        {
            int32_t *p = (int32_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_INT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT32)
        {
            uint32_t *p = (uint32_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_UINT32: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INT64)
        {
            int64_t *p = (int64_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_INT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINT64)
        {
            uint64_t *p = (uint64_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_UINT64: %lld\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_INTPTR)
        {
            intptr_t *p = (intptr_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_INTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_UINTPTR)
        {
            uintptr_t *p = (uintptr_t *) v->mass[i];
            printf("VOID_ARRAY_TYPE_UINTPTR: %d\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_DOUBLE)
        {
            double *p = (double *) v->mass[i];
            printf("VOID_ARRAY_TYPE_DOUBLE: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_FLOAT)
        {
            float *p = (float *) v->mass[i];
            printf("VOID_ARRAY_TYPE_FLOAT: %7.7f\n", *p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_STR)
        {
            char *p = (char *) v->mass[i];
            printf("VOID_ARRAY_TYPE_STR: %d %s\n", strlen(p), p);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
        {
            struct buf* p = (struct buf*) v->mass[i];
            printf("VOID_ARRAY_TYPE_BUFFER_DATA: %d\n", p->len);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
        {
            struct VarChar *p = (struct VarChar*) v->mass[i];
            printf("VOID_ARRAY_TYPE_BUFFER_VCHAR: %d %s\n", p->const_len, p->data->ptr);
        }
        else if( v->types_mass[i] == VOID_ARRAY_TYPE_NULL)
        {
            printf("VOID_ARRAY_TYPE_NULL\n");
        }
    }

    printf("----------------\n");
}


int8_t* VoidArray_getInt8(struct VoidArray *v, int index)
{
    int8_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_INT8)
    {
        result = (int8_t*) v->mass[index];
    }
    
    return result;
}

uint8_t* VoidArray_getUInt8(struct VoidArray *v, int index)
{
    uint8_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_UINT8)
    {
        result = (uint8_t*) v->mass[index];
    }
    
    return result;
}

int16_t* VoidArray_getInt16(struct VoidArray *v, int index)
{
    int16_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_INT16)
    {
        result = (int16_t*) v->mass[index];
    }
    
    return result;
}

uint16_t* VoidArray_getUInt16(struct VoidArray *v, int index)
{
    uint16_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_UINT16)
    {
        result = (uint16_t*) v->mass[index];
    }
    
    return result;
}

int32_t* VoidArray_getInt32(struct VoidArray *v, int index)
{
    int32_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_INT32)
    {
        result = (int32_t*) v->mass[index];
    }
    
    return result;
}

uint32_t* VoidArray_getUInt32(struct VoidArray *v, int index)
{
    uint32_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_UINT32)
    {
        result = (uint32_t*) v->mass[index];
    }
    
    return result;
}

int64_t* VoidArray_getInt64(struct VoidArray *v, int index)
{
    int64_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_INT64)
    {
        result = (int64_t*) v->mass[index];
    }
    
    return result;
}

uint64_t* VoidArray_getUInt64(struct VoidArray *v, int index)
{
    uint64_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_UINT64)
    {
        result = (uint64_t*) v->mass[index];
    }
    
    return result;
}

intptr_t* VoidArray_getIntPtr(struct VoidArray *v, int index)
{
    intptr_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_INTPTR)
    {
        result = (intptr_t*) v->mass[index];
    }
    
    return result;
}

uintptr_t* VoidArray_getUIntPtr(struct VoidArray *v, int index)
{
    uintptr_t* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_UINTPTR)
    {
        result = (uintptr_t*) v->mass[index];
    }
    
    return result;
}

float* VoidArray_getFloat(struct VoidArray *v, int index)
{
    float* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_FLOAT)
    {
        result = (float*) v->mass[index];
    }
    
    return result;
}

double* VoidArray_getDouble(struct VoidArray *v, int index)
{
    double* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_FLOAT)
    {
        result = (double*) v->mass[index];
    }
    
    return result;
}

char* VoidArray_getString(struct VoidArray *v, int index)
{
    char* result = NULL;

    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_STR)
    {
        result = (char*) v->mass[index];
    }
    
    return result;
}

struct buf* VoidArray_getBinaryBuffer(struct VoidArray *v, int index)
{
    struct buf* result = NULL;
    
    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_BUFFER_DATA)
    {
        result = (struct buf*) v->mass[index];
    }
    
    return result;
}

struct VarChar* VoidArray_getVarChar(struct VoidArray *v, int index)
{
    struct VarChar* result = NULL;
    
    if( index >= 0 && index < v->len && v->types_mass[index] == VOID_ARRAY_TYPE_VCHAR)
    {
        result = (struct VarChar*) v->mass[index];
    }
    
    return result;
}

int VoidArray_isNULL(struct VoidArray *v, int index)
{
    int result = 0;
    
    if(    index >= 0 
        && index < v->len 
        && v->types_mass[index] == VOID_ARRAY_TYPE_NULL
        && v->mass[index] == NULL
      )
    {
        result = 1;
    }
    
    return result;
}

//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
void VoidArray_append(struct VoidArray *dest, struct VoidArray *src)
{
    for(int i =0; i < src->len; i++)
    {
        if( src->types_mass[i] == VOID_ARRAY_TYPE_INT8)
        {
            int8_t *p = (int8_t *) src->mass[i];

            VoidArray_addInt8(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_UINT8)
        {
            uint8_t *p = (uint8_t *) src->mass[i];

            VoidArray_addUInt8(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_INT16)
        {
            int16_t *p = (int16_t *) src->mass[i];

            VoidArray_addInt16(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_UINT16)
        {
            uint16_t *p = (uint16_t *) src->mass[i];

            VoidArray_addUInt16(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_INT32)
        {
            int32_t *p = (int32_t *) src->mass[i];

            VoidArray_addInt32(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_UINT32)
        {
            uint32_t *p = (uint32_t *) src->mass[i];

            VoidArray_addUInt32(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_INT64)
        {
            int64_t *p = (int64_t *) src->mass[i];

            VoidArray_addInt64(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_UINT64)
        {
            uint64_t *p = (uint64_t *) src->mass[i];

            VoidArray_addUInt64(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_INTPTR)
        {
            intptr_t *p = (intptr_t *) src->mass[i];

            VoidArray_addIntPtr(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_UINTPTR)
        {
            uintptr_t *p = (uintptr_t *) src->mass[i];

            VoidArray_addUIntPtr(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_DOUBLE)
        {
            double *p = (double *) src->mass[i];

            VoidArray_addDouble(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_FLOAT)
        {
            float *p = (float *) src->mass[i];

            VoidArray_addFloat(dest, *p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_STR)
        {
            char *p = (char *) src->mass[i];

            VoidArray_addStr(dest, p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_BUFFER_DATA)
        {
            struct buf* p = (struct buf*) src->mass[i];

            VoidArray_addBufferData(dest, p);
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_VCHAR)
        {
            struct VarChar *p = (struct VarChar*) src->mass[i];
            string s;
            s.append((char*)p->data->ptr, p->const_len);

            VoidArray_addStr(dest, (char*) s.c_str());
        }
        else if( src->types_mass[i] == VOID_ARRAY_TYPE_NULL)
        {
            VoidArray_addNULL(dest);
        }
    }
}
//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
bool VoidArray_swap(struct VoidArray *l1, struct VoidArray *l2)
{
    if( l1 == NULL || l2 == NULL || l1->len != l2->len )
    {
        return false;
    }
    
    for(int i = 0; i < l1->len; i++)
    {
        if( l1->types_mass[i] != l2->types_mass[i] )
        {
            return false;
        }
    }
    
    void *tmp_ref;
    
    for(int i = 0; i < l1->len; i++)
    {
        tmp_ref = l1->mass[i];
        l1->mass[i] = l2->mass[i];
        l2->mass[i] = tmp_ref;
    }
    
    return true;
}