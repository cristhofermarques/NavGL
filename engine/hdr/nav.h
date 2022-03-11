#ifndef NAV_H
#define NAV_H

#include<nav_api.h>
#include<nav_platform.h>
#include<nav_mem.h>

NAV_API void RunNav( char* gameLibPath);

NAV_API void CreateNavDataBuffer( unsigned int desc[]);
NAV_API void DeleteNavDataBuffer();

NAV_API WND* GetNavWND();
NAV_API DataBuffer* GetNavDataBuffer();

#endif

