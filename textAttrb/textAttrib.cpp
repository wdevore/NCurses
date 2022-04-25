#include <ncurses.h>

int main() {
	initscr();

	attron(A_BOLD);
	addstr("This ia test of attributes\n");
	attron(A_BLINK);
	addstr("More text to blink\n");
	attroff(A_BOLD);
	addstr("More text for BOLD\n");
	attrset(A_NORMAL);
	addstr("Back to normal\n");
	refresh();

	getch();

	endwin();
	return 0;
}
