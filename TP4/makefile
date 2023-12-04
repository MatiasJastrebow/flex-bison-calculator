cflags = -g -Wall -pedantic-errors -D_GNU_SOURCE -Wno-switch -std=c2x

calc : scanner.o parser.o calc.o main.o
	gcc calc.o main.o parser.o scanner.o -o calc -lfl -lm

scanner.o : scanner.c scanner.h
	gcc $(cflags) -c scanner.c

scanner.c scanner.h : scanner.l parser.h calc.h
	flex scanner.l

parser.o : parser.c parser.h
	gcc $(cflags) -c parser.c

parser.c parser.h : parser.y scanner.h calc.h
	bison parser.y

calc.o : calc.c calc.h parser.h
	gcc $(cflags) -c calc.c

main.o: main.c scanner.h parser.h calc.h 
	gcc $(cflags) -c main.c

clean :
		rm scanner.c scanner.h scanner.o parser.c parser.h parser.o calc.o main.o calc