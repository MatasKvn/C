test.exe : main.c checkSubsets.h checkSubsets.o
	gcc -std=c99 -o test.exe main.c checkSubsets.o

checkSubsets.o : checkSubsets.c checkSubsets.h
	gcc -c -std=c99 checkSubsets.c