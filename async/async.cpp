#include <ncurses.h>
#include <list>
#include <iostream>

#define COLOR_DARK_GRAY 20
#define COLOR_ORANGE 21

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

	init_color(COLOR_DARK_GRAY, 128, 128, 128);
	init_color(COLOR_ORANGE, 255, 127, 0);

	// Change text and background color for the screen
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));

	init_pair(2, COLOR_WHITE, COLOR_ORANGE);

	printw("Starting loop.\n");

	bool looping = true;
	int count = 0;
	char ch;
	int col = 20;

	cbreak();
	nodelay(stdscr, true);
	noecho();

	std::string buf;

	while (looping) {
		move(2,0);
		attrset(A_NORMAL);
		printw("%d count\n", count);
		napms(1);
		count++;
		ch = getch();

		attrset(A_NORMAL);
		move(3,20);
		addch('>');

		if (ch == '`') {
			looping = false;
			continue;
		} else if (ch == '\n') {
			move(4,0);
			col = 20;
			if (buf == "run") {
				move(5,0);
				addstr(buf.c_str());
			}
			// Delete and then insert blanks
			//for (auto &ch : buf) {
			//	delch();
			//}
			buf.clear();
		} else if (ch >= 'a' && ch <= 'z') {
			col++;
			move(3, col);
			addch(ch | A_NORMAL);
			buf.push_back(ch);
			refresh();
		}

		move(3, col+1);

		refresh();
	}

	endwin();

	puts("Goodbye ;-)");

	return 0;
}
