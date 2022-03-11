#ifndef NAV_LOG_H
#define NAV_LOG_H

#define STR " %s"
#define CHR " %c"
#define DEC " %i"
#define HEX " %x"
#define FLT " %g"
#define LFL " %lg"

#define LOG_TEXT_RED 4
#define LOG_TEXT_GREEN 2
#define LOG_TEXT_BLUE 1
#define LOG_TEXT_GLOW 8
#define LOG_TEXT_WHITE  LOG_TEXT_RED | LOG_TEXT_GREEN | LOG_TEXT_BLUE

#include<nav_api.h>

NAV_API void SetConsoleColor( char txtColorAttribs);

#ifdef DEBUG 
#include<stdio.h>
#define MSG( msg)\
    SetConsoleColor( LOG_TEXT_WHITE);\
    printf( "[INFO] %s %d : %s\n", __FILE__, __LINE__, msg);

#define INFO( msg)\
    SetConsoleColor( LOG_TEXT_GREEN | LOG_TEXT_RED);\
    printf( "[INFO] %s %d : %s\n", __FILE__, __LINE__, msg);
   
#define LOG( fmt, ...)\
    SetConsoleColor( LOG_TEXT_WHITE | LOG_TEXT_GLOW);\
    printf( "[LOG] %s %d :" fmt "\n", __FILE__, __LINE__, __VA_ARGS__)

#define ERRLOG( msg)\
    SetConsoleColor(LOG_TEXT_RED | LOG_TEXT_GLOW);\
    printf( "[ERR] %s %d : %s\n", __FILE__, __LINE__, msg);
    
#else
#define INFO( msg)
#define LOG(msg)
#define ERRLOG( msg)
#endif

#endif
