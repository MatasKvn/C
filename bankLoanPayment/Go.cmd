if .%USERDOMAIN% == .DESKTOP-0L06FIQ goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path"
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
test.exe 1500 10 5.0 1.0 0 1000 10 30> test.txt