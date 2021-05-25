luhn_analyzer: process.o files.o errors.o main.o io.o strings.o adt.o
	gcc process.o  adt.o files.o errors.o main.o io.o strings.o  -o luhn_analyzer

main.o: errors.h files.h process.h main.h main.c
	gcc -c main.c

adt.o: errors.h adt.h adt.c
	gcc -c adt.c

process.o: errors.h io.h process.h process.c adt.h
	gcc -c process.c
	
io.o: errors.h io.h strings.h io.c adt.h adt.c
	gcc -c io.c

strings.o: errors.h strings.c
	gcc -c strings.c

files.o: files.h errors.h files.c
	gcc -c files.c

errors.o: errors.h errors.c
	gcc -c errors.c
