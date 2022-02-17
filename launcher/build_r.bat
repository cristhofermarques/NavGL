@cls

copy ..\engine\bin\nav.dll bin

@gcc src\launcher.c -I ..\engine\hdr bin\nav.dll -o bin\launcher.exe