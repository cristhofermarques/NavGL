#include<nav_log.h>
#include<nav_io.h>
#include<stdio.h>
#include<stdlib.h>

char* GetFileText( char* filePath)
{
    FILE* file = fopen( filePath, "r");
    if( file == NULL){ fclose( file); return NULL;}

    size_t len = 0;
    char c;
    while(( c = fgetc( file)) != EOF){ len++;}
    fseek( file, 0, SEEK_SET);

    char* buffer = malloc( (len+1) * sizeof(char));

    c = fgetc(file);
    for(int i = 0; c != EOF; i++)
    {
        buffer[i] = c;
        c = fgetc(file);
    }
    buffer[len] = '\0';
    fclose( file);
    return buffer;
}

void* GetFileBuffer( char* filePath, size_t* bufferSize)
{
    FILE* file = fopen( filePath, "r");
    if( file == NULL){ fclose( file); return NULL;}

    fseek( file, 0, SEEK_END);
    size_t size = ftell( file);
    fseek( file, 0, SEEK_SET);

    void* buffer = malloc( size * sizeof(char));
    *bufferSize = size * sizeof(char);

    fread( buffer, size * sizeof(char), 1, file);
    fclose( file);
    return buffer;
}

char WriteBufferToFile( void* buffer, size_t bufferSize, char* filePath)
{
    FILE* file = fopen( filePath, "w");
    if( file == NULL){ fclose( file); return -1;}

    fwrite( buffer, bufferSize, 1, file);

    fclose( file);
    return 1;
}