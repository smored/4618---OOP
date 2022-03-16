#makefile

# The compiler to use is for C++
CC=g++
# The compiler options are (all warnings)
CFLAGS=-Wall -c
# The linker options are (all warnings)
LDFLAGS=-Wall

all: Source

Source: Source.o CStudent.o CCourse.o
	$(CC) $(LDFLAGS) Source.o CCourse.o CStudent.o -o main

CStudent.o: CStudent.cpp
	$(CC) $(CFLAGS) CStudent.cpp

CCourse.o: CCourse.cpp
	$(CC) $(CFLAGS) CCourse.cpp

Source.o: Source.cpp
	$(CC) $(CFLAGS) Source.cpp

clean:
	rm *o main
