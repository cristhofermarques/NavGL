#include<nav_platform.h>
#include<nav_game.h>
#include<nav_str.h>
#include<nav_api.h>
#include<nav_log.h>
#include<stdlib.h>

int main( int argc, char** argv)
{
    int argvLen = StrLen( *argv);

    char* gameLibPath = malloc( argvLen * sizeof(char));

    for(int i = 0; i < argvLen; i++)
    {
        gameLibPath[i] = (*argv)[i];
    }
    gameLibPath[ argvLen - 4] = 'd';
    gameLibPath[ argvLen - 3] = 'l';
    gameLibPath[ argvLen - 2] = 'l';

    RunEngine( gameLibPath);
    free(gameLibPath);
    return 0;
}
