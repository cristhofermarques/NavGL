@cls

@windres res\nav.rc -O coff -o res\nav.res

@gcc -D DEBUG -I hdr\ -c src\win_nav_platform.c -lgdi32 -luser32 -o bin\platform.o

@gcc -D DEBUG -shared -fpic -o bin\nav.dll   bin\platform.o -Wl,--out-implib,bin\libnav.a

@del bin\platform.o