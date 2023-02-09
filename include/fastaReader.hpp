#ifndef FASTAREADER_HPP
#define FASTAREADER_HPP

#include <fstream>
#include <string>

void skipFirstLine(std::ifstream& fs);

char read1(std::ifstream& fs);

#endif