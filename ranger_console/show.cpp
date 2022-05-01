#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset>

#include "utils.h"

void showCPUStatus(std::string& cpu_status) {
	move(1,1);
	attrset(A_NORMAL);
	printw("CPU Status: ");
	attrset(A_BOLD);
//	printw("%s\n", cpu_status.c_str());
	printw("%s", cpu_status.c_str());
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

void showRegFile(int row, long int values[32]) {
	int col = 50;
	mvaddstr(row, col, "--- RegFile ---");
	row++;

	for (int i = 0; i < 32; i++) {
		move(row,col);
		attrset(A_NORMAL);
		if (i < 10)
			printw(" x%d: ", i);
		else
			printw("x%d: ", i);
		attrset(A_BOLD);
		printw("%s", int_to_hex(values[i], "").c_str());
		row++;
	}
}

void showRegister(int row, const std::string& header,  int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("%s: ", header.c_str());
	attrset(A_BOLD);
	printw("%s", int_to_hex(value, "0x").c_str());
}

void showRegisterBin(int row, const std::string& header,  int value) {
	move(row,1);
	attrset(A_NORMAL);
	printw("%s: ", header.c_str());
	attrset(A_BOLD);
	printw("%s", int_to_bin(value, "").c_str());
}

// Clear memory display area
void clearMemory() {
	int row = 2;
	for (int i = 0; i < 32; i++) {
		move(row,60);
		clrtoeol();
		row++;
	}
}

// Show mem dump from A to B and ascii
void showMemory(long int fromAddr, int memLen, long int mem[]) {
	// Addr           data          Ascii
	// 0x0000000a     0x01010101    ..ll
	int row = 1;
	int col = 70;

	mvaddstr(row, col, " ---------- Memory -------");
	row++;

	// Check if the fromAddr+memLen > memLen
	int toAddr = fromAddr + 32;
	if (toAddr > memLen) {
		toAddr = memLen;
	}

	for (int i = fromAddr; i < toAddr; i++) {
		move(row,col);

		attrset(A_NORMAL);
		printw("%s: ", int_to_hex(i, "0x").c_str());

		attrset(A_BOLD);
		std::string data = int_to_hex(mem[i], "");
		printw("%s  ", data.c_str());

		// Display text column
		std::string bye = {data[0], data[1]};
		int bt = hex_string_to_int(bye);
		if (bt >= 32 && bt <= 126)
			printw("%c", bt);
		else
			printw(".");

		bye = {data[2], data[3]};
		bt = hex_string_to_int(bye);
		if (bt >= 32 && bt <= 126)
			printw("%c", bt);
		else
			printw(".");

		bye = {data[4], data[5]};
		bt = hex_string_to_int(bye);
		if (bt >= 32 && bt <= 126)
			printw("%c", bt);
		else
			printw(".");

		bye = {data[6], data[7]};
		bt = hex_string_to_int(bye);
		if (bt >= 32 && bt <= 126)
			printw("%c", bt);
		else
			printw(".");

		row++;
	}
}
