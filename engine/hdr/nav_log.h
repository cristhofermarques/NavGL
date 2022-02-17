#ifndef NAV_LOG_H
#define NAV_LOG_H

#ifdef DEBUG 
#include<stdio.h>
#define LOG(msg) printf( "%s", msg);
#define NUMLOG(msg) printf( "%d", msg);
#else
#define LOG(msg)
#endif

#endif