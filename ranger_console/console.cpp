#include <ncurses.h>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>

#include "show.h"
#include "utils.h"

#define COLOR_DARK_GRAY 20
#define COLOR_ORANGE 21

#define ESC '\x1B'

void clearCmdLine() {
	move(LINES-1, 2);
	clrtoeol();
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
	int stepCycleCount = 0;
	int stepCnt = 0;

	long int regFile[] = {0xdeedbeaf,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
	long int mem[] = {
		0x48454c50,0xc0debabe,14,15,16,17,18,19,20,128,129,130,131,132,133,
		0x4e4f5045,135,256,257,258,259,2,3,4,5,6,7,8,9,10,11,12,13,128,129,130,131,132,133,128,129,130,131,132,133,
		0x534f5550,135,256,257,258,777,7,7,7,5,6,8,8,8,
		0x44495254,15,16,17,18,19,20,128,129,130,555,444,333,
		0x454e4421
	};
	int lenMem = sizeof(mem)/sizeof(mem[0]);

	// This enables aysnc input. It allows the simulator to run while capture key input.
	nodelay(stdscr, true);
	// We don't want characters to appear where ever the cursor is at,
	// only at the area we control.
	noecho();

	std::string buf;
	std::string lastCmd;
	std::string cpu_status = "Stopped";
	WINDOW *helpWin;
	bool helpWinVisible = false;

	long int fromAddr = 0;
	long int toAddr = 20;
	int selectedReg = 0;

	while (looping) {
		attrset(A_NORMAL);

		napms(10);

		if (running) {
			timeStep = stepSimulation(timeStep);
			stepCnt++;
			if (cycleCountEnabled && stepCnt >= stepCycleCount) {
				running = false;
				cycleCountEnabled = false;
			}
		}

		ch = getch();

		if (ch == ESC) {
			// Close popup window
			if (helpWin != NULL) {
				delwin(helpWin);
				touchwin(stdscr);
				helpWinVisible = false;
			}
		} else if (ch == '`') {
			looping = false;
			continue;
		} else if (ch == '\n') {
			col = 2;
			move(LINES-1,col);

			// If the user hit return on a blank line then repeat previous command
			if (buf == "") {
				buf = lastCmd;
			}

			// If there was no previous command then skip everything
			if (buf == "") {
				continue;
			}

			if (buf == "run" || buf == "r") {
				cpu_status = "Running";
				running = true;
			} else if (buf == "stop" || buf == "s") {
				cpu_status = "Stopped";
				running = false;
			} else if (buf == "exit" || buf == "e") {
				looping = false;
				continue;
			} else if (buf == "reset") {
				running = true;
				stepCycleCount = 40;
				cycleCountEnabled = true;
				// Enable cpu reset pin and wait for reset-complete
			} else if (buf == "half") {
				stepCnt = 0;
				running = true;
				stepCycleCount = 10;
				cycleCountEnabled = true;
			} else if (buf == "full") {
				stepCnt = 0;
				running = true;
				stepCycleCount = 20;
				cycleCountEnabled = true;
			} else if (buf == "step" || buf == "t") {
				stepCnt = 0;
				running = true;
				stepCycleCount = 1;
				cycleCountEnabled = true;
			} else if (buf.rfind("sel", 0) == 0) {
				std::vector<std::string> fields = split_string(buf);
				if (fields.size() > 1) {
					selectedReg = string_to_int(fields[1]);
				} else {
					selectedReg = 0;
				}
			} else if (buf.rfind("mem", 0) == 0) {
				// Extract from/to values
				std::vector<std::string> fields = split_string(buf);
				if (fields.size() > 1) {
					if (fields[1].find("0x") != std::string::npos)
						fromAddr = hex_string_to_int(fields[1]);
					else
						fromAddr = string_to_int(fields[1]);
				} else {
					fromAddr = 0;
				}
				clearMemory();
				showMemory(fromAddr, lenMem, mem);
			} else if (buf == "clear") {
				clearMemory();
			} else if (buf == "help" || buf == "h") {
				// Display help window
				helpWin = newwin(20, 50, 10, 40);
				if (helpWin != NULL) {
					wattrset(helpWin, A_BOLD);
					mvwaddstr(helpWin, 1,1,"---------- Help -----------\n");
					wattrset(helpWin, A_NORMAL);
					waddstr(helpWin, " run/r = run simulation\n");
					waddstr(helpWin, " stop/s = stop simulation\n");
					waddstr(helpWin, " exit/e = exit to console\n");
					waddstr(helpWin, " half = half clock cycle\n");
					waddstr(helpWin, " full = full clock cycle\n");
					waddstr(helpWin, " step = steps a single time unit\n");
					waddstr(helpWin, " mem = mem <fromAddr>\n");
					waddstr(helpWin, " reset = reset CPU\n");
					waddstr(helpWin, " clear = clear memory display area\n");
					wborder(helpWin, '|', '|', '-', '-', '.','.','.','.');
					wrefresh(helpWin);
					helpWinVisible = true;
				} else {
					mvaddstr(10, 10, "oops");
				}
			}

			lastCmd = buf;
			clearCmdLine();
			buf.clear();	// Clear command now that we have used it
		} else if (ch >= ' ' && ch < '~') { // Allow all normal keys a-z,A-Z...
			col++;
			move(LINES-1, col);
			addch(ch | A_NORMAL);
			buf.push_back(ch);
		}

		if (!helpWinVisible) {
			showCPUStatus(cpu_status);
			showTimeStep(timeStep);

			showTermCaret();

			showRegister(3, "PC", 128);
			showRegister(4, "PCPrior", 1024);
			showRegister(5, "IR", 128+64);
			showRegister(6, "ALUOut", 1234);
			showRegister(7, "MDR", 999);
			showRegister(8, "RS1", 666);
			showRegister(9, "RS2", 777);
			showALUFlags(10, 9); 
			showRegFile(1, regFile);
			showRegisterBin(11, "Reg", regFile[selectedReg]);
			moveCaretToEndl(col+1);

			refresh();
		}
	}

	if (helpWin != NULL)
		delwin(helpWin);

	endwin();

	puts("Goodbye ;-)");

	return 0;
}
