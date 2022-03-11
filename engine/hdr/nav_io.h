#ifndef NAV_IO_H
#define NAV_IO_H

#include<nav_api.h>
#include<nav_mem.h>

NAV_API void* GetFileBufferToStackBuffer( char* filePath, char addEndLine, DataBuffer* dataBuffer, size_t* outLen);

NAV_API char WriteBufferToFile( void* buffer, size_t bufferSize, char* filePath);

#endif
