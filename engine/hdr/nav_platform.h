#ifndef NAV_PLATFORM_H
#define NAV_PLATFORM_H


struct Wnd;
typedef struct Wnd WND;

void ShowMSGBox( char* msg, char* title, int style);

WND* CreateWND( char* title, int width, int height, char borderless);
void DeleteWND(WND* wnd);
void SetWNDUndestructible( WND* wnd, char state);
char UpdateWNDEvents( WND* wnd);
char GetWNDFocus( WND* wnd);


#endif