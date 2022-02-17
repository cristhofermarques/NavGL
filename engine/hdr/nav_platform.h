#ifndef NAV_PLATFORM_H
#define NAV_PLATFORM_H

void ShowMSGBox( char* msg, char* title, int style);

typedef struct WND WND;

WND* CreateWND( char* title, int width, int height, char borderless);

void DeleteWND(WND* wnd);
void SetWNDUndestructible( WND* wnd, char state);

char UptateWNDEnvets( WND* wnd);
char GetWNDFocus( WND* wnd);

#endif