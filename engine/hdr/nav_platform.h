#ifndef NAV_PLATFORM_H
#define NAV_PLATFORM_H

#include<nav_math.h>
#include<nav_game.h>
#include<nav_api.h>

struct Wnd;
typedef struct Wnd WND;

NAV_API  void ShowMSGBox( char* msg, char* title, int style);

NAV_API WND* CreateWND( char* title, int width, int height, char borderless);
NAV_API void DeleteWND(WND* wnd);
NAV_API void SetWNDVisibility(WND* wnd, char visibility);
NAV_API void SetWNDUndestructible( WND* wnd, char state);
NAV_API char UpdateWNDEvents( WND* wnd);
NAV_API char GetWNDFocus( WND* wnd);
NAV_API VecI2 GetWNDClientSize( WND* wnd);
NAV_API VecI2 GetMousePos( WND* wnd);
NAV_API VecI2 GetScreenSize();

#endif
