#ifndef NAV_STR_H
#define NAV_STR_H

#include<nav_api.h>

NAV_API char* StrFrom( char* inStr);

NAV_API unsigned int StrLen( char* str);

NAV_API unsigned int SplitByChar( char* str, char separator);

NAV_API int IndexOf( char* str, char* sepStr, unsigned int startIdx);

NAV_API unsigned int SplitByStr( char* str, char* sepStr, unsigned int strLen, unsigned int** idxsBeginList);

NAV_API char* GetStrInBuffer( char* buffer, unsigned int bufferLen, unsigned int idx);

#endif