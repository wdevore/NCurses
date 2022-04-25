#include <ncurses.h>

int main() {
	initscr();

	if (!has_colors()) {
		endwin();
		puts("Term can't do colors");
		return 1;
	}

	if (start_color() != OK) {
		endwin();
		puts("Term can't start colors");
		return 1;
	}

	// Change text and background color for the screen
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));

	printw("Colors inited.\n");
	printw("%d colors available.\n", COLORS);
	printw("%d color pairs.\n", COLOR_PAIRS);

	init_pair(2, COLOR_YELLOW, COLOR_RED);
	attrset(COLOR_PAIR(2) | A_BOLD);
	addstr("Alert! Alert!\n");

	attrset(A_NORMAL);
	addstr("Just kidding ;-)\n");

	int y,x;
	getmaxyx(stdscr, y, x);
	printw("Window is %d rows by %d columns.\n", y,x);

	refresh();

	getch();

	endwin();
	return 0;
}
