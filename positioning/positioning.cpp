#include <ncurses.h>

int main() {
	char t1[] = "Greetings from Ncurses!";
	char t2[] = "Hello world";

	initscr();

	addstr(t1);
	addstr(t2);

	move(2,0);
	addstr("Today is today");

	refresh();

	getch();

	endwin();
	return 0;
}
