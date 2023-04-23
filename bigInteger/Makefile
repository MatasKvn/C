test.exe : main.c bigInt.h bigInt.o
	gcc -std=c99 -o test.exe main.c bigInt.o

bigInt.o : bigInt.c bigInt.h
	gcc -c -std=c99 bigInt.c