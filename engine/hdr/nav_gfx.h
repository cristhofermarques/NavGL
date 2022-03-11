#ifndef NAV_GFX_H
#define NAV_GFX_H

#include<nav_platform.h>
#include<nav_api.h>

typedef struct
{
  unsigned short width, height, fmt;
}NavImg;

// Platform Impl
NAV_API void SwapWNDBuffers( WND* wnd);

#endif
