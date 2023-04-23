test.exe : main.c queue.h queue.o bankLoanPayment.h bankLoanPayment.o
	gcc -std=c99 -o test.exe main.c queue.o bankLoanPayment.o

queue.o : queue.c queue.h
	gcc -c -std=c99 queue.c

bankLoanPayment.o : bankLoanPayment.c bankLoanPayment.h
	gcc -c -std=c99 bankLoanPayment.c