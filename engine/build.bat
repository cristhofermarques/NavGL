@cls

@gcc -D DEBUG -I hdr\ -c src\win_nav_platform.c -o bin\platform.o

@gcc -D DEBUG -shared -fpic -o bin\nav.dll bin\platform.o -lgdi32 -luser32 -Wl,--out-implib,bin\libnav.a

@del bin\platform.o