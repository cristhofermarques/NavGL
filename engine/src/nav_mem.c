#include<stdlib.h>
#include<stdio.h>
#include<nav_mem.h>
#include<nav_log.h>

DataBuffer* CreateDataBuffer( unsigned int* desc)
{
    size_t dataBufferSize = 0, stackBufferSize = 0, fieldCount = 0;
    Field fieldInfo[100] = {};
    
    // dataBufferSize, stackBufferSize, fieldCount
    dataBufferSize += DATA_BUFFER_INFO_SIZE;
    size_t afterStackSize = dataBufferSize;
    
    
    while( *desc != END_DESC)
    {
        switch( *desc)
        {
            case SET_STACK_SIZE:
                if(! stackBufferSize)
                {
                    desc++;
                    afterStackSize += *desc;
                    stackBufferSize = *desc;
                    // stackBuffer
                    dataBufferSize += *desc;
                    desc++;
                }
            break;
            
            case NEW_FIELD:
                desc++;    
                fieldInfo[fieldCount].elSize = *desc;
                desc++;
                fieldInfo[fieldCount].elCapacity = *desc;
                fieldInfo[fieldCount].fieldSize = fieldInfo[fieldCount].elCapacity * (fieldInfo[fieldCount].elSize + sizeof( char));
                fieldInfo[fieldCount].stride = fieldInfo[fieldCount].elSize + sizeof( char);
                // fieldSize, elSize, elCapacity, stride
                dataBufferSize += FIELD_BUFFER_INFO_SIZE;
                // fieldBuffer
                dataBufferSize += fieldInfo[fieldCount].fieldSize;
                fieldCount++;
                desc++;
            break;
        }
    }
    
    // size of array of field address in DataBuffer
    dataBufferSize += sizeof( void*) *  fieldCount;
    void* buff = malloc( dataBufferSize);
    
    AS( size_t*, buff)[0] = dataBufferSize;
    AS( size_t*, buff)[1] = stackBufferSize;
    AS( size_t*, buff)[2] = fieldCount;
    //AS( size_t*, buff)[3] = 0; stackBufferPeek
    
    
    void* ptrFieldPtr = OFFSET( buff, afterStackSize);
    void* fieldPtr = OFFSET( buff, afterStackSize + fieldCount * sizeof( void*));
    
    for( int i = 0; i < fieldCount; i++)
    {
        AS( size_t*, fieldPtr)[0] = fieldInfo[i].fieldSize;
        AS( size_t*, fieldPtr)[1] = fieldInfo[i].elSize;
        AS( size_t*, fieldPtr)[2] = fieldInfo[i].elCapacity;
        AS( size_t*, fieldPtr)[3] = fieldInfo[i].stride;
        AS( size_t*, fieldPtr)[4] = 0;
        AS( size_t**, ptrFieldPtr)[i] = fieldPtr;
        
        fieldPtr = OFFSET( fieldPtr, fieldInfo[i].fieldSize + FIELD_BUFFER_INFO_SIZE);
    }
    return buff;
}

void* GetStackMem( DataBuffer* dataBuffer, size_t size)
{
    if( dataBuffer->stackPeek + size > dataBuffer->stackBufferSize){ return NULL;}
    dataBuffer->stackPeek += size;
    return  OFFSET( dataBuffer, DATA_BUFFER_INFO_SIZE + dataBuffer->stackPeek);
}

void FreeStackMem(DataBuffer* dataBuffer, size_t size)
{
    if( (long)(dataBuffer->stackPeek - size) <  0){ dataBuffer->stackPeek = 0;}
    else{dataBuffer->stackPeek -= size;}
}

void* GetFieldMem( DataBuffer* dataBuffer, unsigned char  fieldIdx)
{
    size_t* fPtr = GFIELD( dataBuffer, fieldIdx);
    
    char* h = AS( char*, fPtr + 5);
    h += fPtr[4] * fPtr[3];
    if(! (*h)){ *h = 1; fPtr[4]++; return (h + sizeof(char));}

    for( int i = fPtr[4]; i < fPtr[2]; i++)
    {
        char* head = OFFSET( h, fPtr[3] * i);
        if(! (*head))
        {
            *head = 1;
            fPtr[4] = i;
            return head + sizeof(char);
        }
    }
    return NULL;
}
