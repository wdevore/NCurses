#pragma once

void showCPUStatus(std::string& cpu_status);
void showTimeStep(int timeStep);
void showTermCaret();

void showPC(int row, int value);
void showPCPrior(int row, int value);
void showIR(int row, int value);
void showALUFlags(int row, int value);
void showRegFile(int row, int values[]);

