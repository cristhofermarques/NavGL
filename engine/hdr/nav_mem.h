#ifndef NAV_MEM_H
#define NAV_MEM_H

#define SET_STACK_SIZE 111111
#define NEW_FIELD  222222
#define END_DESC 333333

#include<nav_api.h>
#include<nav_macro.h>
#include<nav_log.h>

#define DATA_BUFFER_INFO_SIZE (sizeof( size_t) * 4)
#define FIELD_BUFFER_INFO_SIZE (sizeof( size_t) * 5)

#define GFIELD( dataBuffer, idx) AS( size_t**, OFFSET( dataBuffer, DATA_BUFFER_INFO_SIZE + AS( size_t*, dataBuffer)[1]))[idx]

#define GSTACKMEM( dataBuff, ptr, size)\
{\
    if( AS( size_t*, dataBuff)[3] + size > AS( size_t*, dataBuff)[1]){ ptr = NULL;}\
    else{ AS( size_t*, dataBuff)[3] += size; ptr = OFFSET( AS( void*, dataBuff), DATA_BUFFER_INFO_SIZE + AS( size_t*, dataBuff)[3]);}\
}
    
#define FSTACKMEM( dataBuff, size)\
{\
    if( AS( long, AS( size_t*, dataBuff)[3]) <  0){ AS( size_t*, dataBuff)[3] = 0;}\
    else{ AS( size_t*, dataBuff)[3] -= size;}\
}

#define GFIELDBLOCK( dataBuff, idx, ptr)\
{\
    size_t* fPtr = GFIELD( dataBuff, idx);\
    \
    char* h = AS( char*, fPtr + 5);\
    h += fPtr[4] * fPtr[3];\
    if(! (*h)){ *h = 1; if( fPtr[4] < fPtr[2]){ fPtr[4]++;} ptr = AS( typeof(ptr), h + sizeof(char));}\
    else\
    {\
        for( int i = fPtr[4]; i < fPtr[2]; i++)\
        {\
            char* head = OFFSET( h, fPtr[3] * i);\
            if(! (*head))\
            {\
                *head = 1;\
                fPtr[4] = i;\
                ptr = AS( typeof(ptr), head + sizeof(char));\
            }\
        }\
    }\
}

#define FFIELDBLOCK( dataBuff, idx, ptr)\
{\
    char* h = (AS(char*, ptr) - 1);\
    *h = 0;\
    size_t* fPtr = GFIELD( dataBuff, idx);\
    size_t diff = BYTEDIFF( h, (fPtr) + 5) / fPtr[3];\
    if( diff < fPtr[4]){ fPtr[4] = diff;}\
}

    
typedef struct{ size_t fieldSize, elSize, elCapacity, stride, peek;} Field;
typedef struct { size_t dataBufferSize, stackBufferSize, fieldCount, stackPeek;} DataBuffer;

NAV_API DataBuffer* CreateDataBuffer( unsigned  int* desc);

NAV_API void* GetStackMem( DataBuffer* dataBuffer, size_t size);
NAV_API void FreeStackMem(DataBuffer* dataBuffer, size_t size);

NAV_API void* GetFieldMem( DataBuffer* dataBuffer, unsigned char fieldIdx);

#endif
