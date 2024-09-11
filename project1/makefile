CFLAGS = -g -Wall 
CC = g++

objects = param.o parse.o myshell.o

myshell: $(objects)
	$(CC) -o myshell $(objects)

param.o: param.cpp param.hpp
	$(CC) $(CFLAGS) -c param.cpp

parse.o: parse.cpp parse.hpp
	$(CC) $(CFLAGS) -c parse.cpp

myshell.o: myshell.cpp param.hpp parse.hpp
	$(CC) $(CFLAGS) -c myshell.cpp

.PHONY: clean
clean:
	 rm -f myshell $(objects)
