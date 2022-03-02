#ifndef NAV_LIB_H
#define NAV_LIB_H

#include<nav_api.h>
#include<nav_platform.h>

struct Lib;
typedef struct Lib LIB;

NAV_API LIB* LoadLIB( char* path);
NAV_API void UnloadLIB( LIB* lib);
NAV_API void* GetLIBProcAddress( LIB* lib, char* procName);

#endif

