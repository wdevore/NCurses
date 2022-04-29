#include <ncurses.h>
#include <list>
#include <iostream>

#define COLOR_DARK_GRAY 20
#define COLOR_ORANGE 21

void showCPUStatus(std::string& cpu_status) {
	move(1,1);
	printw("CPU Status: %s\n", cpu_status.c_str());
}

void showTimeStep(int timeStep) {
	move(2,1);
	printw("timeStep: %d", timeStep);
}

void showTermCaret() {
	move(LINES-1, 1);
	addch('>');
}

void moveCaretToEndl(int col) {
	move(LINES-1, col);
}

int stepSimulation(int timeStep) {
	timeStep++;
	return timeStep;
}

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

	if (can_change_color() != OK) {
		puts("Term can't change colors");
	}

	init_color(COLOR_DARK_GRAY, 128, 128, 128);
	init_color(COLOR_ORANGE, 255, 127, 0);

	// Change text and background color for the screen
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));

	init_pair(2, COLOR_WHITE, COLOR_ORANGE);

	bool looping = true;
	bool running = false;
	int timeStep = 0;
	char ch;
	int col = 2;
	bool cycleCountEnabled = false;
	int halfCycleCount = 0;
	int stepCnt = 0;

	cbreak();
	nodelay(stdscr, true);
	noecho();

	std::string buf;
	std::string lastCmd;
	std::string cpu_status = "Stopped";

	while (looping) {
		attrset(A_NORMAL);

		showCPUStatus(cpu_status);
		showTimeStep(timeStep);

		napms(10);

		if (running) {
			timeStep = stepSimulation(timeStep);
			stepCnt++;
			if (cycleCountEnabled && stepCnt >= halfCycleCount) {
				running = false;
				cycleCountEnabled = false;
			}
		}

		ch = getch();

		showTermCaret();

		if (ch == '`') {
			looping = false;
			continue;
		} else if (ch == '\n') {
			col = 2;
			move(LINES-1,col);

			if (buf == "") {
				buf = lastCmd;
			}

			if (buf == "run" || buf == "r") {
				cpu_status = "Running";
				running = true;
			} else if (buf == "stop" || buf == "s") {
				cpu_status = "Stopped";
				running = false;
			} else if (buf == "exit") {
				looping = false;
				continue;
			} else if (buf == "half") {
				stepCnt = 0;
				running = true;
				halfCycleCount = 10;
				cycleCountEnabled = true;
			} else if (buf == "full") {
				stepCnt = 0;
				running = true;
				halfCycleCount = 20;
				cycleCountEnabled = true;
			}

			lastCmd = buf;
			// Clear command line
			addstr("                      ");
			buf.clear();	// Clear command now that we have used it
		} else if (ch >= ' ' && ch < '~') { // Allow all normal keys a-z,A-Z...
			col++;
			move(LINES-1, col);
			addch(ch | A_NORMAL);
			buf.push_back(ch);
		}

		moveCaretToEndl(col+1);

		refresh();
	}

	endwin();

	puts("Goodbye ;-)");

	return 0;
}
