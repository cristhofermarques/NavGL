#ifndef NAV_STR_H
#define NAV_STR_H

#include<nav_api.h>

NAV_API void StrFromIntNum( int num, char* outStr);
NAV_API void StrFromFloatNum( float num, unsigned char len, char* outStr);

NAV_API unsigned int IntLenAsStr( int num);
NAV_API unsigned int FloatLenAsStr( float num, unsigned char count);

NAV_API unsigned int StrLen( char* str);
NAV_API unsigned int SplitByChar( char* str, char separator);
NAV_API int IndexOf( char* str, char* sepStr, unsigned int startIdx);
NAV_API unsigned int SplitByStr( char* str, char* sepStr, unsigned int strLen, unsigned int** idxsBeginList);
NAV_API char* GetStrInBuffer( char* buffer, unsigned int bufferLen, unsigned int idx);
NAV_API char CharFromIntNum( unsigned int num, unsigned int idx);

#endif
