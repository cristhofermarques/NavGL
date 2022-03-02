#ifndef NAV_INPUT_H
#define NAV_INPUT_H

#include<nav_api.h>

NAV_API enum Mouse
{
    Left = 0,
    Scroll = 1,
    Right = 2,
};

NAV_API char GetKey(char key);
NAV_API char GetKeyDown(char key);
NAV_API char GetKeyUp(char key);
NAV_API char GetMouseButton(char button);
NAV_API char GetMouseButtonDown(char button);
NAV_API char GetMouseButtonUp(char button);
NAV_API char GetMouseWheelDelta();


#endif