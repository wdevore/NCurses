#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset>

std::string int_to_hex(int v) {
	std::stringstream stream;
	stream << "0x"
			<< std::setfill('0') << std::setw(sizeof(int)*2)
			<< std::hex << v;
	return stream.str();
}

std::string int_to_bin(int v) {
	std::stringstream stream;
	stream << std::bitset<4>(v);
	return stream.str();
}

void showCPUStatus(std::string& cpu_status) {
	move(1,1);
	printw("CPU Status: %s\n", cpu_status.c_str());
}

void showTimeStep(int timeStep) {
	move(2,1);
	printw("timeStep: %d", timeStep);
}

void showTermCaret() {
	mvaddch(LINES-1, 1, '>');
}

void showPC(int row, int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("PC: ");
	attrset(A_BOLD);
	printw("%s", int_to_hex(value).c_str());
}

void showPCPrior(int row, int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("PCPrior: ");
	attrset(A_BOLD);
	printw("%s", int_to_hex(value).c_str());
}

void showIR(int row, int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("IR: ");
	attrset(A_BOLD);
	printw("%s", int_to_hex(value).c_str());
}

void showALUFlags(int row, int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("Flags: ");
	attrset(A_BOLD);
	std::string bits = int_to_bin(value);

	if (bits[0] == '0')
		printw("-");
	else
		printw("V");

	if (bits[1] == '0')
		printw("-");
	else
		printw("N");

	if (bits[2] == '0')
		printw("-");
	else
		printw("C");

	if (bits[3] == '0')
		printw("-");
	else
		printw("Z");
}

void showRegFile(int row, int values[32]) {
	for (int i = 0; i < 32; i++) {
		move(row,40);
		attrset(A_NORMAL);
		if (i < 10)
			printw(" x%d: ", i);
		else
			printw("x%d: ", i);
		attrset(A_BOLD);
		printw("%s", int_to_hex(values[i]).c_str());
		row++;
	}
}
