#ifndef NAV_INPUT_H
#define NAV_INPUT_H

typedef signed char SCHAR;

enum Mouse
{
    Left = 0,
    Scroll = 1,
    Right = 2,
};

char GetKey(char key);
char GetKeyDown(char key);
char GetKeyUp(char key);
char GetMouseButton(char button);
char GetMouseButtonDown(char button);
char GetMouseButtonUp(char button);

SCHAR GetMouseWheelDelta();

#endif