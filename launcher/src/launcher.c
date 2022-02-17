#include<nav_log.h>
#include<nav_platform.h>
#include<nav_input.h>

int main()
{
    WND* wnd = CreateWND((char*)"Nav", 600, 480, 1);

    while( UpdateWNDEvents( wnd))
    {
        if( GetKeyUp(0x20))
        {
            LOG("ok");
        }
    }

    DeleteWND( wnd);
    return 0;
}