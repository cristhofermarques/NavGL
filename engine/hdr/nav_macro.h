#ifndef NAV_MACRO_H
#define NAV_MACRO_H

#define AS( type, value) ((type)(value))

#define OFFSET(  value, offset) (((void*)(value)) + (offset))
#define BYTEDIFF(  ptr0, ptr1) ((size_t)( AS( void*, ptr0) - AS( void*, ptr1)))

#define DOIF( v, cmd) if((v) != NULL){ cmd;}

#endif

