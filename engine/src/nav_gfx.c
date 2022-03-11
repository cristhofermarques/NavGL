#include<nav.h>
#include<nav_gfx.h>
#include<nav_str.h>
#include<nav_log.h>
#include<nav_mem.h>
#include<nav_io.h>
#include<nav_gl.h>
#include<stdlib.h>
#include<stdio.h>

unsigned int GLShaderFromFile( char* filePath)
{
    size_t len = 0;
    char* cont = GetFileBufferToStackBuffer( filePath, 1, GetNavDataBuffer(), &len);
    if( cont == NULL){ return -1;}

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
        FSTACKMEM( GetNavDataBuffer(),len);
        return 0;
    }

    const char* fragSource = (const char*)(cont + fragIdx + 5);
    GLuint fragShaderH = glCreateShader( GL_FRAGMENT_SHADER);
    glShaderSource( fragShaderH, 1, &fragSource, NULL);
    glCompileShader( fragShaderH);

    glGetShaderiv( fragShaderH, GL_COMPILE_STATUS, &info);
    if(! info)
    {
        char err[512];
        glGetShaderInfoLog( fragShaderH, 512, NULL, err);
        ERRLOG( err);
        glDeleteShader( vertShaderH);
        glDeleteShader( fragShaderH);
        FSTACKMEM( GetNavDataBuffer(),len);
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
        glGetProgramInfoLog( shaderH, 512, NULL, err);
        ERRLOG( err);
        glDeleteShader( vertShaderH);
        glDeleteShader( fragShaderH);
        glDeleteProgram( shaderH);
        FSTACKMEM( GetNavDataBuffer(),len);
        return 0;
    }

    glDetachShader( shaderH, vertShaderH);
    glDetachShader( shaderH, fragShaderH);
    glDeleteShader( vertShaderH);
    glDeleteShader( fragShaderH);

    FSTACKMEM( GetNavDataBuffer(),len);
    return shaderH;
}

unsigned int GL2DTextureFromNif( char* filePath)
{
    size_t len = 0;
    NavImg* img = (NavImg*)GetFileBufferToStackBuffer( filePath, 0, GetNavDataBuffer(), &len);
    if( img == NULL){ ERRLOG(filePath);return -1;}
    
    unsigned char* data = ((void*)img) + sizeof( NavImg);
    
    GLuint tex;
    glGenTextures( 1, &tex);
    glBindTexture( GL_TEXTURE_2D, tex);
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    FSTACKMEM( GetNavDataBuffer(), len);
    
    return tex;
}
