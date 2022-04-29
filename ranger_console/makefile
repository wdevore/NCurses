CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lncurses -lstdc++

PROG = console
SOURCE = $(PROG).cpp \
	show.cpp

clean:
	$(RM) *.o $(PROG)

$(PROG): console.o show.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
