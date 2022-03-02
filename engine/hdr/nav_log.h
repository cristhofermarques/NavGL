#ifndef NAV_LOG_H
#define NAV_LOG_H

#ifdef DEBUG 
#include<stdio.h>

#define LOG( msg) printf( "[LOG] %s %d : %s\n", __FILE__, __LINE__, #msg)
#define FMTLOG( fmt, msg) printf( "[LOG] %s %d : " fmt, __FILE__, __LINE__, msg)
#define ERRLOG( msg) printf( "%s\n", msg)
#else
#define LOG(msg)
#define NUMLOG( msg)
#endif

#endif