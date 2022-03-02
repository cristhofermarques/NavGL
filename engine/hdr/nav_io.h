#ifndef NAV_IO_H
#define NAV_IO_H

#include<nav_api.h>

NAV_API char* GetFileText( char* filePath);

NAV_API void* GetFileBuffer( char* filePath, size_t* bufferSize);

NAV_API char WriteBufferToFile( void* buffer, size_t bufferSize, char* filePath);

#endif