CC=gcc

CFLAGS= -std=c99 -Wall -Werror -Wextra
LDFLAGS=-lm

all: grade 

version.o: version.c

test.o: test.c

test: version.o test.o
	$(CC) $(CFLAGS) version.o test.o -o test $(LDFLAGS)


grade: test
	./test
	rm *.o test  

