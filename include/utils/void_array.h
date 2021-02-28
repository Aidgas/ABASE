#ifndef VOID_ARRAY_H_INCLUDED
#define VOID_ARRAY_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string>
#include <string.h>

extern "C"
{
    #include "../utils/buf.h"
}

#define VOID_ARRAY_TYPE_NULL              0x00
#define VOID_ARRAY_TYPE_INT8              0x01
#define VOID_ARRAY_TYPE_UINT8             0x02
#define VOID_ARRAY_TYPE_INT16             0x03
#define VOID_ARRAY_TYPE_UINT16            0x04
#define VOID_ARRAY_TYPE_INT32             0x05
#define VOID_ARRAY_TYPE_UINT32            0x06
#define VOID_ARRAY_TYPE_INT64             0x07
#define VOID_ARRAY_TYPE_UINT64            0x08
#define VOID_ARRAY_TYPE_INTPTR            0x09
#define VOID_ARRAY_TYPE_UINTPTR           0x10
#define VOID_ARRAY_TYPE_DOUBLE            0x11
#define VOID_ARRAY_TYPE_FLOAT             0x12
#define VOID_ARRAY_TYPE_STR               0x13
#define VOID_ARRAY_TYPE_BUFFER_DATA       0x14
#define VOID_ARRAY_TYPE_VCHAR             0x15

using namespace std;

struct VoidArray
{
    int len;
    void **mass;
    uint8_t *types_mass;
    
    VoidArray()
    {
        len = 0;
    }
};

struct VarChar
{
    unsigned int const_len;
    struct buf* data;
};

///----------------------------------------------------------------

struct VoidArray *VoidArray_init();

void VoidArray_free(struct VoidArray *v);

void VoidArray_deleteItem(struct VoidArray *v, int index);

int VoidArray_setInt8(struct VoidArray *v, int8_t int8, int index);
int VoidArray_addInt8(struct VoidArray *v, int8_t int8);

int VoidArray_setUInt8(struct VoidArray *v, uint8_t uint8, int index);
int VoidArray_addUInt8(struct VoidArray *v, uint8_t uint8);

int VoidArray_setInt16(struct VoidArray *v, int16_t int16, int index);
int VoidArray_addInt16(struct VoidArray *v, int16_t int16);

int VoidArray_setUInt16(struct VoidArray *v, uint16_t uint16, int index);
int VoidArray_addUInt16(struct VoidArray *v, uint16_t uint16);

int VoidArray_setInt32(struct VoidArray *v, int32_t int32, int index);
int VoidArray_addInt32(struct VoidArray *v, int32_t int32);

int VoidArray_setUInt32(struct VoidArray *v, uint32_t uint32, int index);
int VoidArray_addUInt32(struct VoidArray *v, uint32_t uint32);

int VoidArray_setInt64(struct VoidArray *v, int64_t int64, int index);
int VoidArray_addInt64(struct VoidArray *v, int64_t int64);

int VoidArray_setUInt64(struct VoidArray *v, uint64_t uint64, int index);
int VoidArray_addUInt64(struct VoidArray *v, uint64_t uint64);

int VoidArray_setIntPtr(struct VoidArray *v, intptr_t intptr, int index);
int VoidArray_addIntPtr(struct VoidArray *v, intptr_t intptr);

int VoidArray_setUIntPtr(struct VoidArray *v, uintptr_t uintptr, int index);
int VoidArray_addUIntPtr(struct VoidArray *v, uintptr_t uintptr);

int VoidArray_setFloat(struct VoidArray *v, float _float, int index);
int VoidArray_addFloat(struct VoidArray *v, float _float);

int VoidArray_setDouble(struct VoidArray *v, double _double, int index);
int VoidArray_addDouble(struct VoidArray *v, double _double);

int VoidArray_setStr(struct VoidArray *v, char* _str, int index);
int VoidArray_addStr(struct VoidArray *v, char* _str);

int VoidArray_setVChar(struct VoidArray *v, char* _str, unsigned int const_len, int index);
int VoidArray_addVChar(struct VoidArray *v, char* _str, unsigned int const_len);

int VoidArray_setNULL(struct VoidArray *v, int index);
int VoidArray_addNULL(struct VoidArray *v);


int8_t* VoidArray_getInt8(struct VoidArray *v, int index);
uint8_t* VoidArray_getUInt8(struct VoidArray *v, int index);

int16_t* VoidArray_getInt16(struct VoidArray *v, int index);
uint16_t* VoidArray_getUInt16(struct VoidArray *v, int index);

int32_t* VoidArray_getInt32(struct VoidArray *v, int index);
uint32_t* VoidArray_getUInt32(struct VoidArray *v, int index);

int64_t* VoidArray_getInt64(struct VoidArray *v, int index);
uint64_t* VoidArray_getUInt64(struct VoidArray *v, int index);

intptr_t* VoidArray_getIntPtr(struct VoidArray *v, int index);
uintptr_t* VoidArray_getUIntPtr(struct VoidArray *v, int index);

float* VoidArray_getFloat(struct VoidArray *v, int index);
double* VoidArray_getDouble(struct VoidArray *v, int index);

char* VoidArray_getString(struct VoidArray *v, int index);
struct buf* VoidArray_getBinaryBuffer(struct VoidArray *v, int index);
struct VarChar* VoidArray_getVarChar(struct VoidArray *v, int index);

int VoidArray_isNULL(struct VoidArray *v, int index);

/**
    copy ref in array
*/
int VoidArray_setBufferData(struct VoidArray *v, struct buf* bd, int index);
int VoidArray_addBufferData(struct VoidArray *v, struct buf* bd);

void VoidArray_append(struct VoidArray *dest, struct VoidArray *src);
bool VoidArray_swap(struct VoidArray *l1, struct VoidArray *l2);

void debug_void_array_print( struct VoidArray *data_list );

#endif // VOID_ARRAY_H_INCLUDED
