#include<windows.h>
#include<nav_platform.h>
#include<nav_input.h>
#include<nav_log.h>

#define NAV_WND_CLASS (char*)"nav_wnd_class"
#define NAV_WND_CLOSE WM_USER + 1

#define GBIT( value, bitIdx) value & (1 << bitIdx);
#define ABIT( value, bitIdx) value |= (1 << bitIdx);
#define DBIT( value, bitIdx) value &= ~(1 << bitIdx);

char GetBit( char value, unsigned int bitIdx){ return value & (1 << bitIdx);}

// 0 : key state
// 1 : key down
// 2 : key up
// 3 : pressed key down
// 4 : pressed key up
char keyboard[255] = {0};

struct Wnd
{
    char state;
    HWND hwnd;
};

char UpdateWNDEvents(WND* wnd)
{
    for(int i = 0; i < 255; i++){ DBIT( keyboard[i], 1); DBIT( keyboard[i], 2);}

    MSG msg;

    while( PeekMessage( &msg, wnd->hwnd, 0, 0, PM_REMOVE))
    {
        if( msg.message == NAV_WND_CLOSE){ return 0;}

        TranslateMessage( &msg);
        DispatchMessage( &msg);
    }

    return 1;
}

LRESULT NavWNDProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg)
    {
        case WM_CLOSE:
            PostMessage( hwnd, NAV_WND_CLOSE, 0, 0);
            return 0;
        break;

        case WM_KEYDOWN:
            ABIT( keyboard[wParam], 0);
            if( GetBit( keyboard[wParam], 3)){ DBIT( keyboard[wParam], 3); ABIT( keyboard[wParam], 1);}
            ABIT( keyboard[wParam], 4);
        break;

        case WM_KEYUP:
            DBIT( keyboard[wParam], 0);
            ABIT( keyboard[wParam], 3);
            if( GetBit( keyboard[wParam], 4)){ DBIT( keyboard[wParam], 4); ABIT( keyboard[wParam], 2);}
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
        if(! RegisterClassExA( &wndClass)){ LOG("cant register wnd class") return 0;}
    }

    DWORD wndStyle = WS_VISIBLE;
    if(borderless){ wndStyle |= WS_OVERLAPPEDWINDOW;} else { wndStyle |= WS_POPUP;}

    HWND hwnd = CreateWindowExA
    (
        0, NAV_WND_CLASS, title, wndStyle, 
        0, 0, width, height,
        NULL, NULL, hInst, 0
    );

    if(! hwnd){ LOG("cant create window") return 0;}

    WND* wnd = (WND*)malloc( sizeof( WND));
    wnd->hwnd = hwnd;
    return wnd;
}

void DeleteWND( WND* wnd){ if( wnd != 0){ free( wnd);}}

void ShowMSGBox(char* msg, char* title, int style)
{
    MessageBox( NULL, msg, title, style);
}

char GetKey(char key){ return GBIT( keyboard[key], 0);}
char GetKeyDown(char key){ return GBIT( keyboard[key], 1);}
char GetKeyUp(char key){ return GBIT( keyboard[key], 2);}