#include<windows.h>
#include<windowsx.h>
#include<nav_platform.h>
#include<nav_input.h>
#include<nav_math.h>
#include<nav_gfx.h>
#include<nav_lib.h>
#include<nav_log.h>
#include<nav_gl.h>

#define NAV_WND_CLASS (char*)"nav_wnd_class"
#define NAV_WND_CLOSE WM_USER + 1
#define NAV_WND_FOCUS_CHANGE WM_USER + 2

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

// 0 : key state
// 1 : key down
// 2 : key up
// 3 : pressed key down
// 4 : pressed key up
NAV_API char keyboard[255] = {24};
NAV_API char mouse[3] = {0};
char mouseWheelDelta = 0;
VecI2 screenSize;

struct Lib{ HMODULE hModule;};

struct Wnd
{
    // 0 : Undestructible
    // 1 : Focused
    char state;
    HWND hwnd;
    HDC dc;
    HGLRC glCtx;
    VecI2 mousePos;
};

char UpdateWNDEvents(WND* wnd)
{
    for( int i = 0; i < 255; i++){ DBIT( keyboard[i], 1); DBIT( keyboard[i], 2);}
    for( int i = 0; i < 3; i++){ DBIT( mouse[i], 1); DBIT( mouse[i], 2);}

    MSG msg;

    while( PeekMessage( &msg, wnd->hwnd, 0, 0, PM_REMOVE))
    {
        switch(msg.message)
        {
            case WM_MOUSEMOVE:
                wnd->mousePos.x = GET_X_LPARAM( msg.lParam);
                wnd->mousePos.y = GET_Y_LPARAM( msg.lParam);
            break;

            case NAV_WND_FOCUS_CHANGE:
                if( msg.wParam){ ABIT( wnd->state, 1);} else { DBIT( wnd->state, 1);}
            break;

            case NAV_WND_CLOSE:
                if(! GBIT(wnd->state, 0)){ return 0;}
        }

        TranslateMessage( &msg);
        DispatchMessage( &msg);
    }

    return 1;
}

LRESULT NavWNDProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg)
    {
        case WM_CREATE:
            for( int i = 0; i < 255; i++){ PostMessage( hwnd, WM_KEYUP, i, 0);}
            PostMessage( hwnd, WM_SETFOCUS, 0, 0);
        break;

        case WM_CLOSE:
            PostMessage( hwnd, NAV_WND_CLOSE, 0, 0);
            return 0;
        break;

        case WM_KEYDOWN:
            ABIT( keyboard[wParam], 0);
            if( GBIT( keyboard[wParam], 3)){ DBIT( keyboard[wParam], 3); ABIT( keyboard[wParam], 1);}
            ABIT( keyboard[wParam], 4);
        break;

        case WM_KEYUP:
            DBIT( keyboard[wParam], 0);
            ABIT( keyboard[wParam], 3);
            if( GBIT( keyboard[wParam], 4)){ DBIT( keyboard[wParam], 4); ABIT( keyboard[wParam], 2);}
        break;

        case WM_LBUTTONDOWN:
            ABIT( mouse[0], 0);
            ABIT( mouse[0], 1);
        break;

        case WM_LBUTTONUP:
            DBIT( mouse[0], 0);
            ABIT( mouse[0], 2);
        break;

        case WM_MBUTTONDOWN:
            ABIT( mouse[1], 0);
            ABIT( mouse[1], 1);
        break;

        case WM_MBUTTONUP:
            DBIT( mouse[1], 0);
            ABIT( mouse[1], 2);
        break;

        case WM_RBUTTONDOWN:
            ABIT( mouse[2], 0);
            ABIT( mouse[2], 1);
        break;

        case WM_RBUTTONUP:
            DBIT( mouse[2], 0);
            ABIT( mouse[2], 2);
        break;

        case WM_MOUSEWHEEL:
            mouseWheelDelta = GET_WHEEL_DELTA_WPARAM( wParam);
        break;
        
        case WM_SYSKEYDOWN:
            LOG( DEC, wParam);
        break;
        
        case WM_HELP:
            LOG( DEC, wParam);
        break;

        case WM_SETFOCUS:
            PostMessage( hwnd, NAV_WND_FOCUS_CHANGE, 1, 0);
        break;

        case WM_KILLFOCUS:
            PostMessage( hwnd, NAV_WND_FOCUS_CHANGE, 0, 0);
        break;
    }

    return DefWindowProc( hwnd, msg, wParam, lParam);
}

