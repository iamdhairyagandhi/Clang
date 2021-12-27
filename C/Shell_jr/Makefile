# provide a makefile with a target called shell_jr that 
# creates the executable shell_jr
CC = gcc
CFLAGS = -g -Wall -O0 -Werror -Wshadow -Wwrite-strings
PROGS = shell_jr

.PHONY: all clean

all: $(PROGS)

shell_jr: shell_jr.o
	$(CC) -o shell_jr shell_jr.o

shell_jr.o: shell_jr.c
	$(CC) $(CFLAGS) -c shell_jr.c

clean:
	rm -f *.o $(PROGS)
