#include<nav.h>
#include<nav_str.h>

int main( int argc, char** argv)
{
    int argvLen = StrLen( *argv);
    argv[0][ argvLen - 4] = 'd';
    argv[0][ argvLen - 3] = 'l';
    argv[0][ argvLen - 2] = 'l';

    RunNav( argv[0]);
    return 0;
}
