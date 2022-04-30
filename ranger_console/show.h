#pragma once

void showCPUStatus(std::string& cpu_status);
void showTimeStep(int timeStep);
void showTermCaret();

void showRegFile(int row, int values[]);
void showRegister(int row, const std::string& header,  int value);

