#ifndef KMERHANDLER_HPP
#define KMERHANDLER_HPP

#include "fastaReader.hpp"
#include <string>

uint8_t converToInt(char c);
uint64_t convertToInt(std::string s);

uint64_t nextKmer(std::ifstream& fs, uint64_t prev, uint8_t k);

#endif