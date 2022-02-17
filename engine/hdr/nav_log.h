#ifndef NAV_LOG_H
#define NAV_LOG_H

#ifdef DEBUG 
#include<stdio.h>
#define LOG(msg) printf( "%s", msg);
#else
#define LOG(msg)
#endif

#endif