#ifndef NAV_GFX_H
#define NAV_GFX_H

#include<nav_platform.h>
#include<nav_api.h>

NAV_API unsigned int GLShaderFromFile( char* filePath);

NAV_API void SwapWNDBuffers( WND* wnd);
NAV_API char CreateGLContextToWND( WND* wnd, unsigned char glMajor, unsigned char glMinor, unsigned char colorBits, unsigned char depthBits);
NAV_API void DeleteGLContextOfWND( WND* wnd);



#endif
