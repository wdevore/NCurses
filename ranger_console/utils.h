#pragma once

#include <vector>
#include <sstream>

std::vector<std::string> split_string(std::string& cmdLine);
long int string_to_int(std::string& v);
std::string int_to_hex(long int v, const std::string& header);
std::string int_to_bin(long int v);
long int string_to_int(std::string& v);
int hex_string_to_int(std::string& v);
std::string int_to_bin(long int v, const std::string& header);
