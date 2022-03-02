#ifndef NAV_MEM_H
#define NAV_MEM_H

#define SET_STACK_SIZE 869437
#define NEW_FIELD  473964
#define END_DESC 392749

#include<stdlib.h>

typedef struct
{
    size_t fieldSize, elSize, elCapacity;
} FieldInfo;

typedef struct
{
    size_t dataBufferSize, stackSize, stackPeek, fieldCount;
    FieldInfo fields[];
} DataBufferInfo;

void CreateDataBuffer( unsigned int* desc)
{
    DataBufferInfo info = {};
    info.dataBufferSize = 0;
    info.stackSize = 0;
    FieldInfo fieldInfos[100] = {};
    
    while( *desc != END_DESC)
    {
        switch( *desc)
        {
            case SET_STACK_SIZE:
                if(! info.stackSize)
                {
                    desc++;
                    info.stackSize = *desc;
                    info.dataBufferSize += *desc;
                    desc++;
                }
            break;
            
            case NEW_FIELD:
                desc++;
                fieldInfos[info.fieldCount].elSize = *desc;
                desc++;
                fieldInfos[info.fieldCount].elCapacity = *desc;
                fieldInfos[info.fieldCount].fieldSize = fieldInfos[info.fieldCount].elCapacity * fieldInfos[info.fieldCount].elSize;
                info.dataBufferSize += fieldInfos[info.fieldCount].fieldSize;
                info.fieldCount++;
                desc++;
            break;
        }
    }
    
    info.dataBufferSize += (info.fieldCount -1)  * (sizeof(FieldInfo));
    info.dataBufferSize += sizeof(DataBufferInfo);
}

#endif
