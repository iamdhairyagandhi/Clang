#defining sf
LODU = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow \
         -pedantic-errors -fstack-protector-all 
PROGS = user_interface public01 public02 public03 public04 public05 \
	public06 student_tests

.PHONY: all clean

all: $(PROGS)

clean:
	rm -f *.o $(PROGS) *.tmp

# create executables for all public tests
public01: calendar.o public01.o my_memory_checker_216.o
	$(LODU) calendar.o public01.o my_memory_checker_216.o -o public01

public02: calendar.o public02.o my_memory_checker_216.o
	$(LODU) calendar.o public02.o my_memory_checker_216.o -o public02

public03: calendar.o public03.o my_memory_checker_216.o
	$(LODU) calendar.o public03.o my_memory_checker_216.o -o public03

public04: calendar.o public04.o my_memory_checker_216.o
	$(LODU) calendar.o public04.o my_memory_checker_216.o -o public04

public05: calendar.o public05.o my_memory_checker_216.o
	$(LODU) calendar.o public05.o my_memory_checker_216.o -o public05

public06: calendar.o public06.o my_memory_checker_216.o
	$(LODU) calendar.o public06.o my_memory_checker_216.o -o public06
# create an executable for my student_tests.c
student_tests: student_tests.o my_memory_checker_216.o
	$(LODU) student_tests.o my_memory_checker_216.o -o student_tests

# compile the public tests into object files
public01.o: public01.c event.h calendar.h
	$(LODU) $(CFLAGS) -c public01.c

public02.o: public02.c event.h calendar.h
	$(LODU) $(CFLAGS) -c public02.c

public03.o: public03.c event.h calendar.h
	$(LODU) $(CFLAGS) -c public03.c

public04.o: public04.c event.h calendar.h
	$(LODU) $(CFLAGS) -c public04.c

public05.o: public05.c event.h calendar.h
	$(LODU) $(CFLAGS) -c public05.c

# compile other source files into object files
student_tests.o: student_tests.c event.h calendar.h	
	$(LODU) $(CFLAGS) -c student_tests.c -o student_tests.o

calendar.o: calendar.c calendar.h
	$(LODU) $(CFLAGS) -c calendar.c -o calendar.o

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	$(LODU) $(CFLAGS) -c my_memory_checker_216.c -o my_memory_checker_216.o

# clean: delete all object files and executables
clean:
	echo "Cleaning project4 files"
	rm public01 public02 public03 public04 student_tests ./*.o