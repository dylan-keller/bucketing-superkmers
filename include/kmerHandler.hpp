#ifndef KMERHANDLER_HPP
#define KMERHANDLER_HPP

#include "fastaReader.hpp"
#include <string>
#include <iostream> // TODO : remove, only for debugging

uint64_t convertToInt(std::string s);

uint64_t nextKmer(std::ifstream& fs, uint64_t prev, uint8_t k);

#endif