CC = gcc
CFLAGS =  -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all
PROGS = d8sh

.PHONY: all clean


d8sh: lexer.o parser.tab.o executor.o d8sh.o
	$(CC) -o d8sh  lexer.o parser.tab.o executor.o d8sh.o -lreadline

lexer.o: lexer.h command.h
	$(CC) $(CFLAGS) -c lexer.c 
parser.tab.o: parser.tab.h command.h
	$(CC) $(CFLAGS) -c parser.tab.c
executor.o: executor.h command.h
	$(CC) $(CFLAGS) -c executor.c
d8sh.o:  command.h executor.h
	$(CC) $(CFLAGS) -c d8sh.c

clean:
	rm -f *.o $(PROGS) a.out