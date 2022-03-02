#include<nav_str.h>
#include<nav_log.h>
#include<stdlib.h>

unsigned int StrLen( char* str)
{
    unsigned int c = 0;
    while( str[c] != '\0'){ c++;}
    c++;
    return c;
}

char* StrFrom( char* inStr)
{
    unsigned int inStrLen = StrLen( inStr);
    if( inStrLen < 1){ return NULL;}

    char* str = malloc( inStrLen * sizeof(char));
    for(int i = 0; i < inStrLen; i++)
    {
        str[i] = inStr[i];
    }
    return str;
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

char* GetStrInBuffer( char* buffer,  unsigned int bufferLen, unsigned int idx)
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