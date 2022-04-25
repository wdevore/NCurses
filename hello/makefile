CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lncurses

PROG = hello
SOURCE = goodbye.cpp

clean:
	$(RM) *.o $(PROG)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(PROG): goodbye.o 
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
