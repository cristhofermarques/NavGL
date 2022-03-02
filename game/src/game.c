 #include<nav_log.h>
#include<nav_platform.h>
#include<nav_input.h>
#include<nav_math.h>
#include<nav_gfx.h>
#include<nav_api.h>
#include<nav_gl.h>
#include<nav_io.h>
#include<nav_str.h>
#include<pthread.h>
#include<stdlib.h>

VecI2 clientSize;
VecI2 mousePos;
VecI2 size;
GLuint vbo, ibo, vao;
int shader;

int posUni;
int sizeUni;
int anchorUni;
int colorUni;

size_t elSize = 128 * sizeof(float);
size_t elCount = 100;
void* buffer;
unsigned int beginIdx = 0;

void* lastFree = 0;
char frag = 0;

WND* wnd;

#define gmem( ptr)\
{\
    char* h = (char*)(buffer + beginIdx * elSize);\
    if(! *h){ *h = 1; ptr = h;}\
    for( size_t i = beginIdx; i < elCount ; i++)\
    {\
        h = (char*)(buffer + elSize * i);\
        if(! *h)\
        {\
            *h = 1;\
            beginIdx = i + 1;\
            ptr = h; \
        }\
    }\
}

#define fmem(idx)\
{\
    char* h = buffer + elSize * idx;\
    *h = 0;\
    if( idx < beginIdx)\
    {\
        beginIdx = idx;\
    }\
}
 
NAV_GAME_API void Run()
{  
}


NAV_GAME_API void Update( float deltaTime)
{
	if( GetKeyDown(27))
	{
		ExitGame();
	}
    SwapWNDBuffers( wnd);
}

NAV_GAME_API void End()
{
}
