WND* CreateWND( char* title, int width, int height, char borderless)
{
    HINSTANCE hInst = GetModuleHandle(NULL);

    WNDCLASSEXA wndClass = {0};
    wndClass.cbClsExtra = wndClass.cbWndExtra = 0;
    wndClass.cbSize = sizeof( WNDCLASSEX);
    wndClass.lpfnWndProc = NavWNDProc;
    wndClass.hIcon = LoadIcon( hInst, MAKEINTRESOURCE( 101));
    wndClass.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH);
    wndClass.hInstance = hInst;
    wndClass.lpszClassName = NAV_WND_CLASS;

    if(! GetClassInfoExA( hInst, NAV_WND_CLASS, &wndClass))
    {
        if(! RegisterClassExA( &wndClass)){ ERRLOG("cant register wnd class"); return 0;}
    }

    DWORD wndStyle = WS_VISIBLE;
    if(borderless){ wndStyle |= WS_OVERLAPPEDWINDOW;} else { wndStyle |= WS_POPUP;}

    HWND hwnd = CreateWindowExA
    (
        0, NAV_WND_CLASS, title, wndStyle, 
        0, 0, width, height,
        NULL, NULL, hInst, 0
    );

    if(! hwnd){ ERRLOG("cant create window"); return 0;}

    WND* wnd = (WND*)malloc( sizeof( WND));
    DBIT( wnd->state, 0);
    DBIT( wnd->state, 1);
    wnd->hwnd = hwnd;
    wnd->dc = GetDC( hwnd);
    return wnd;
}

void DeleteWND( WND* wnd){ if( wnd != 0){ DestroyWindow( wnd->hwnd); free( wnd);}}

void SetWNDVisibility( WND *wnd, char visibility)
{
    char showFlag = SW_HIDE;
    if( visibility){ showFlag = SW_SHOW;}

    if(  wnd == NULL)
    {
        HWND cHwnd = GetConsoleWindow();
        ShowWindow( cHwnd, showFlag);
    }
    else
    {
        ShowWindow( wnd->hwnd, showFlag);
    }
}

VecI2 GetWNDClientSize( WND* wnd)
{ 
    RECT clientRect = {-1};
    GetClientRect( wnd->hwnd, &clientRect);
    VecI2 clientSize;
    clientSize.x = clientRect.right - clientRect.left;
    clientSize.y = clientRect.bottom - clientRect.top;
    return clientSize;
}

VecI2 GetMousePos( WND* wnd){ return wnd->mousePos;}

VecI2 GetScreenSize()
{
    screenSize.x = GetSystemMetrics(SM_CXSCREEN);
    screenSize.y = GetSystemMetrics(SM_CYSCREEN);
    return screenSize;
}

char GetMouseWheelDelta(){ return mouseWheelDelta;}
void SetWNDUndestructible( WND* wnd, char state){ if( state){ ABIT( wnd->state, 0);} else { DBIT( wnd->state, 0);}}
char GetWNDFocus( WND* wnd){ return GBIT( wnd->state, 1);}

void ShowMSGBox(char* msg, char* title, int style)
{
    MessageBox( NULL, msg, title, style);
}

char GetKey(char key){ return GBIT( keyboard[key], 0);}
char GetKeyDown(char key){ return GBIT( keyboard[key], 1);}
char GetKeyUp(char key){ return GBIT( keyboard[key], 2);}

char GetMouseButton( char button){ return GBIT( mouse[button], 0);}
char GetMouseButtonDown( char button){ return GBIT( mouse[button], 1);}
char GetMouseButtonUp( char button){ return GBIT( mouse[button], 2);}

