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
	attrset(A_NORMAL);
	printw("CPU Status: ");
	attrset(A_BOLD);
	printw("%s\n", cpu_status.c_str());
}

void showTimeStep(int timeStep) {
	move(2,1);
	attrset(A_NORMAL);
	printw("timeStep: ");
	attrset(A_BOLD);
	printw("%d", timeStep);
}

void showTermCaret() {
	mvaddch(LINES-1, 1, '>');
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
	move(row,40);
	addstr("--- RegFile ---");
	row++;

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

void showRegister(int row, const std::string& header,  int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("%s: ", header.c_str());
	attrset(A_BOLD);
	printw("%s", int_to_hex(value).c_str());
}

// Show mem dump from A to B and ascii
void showMemory(int fromAddr, int toAddr) {
	// Addr           data          Ascii
	// 0x0000000a     0x01010101    hell
}
