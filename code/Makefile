CC=gcc
CFLAGS=-I.

all: main

main: main.o functions.o data_storage.o datastructures.o
	$(CC) -o main main.o functions.o data_storage.o datastructures.o

main.o: main.c
	$(CC) -c main.c

functions.o: functions.c
	$(CC) -c functions.c

data_storage.o: data_storage.c

	$(CC) -c data_storage.c datastrucutres.h

 datastructures.o: datastructures.h
	$(CC) -c datastructures.h
clean:
	rm -f *.o main
