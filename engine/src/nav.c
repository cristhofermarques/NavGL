#include<nav_platform.h>
#include<nav_game.h>
#include<nav_lib.h>
#include<nav_api.h>
#include<nav_mem.h>
#include<nav_log.h>
#include<nav.h>
#include<stdlib.h>

#define NIL (void*)0

WND* wnd;
LIB* gameLib;
DataBuffer* dataBuffer;

VOIDCALL runGame;
VOIDCALL endGame;
UPDATECALL updateGame;

char runLoop = 1;
char requestLoadGame = 0;
char* requestGameLibPath;


// Nav Entry Point
void RunNav(char* gameLibPath)
{
    wnd = CreateWND( "Nav", 600, 480, 1);
    if( wnd == NIL){ return;}
    if(! LoadGame( gameLibPath)){return;}
        
     while( UpdateWNDEvents( wnd) && runLoop)
    {
        updateGame( 0.0f);
        if( requestLoadGame){ LoadGame( requestGameLibPath); requestLoadGame = 0;}
    }
    
    UnloadGame();
    DeleteWND( wnd);
    DeleteNavDataBuffer();
}

// Nav DataBuffer Manipulation
void CreateNavDataBuffer( unsigned int desc[]){ dataBuffer = CreateDataBuffer( desc);}
void DeleteNavDataBuffer(){ if( dataBuffer != NULL){ free( dataBuffer);}}

// Get Nav Infos
WND*  GetNavWND(){ return wnd;}
DataBuffer*  GetNavDataBuffer(){ return dataBuffer;}


// Game Lib Load
char  LoadGame( char* gameLibPath)
{
    LIB* lib = LoadLIB( gameLibPath);
    if( lib == NIL){ return 0;}
    
    VOIDCALL runLib;
    VOIDCALL endLib;
    UPDATECALL updateLib;
    
   runLib = GetLIBProcAddress( lib, "Run");
   endLib = GetLIBProcAddress( lib, "End");
   updateLib = GetLIBProcAddress( lib, "Update");
   
    if( runLib == NIL || endLib == NIL || updateLib == NIL){ return 0;}
    
    UnloadGame();
    gameLib = lib;
    runGame = runLib;
    endGame = endLib;
    updateGame = updateLib;
    runGame();
    return 1;
}

void RequestLoadGame( char* gameLibPath)
{
    requestLoadGame = 1;
    requestGameLibPath = gameLibPath;
}

void UnloadGame()
{
    if( gameLib != (void*)0 && endGame != (void*)0)
    {
        endGame();
        UnloadLIB( gameLib);
    }
}

void ExitGame(){ runLoop = 0;}
