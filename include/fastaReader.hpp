#ifndef FASTAREADER_HPP
#define FASTAREADER_HPP

#include <fstream>
#include <string>

bool skipFirstLine(std::ifstream& fs);

char read1(std::ifstream& fs);

#endif