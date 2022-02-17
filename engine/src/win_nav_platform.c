#include<windows.h>
#include<nav_platform.h>
#include<nav_input.h>
#include<nav_log.h>

void ShowMSGBox(char* msg, char* title, int style)
{
    MessageBox( NULL, msg, title, style);
}