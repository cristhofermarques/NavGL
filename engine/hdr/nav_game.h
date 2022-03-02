#ifndef NAV_GAME_H
#define NAV_GAME_H

#include<nav_api.h>

typedef void (*VOIDCALL)();
typedef void (*UPDATECALL)( float deltaTime);

struct Wnd;

NAV_API struct Wnd* GetWND();
NAV_API void RequestLoadGame( char* gameLibPath);

NAV_API void RunEngine( char* gameLibPath);
NAV_API char LoadGame( char* gameLibPath);
NAV_API void UnloadGame();
NAV_API void ExitGame();

#endif
