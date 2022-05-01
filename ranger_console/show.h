#pragma once

void showCPUStatus(std::string& cpu_status);
void showTimeStep(int timeStep);
void showTermCaret();

void showRegFile(int row, long int values[]);
void showRegister(int row, const std::string& header,  int value);
void showALUFlags(int row, int value);

void showMemory(long int fromAddr, int memLen, long int mem[]);
void clearMemory();
