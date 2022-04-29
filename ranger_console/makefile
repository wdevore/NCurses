CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lncurses -lstdc++

PROG = console
SOURCE = $(PROG).cpp

clean:
	$(RM) *.o $(PROG)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(PROG): $(PROG).o 
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
