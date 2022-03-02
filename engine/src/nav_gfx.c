#include<nav_gfx.h>
#include<nav_str.h>
#include<nav_log.h>
#include<nav_io.h>
#include<nav_gl.h>
#include<stdlib.h>
#include<stdio.h>

unsigned int GLShaderFromFile( char* filePath)
{
    char* cont = GetFileText( filePath);
    if( cont == NULL){ return 0;}

    unsigned int vertIdx, fragIdx;

    vertIdx = IndexOf( cont, "vert:", 0);
    fragIdx = IndexOf( cont, "frag:", 0);

    cont[vertIdx] = '\0';
    cont[fragIdx] = '\0';

    const char* vertSource = (const char*)(cont + vertIdx + 5);
    GLuint vertShaderH = glCreateShader( GL_VERTEX_SHADER);
    glShaderSource( vertShaderH, 1, &vertSource, NULL);
    glCompileShader( vertShaderH);

    GLuint info;
    glGetShaderiv( vertShaderH, GL_COMPILE_STATUS, &info);
    if(! info)
    {
        char err[512];
        glGetShaderInfoLog( vertShaderH, 512, NULL, err);
        ERRLOG( err);
        glDeleteShader( vertShaderH);
        free( cont);
        return 0;
    }

    const char* fragSource = (const char*)(cont + fragIdx + 5);
    GLuint fragShaderH = glCreateShader( GL_FRAGMENT_SHADER);
    glShaderSource( fragShaderH, 1, &fragSource, NULL);
    glCompileShader( fragShaderH);

    glGetShaderiv( vertShaderH, GL_COMPILE_STATUS, &info);
    if(! info)
    {
        char err[512];
        glGetShaderInfoLog( fragShaderH, 512, NULL, err);
        ERRLOG( err);
        glDeleteShader( vertShaderH);
        glDeleteShader( fragShaderH);
        free( cont);
        return 0;
    }

    unsigned int shaderH = glCreateProgram();
    glAttachShader( shaderH, vertShaderH);
    glAttachShader( shaderH, fragShaderH);

    glLinkProgram( shaderH);

    glGetProgramiv( shaderH, GL_LINK_STATUS, &info);
    if(! info)
    {
        char err[512];
        glGetProgramInfoLog( fragShaderH, 512, NULL, err);
        ERRLOG( err);
        glDeleteShader( vertShaderH);
        glDeleteShader( fragShaderH);
        glDeleteProgram( shaderH);
        free( cont);
        return 0;
    }

    glDetachShader( shaderH, vertShaderH);
    glDetachShader( shaderH, fragShaderH);
    glDeleteShader( vertShaderH);
    glDeleteShader( fragShaderH);

    free( cont);
    return shaderH;
}