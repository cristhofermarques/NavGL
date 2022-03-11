#include<nav_str.h>
#include<nav_log.h>
#include<stdlib.h>
#include<math.h>

unsigned int StrLen( char* str)
{
    unsigned int c = 0;
    while( str[c] != '\0'){ c++;}
    c++;
    return c;
}

int IndexOf( char* str, char* sepStr, unsigned int startIdx)
{
    unsigned int strLen = StrLen( str);
    unsigned int sepStrLen = StrLen( sepStr);

    if( strLen < 1){ return -2;}
    if( sepStrLen < 1){ return -2;}

    for( unsigned int i = startIdx; i < strLen; i++)
    {
        if( str[i] == sepStr[0] && i+1 < strLen && str[i+1] != '\0')
        {    
            char equal = 1;
            for( unsigned int sepI = 1; sepI < sepStrLen - 1; sepI++)
            {
                if(! (str[i + sepI] == sepStr[ sepI]))
                {
                    equal = 0;
                    break;
                }
            }

            if( equal)
            {
                return i;
            }
        }
    }
    
    return -1;
}

unsigned int SplitByChar( char* str, char separator)
{
    unsigned int splitCount = 0;
    unsigned int strLen = StrLen( str);
    if( strLen < 1){ return splitCount;}


    for( unsigned int i = 0; i < strLen; i++)
    {
        if( str[i] == separator)
        {    
            str[i] = '\0';
            splitCount++;
        }
    }
    return splitCount;
}

unsigned int SplitByStr( char* str, char* sepStr, unsigned int strLen, unsigned int** idxsBeginList)
{
    char genIdxsBeginList = idxsBeginList != NULL;
    unsigned int splitCount = 0;

    if( strLen == 0){ strLen = StrLen( str);}
    unsigned int sepStrLen = StrLen( sepStr);

    if( strLen < 1){ return splitCount;}
    if( sepStrLen < 1){ return splitCount;}

    unsigned int idxsBeginListProxy[ (int)(strLen / 2)];
    idxsBeginListProxy[0] = 0;

    for( unsigned int i = 0; i < strLen; i++)
    {
        if( str[i] == sepStr[0] && i+1 < strLen && str[i+1] != '\0')
        {    
            char equal = 1;
            for( unsigned int sepI = 1; sepI < sepStrLen - 1; sepI++)
            {
                if( str[i + sepI] == sepStr[ sepI])
                {
                    equal &= 1;
                }
                else{ equal = 0; break;}
            }

            if( equal)
            {
                if( i != 0){ str[i] = '\0';}else{ str[i] = ' ';}
                for( unsigned int sepI = 1; sepI < sepStrLen - 1; sepI++)
                {
                    str[i + sepI] = ' ';
                }
                splitCount++;
                if( genIdxsBeginList){ idxsBeginListProxy[splitCount] = i+ sepStrLen - 1;}
            }
        }
    }

    if( genIdxsBeginList && splitCount > 0)
    {
        *idxsBeginList = malloc( (splitCount + 1) * sizeof( unsigned int));
        for( unsigned int i = 0; i < splitCount + 1; i++)
        {
            (*idxsBeginList)[i] = idxsBeginListProxy[i];
        }
    }

    return splitCount;
}

char* GetStrInBuffer( char* buffer, unsigned int bufferLen, unsigned int idx)
{
    unsigned int currStrIdx = 0;

    for(int i = 0; i < bufferLen; i++)
    {
        if( buffer[i] == '\0' && buffer[i+1] != '\0' && i+1 < bufferLen && (++currStrIdx) == idx)
        {            
            return buffer + i + 1;
        }
    }

    return NULL;
}

char CharFromIntNum( unsigned int num, unsigned int idx)
{
    unsigned int digCount = 0;
    unsigned int res = num;
    while( num > pow( 10, digCount)){ digCount ++;}
    unsigned int curr =  digCount -1;
    
    while(1)
    {    
        unsigned int powByCurr = pow( 10, curr);
        int divRest = trunc( res / powByCurr);
        if( curr == idx){ return 48 + divRest;}
        res -= powByCurr * divRest;
        curr--;
    }
    
    return 0;
}

void StrFromIntNum( int num, char* outStr)
{
    unsigned int strPeek = 0, numPeek = 0;
    if( num < 0){ outStr[0] = '-'; strPeek = 1;  num *= -1;}
    while( num >  pow( 10, numPeek)){ numPeek++;}
    numPeek--;
    for(; numPeek > 0; numPeek--)
    {
        outStr[ strPeek] = CharFromIntNum( num, numPeek);
        strPeek++;
    }
    outStr[ strPeek] = CharFromIntNum( num, 0);
    strPeek++;
    outStr[ strPeek] = '\0';
}

void StrFromFloatNum( float num, unsigned char len, char* outStr)
{
    float numProxy = num;
    float tNumProxy = trunc(abs(num));
    unsigned int amountNumsBeforeFloatPoint = 0, numPeek = 0, strPeek = 0;
    
    while( tNumProxy > 0)
    {
        tNumProxy *= 0.1f;
        tNumProxy = round(tNumProxy);
        amountNumsBeforeFloatPoint++;
    }
    
    if( num < 0.0f){ outStr[0] = '-'; strPeek = 1;  num *= -1; amountNumsBeforeFloatPoint++;}
    
    numProxy = num;
    numProxy *= pow( 10, len);
    int intNumProxy = (int)trunc( numProxy);
    
    while( numProxy > pow( 10, numPeek)){ numPeek++;}
    numPeek--;
    
    for(; numPeek > 0; numPeek--)
    {
        if( strPeek == amountNumsBeforeFloatPoint){ outStr[strPeek] = '.'; numPeek++;}
        else
        {
            outStr[ strPeek] = CharFromIntNum( intNumProxy, numPeek);
        }
        strPeek++;
    }
    outStr[ strPeek] = CharFromIntNum( intNumProxy, 0);
    strPeek++;
    outStr[ strPeek] = '\0';
}

unsigned int IntLenAsStr( int num)
{
    unsigned int len = 0;
    unsigned int numDigCount = 0;
    if( num < 0){ len++; num *= -1;}
    while( num > pow( 10, numDigCount)){ numDigCount++;}
    len += numDigCount;
    len++;
    return len * sizeof(char);
}

unsigned int FloatLenAsStr( float num, unsigned char count)
{
    unsigned int len = 0;
    int numProxy = trunc(num);
    if( num < 0){ len++; numProxy *= -1;} // to num if its negative
    unsigned char amountNumsBeforeFloatPoint = 0;
    while( numProxy > 0)
    {
        numProxy *= 0.1f;
        amountNumsBeforeFloatPoint++;
    }
    len += amountNumsBeforeFloatPoint;
    len += count;
    len++; // to float point char
    len++; // to str end line char
    return len * sizeof(char);
}
