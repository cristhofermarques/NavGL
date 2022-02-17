@cls

@windres res\launcher.rc -O coff -o res\launcher.res

@copy ..\engine\bin\nav.dll bin

@gcc -DDEBUG src\launcher.c -I ..\engine\hdr bin\nav.dll res\launcher.res -o bin\launcher.exe