char GetWglARBFuncsPtr()
{
    WND* dummyWnd = CreateWND((char*)"", 0, 0, 0);

    if( dummyWnd == 0){ DeleteWND( dummyWnd); return 1;}

    PIXELFORMATDESCRIPTOR pxFmtDesc = 
    {
        sizeof(PIXELFORMATDESCRIPTOR), 1, 
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
    };

    int pxFmt = ChoosePixelFormat( dummyWnd->dc, &pxFmtDesc);
    if(! pxFmt){ ERRLOG("Choose Pixel Format"); DeleteWND( dummyWnd); return 1;}

    if(! SetPixelFormat( dummyWnd->dc, pxFmt, &pxFmtDesc)){ ERRLOG("Set Pixel Format"); DeleteWND( dummyWnd); return 1;}

    dummyWnd->glCtx = wglCreateContext( dummyWnd->dc);

    if(! dummyWnd->glCtx){ ERRLOG("Create Dummy Context"); DeleteWND( dummyWnd); return 1;}

    if(! wglMakeCurrent( dummyWnd->dc, dummyWnd->glCtx))
    { 
        ERRLOG("Make Dummy Context Current");
        DeleteWND( dummyWnd); 
        wglDeleteContext(dummyWnd->glCtx);
        return 1;
    }

    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    wglMakeCurrent( 0, 0);
    wglDeleteContext( dummyWnd->glCtx);
    DeleteWND( dummyWnd);

    if( wglChoosePixelFormatARB == NULL){ ERRLOG( "'wglChoosePixelFormatARB' Func Ptr"); return 1;}
    if( wglCreateContextAttribsARB == NULL){ ERRLOG( "'wglCreateContextAttribsARB' Func Ptr"); return 1;}

    return 0;
}

char CreateGLContextToWND( WND* wnd, unsigned char glMajor, unsigned char glMinor, unsigned char colorBits, unsigned char depthBits)
{
    if( GetWglARBFuncsPtr()){ ERRLOG("Get Wgl Funcs Pointer"); return 1;}

    int pxFmtAttribList[] = 
    {
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_COLOR_BITS_ARB, colorBits,
        WGL_DEPTH_BITS_ARB, depthBits,
        0
    };

    int pxFmt, numOfPxFmt;

    wglChoosePixelFormatARB( wnd->dc, pxFmtAttribList, NULL, 1, &pxFmt, &numOfPxFmt);
    if( numOfPxFmt = 0){ ERRLOG(" Choose ARB Pixel Format"); return 1;}
    
    PIXELFORMATDESCRIPTOR pxFmtDesc = 
    {
        sizeof(PIXELFORMATDESCRIPTOR), 1, 
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, depthBits, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        colorBits, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
    };

    if(! SetPixelFormat( wnd->dc, pxFmt, &pxFmtDesc)){ ERRLOG(" Set ARB Pixel Format"); return 1;}

    int ctxAttribList[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, glMajor,
        WGL_CONTEXT_MINOR_VERSION_ARB, glMinor,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
#ifdef DEBUG
        | WGL_CONTEXT_DEBUG_BIT_ARB
#endif
        , 0
    };

    wnd->glCtx = wglCreateContextAttribsARB( wnd->dc, NULL, ctxAttribList);
    if(! wnd->glCtx){ ERRLOG("Create ARB Context"); wnd->glCtx = NULL; return 1; }

    if(! wglMakeCurrent( wnd->dc, wnd->glCtx)){ ERRLOG("Make ARB Context Current"); return 1;};

    return 0;
}

void DeleteGLContextOfWND( WND* wnd)
{
    wglMakeCurrent(0, 0);
    wglDeleteContext( wnd->glCtx);
}

void SwapWNDBuffers( WND* wnd)
{
    SwapBuffers( wnd->dc);
}

LIB* LoadLIB( char* path)
{
    HMODULE hModule = LoadLibrary( path);
    if( hModule)
    {
        //todo mem alloc
        LIB* lib = malloc( sizeof(LIB));
        lib->hModule = hModule;
        return lib;
    }

    ERRLOG( path);
    return NULL;
}

void UnloadLIB( LIB* lib)
{
    if(lib != NULL)
    {
        FreeLibrary( lib->hModule);
        free( lib);// todo mem alloc
    }
}

void* GetLIBProcAddress( LIB* lib, char* procName)
{
    return (void*)GetProcAddress( lib->hModule, procName);
}

void SetConsoleColor( char txtColorAttribs)
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), txtColorAttribs);
}
