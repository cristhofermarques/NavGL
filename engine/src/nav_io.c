#include<nav.h>
#include<nav_log.h>
#include<nav_io.h>
#include<stdio.h>
#include<stdlib.h>

void GetFileBuffer( char* filePath, char addEndLine, char* outStr)
{
    FILE* file = fopen( filePath, "r");
    if( file == NULL){ fclose( file); return;}
    unsigned int len = 0;
    
    fseek( file, 0, SEEK_END);
    len = ftell(file);
    
    fseek( file, -1, SEEK_END);
    char lastBuffChar = fgetc(file);
    if( lastBuffChar != '\n'){ len++;}
    else if(! addEndLine){ len--;}
    
    fseek( file, 0, SEEK_SET);
    fread( outStr, sizeof(char) * len, 1, file);
    if( addEndLine){ outStr[len-1] = '\0';}
    
    fclose( file);
}

void* GetFileBufferToStackBuffer( char* filePath, char addEndLine, DataBuffer* dataBuffer, size_t* outLen)
{
    FILE* file = fopen( filePath, "rb");
    if( file == NULL){ fclose( file); return NULL;}
    
    size_t len = 0;
    fseek( file, 0, SEEK_END);
    len = ftell(file);
    
    fseek( file, -1, SEEK_END);
    char lastBuffChar = fgetc(file);
    if( lastBuffChar != '\n'){ if( addEndLine){ len++;}}
    else if(! addEndLine){ len--;}
    
    char* str;
    GSTACKMEM( dataBuffer, str, len);
    if( str == NULL){ fclose( file); return NULL;}
    
    fseek( file, 0, SEEK_SET);
    fread( str, sizeof(char), len, file);
    if( addEndLine){ str[len-1] = '\0';}
    
    fclose(file);
    *outLen = len;
    return str;
}

char WriteBufferToFile( void* buffer, size_t bufferSize, char* filePath)
{
    FILE* file = fopen( filePath, "w");
    if( file == NULL){ fclose( file); return -1;}

    fwrite( buffer, bufferSize, 1, file);

    fclose( file);
    return 1;
}

