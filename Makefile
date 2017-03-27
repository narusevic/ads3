all: bigInteger

bigInteger: bigIntegerMain.o bigInteger.o
	gcc bigIntegerMain.o bigInteger.o -o bigInteger

bigIntegerMain.o: bigIntegerMain.c
	gcc -c bigIntegerMain.c

bigInteger.o: bigInteger.c
	gcc -c bigInteger.c

