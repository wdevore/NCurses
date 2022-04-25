#include <ncurses.h>

int main() {
	char text[] = "Greetings from Ncurses!";
	char *t;

	initscr();

	t = text;
	while (*t) {
		addch(*t);
		t++;
		refresh();
		napms(100);
	}

	getch();

	endwin();
	return 0;
}
