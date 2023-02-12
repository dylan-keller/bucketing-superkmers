#ifndef KMERHANDLER_HPP
#define KMERHANDLER_HPP

#include "fastaReader.hpp"
#include <string>

uint8_t convertToInt(char c);
uint64_t convertToInt(std::string s);
std::string convertToString(u_int64_t kmer, uint8_t k);

uint64_t nextKmer(char c, uint64_t prev, uint8_t k);
uint64_t nextKmer(std::ifstream& fs, uint64_t prev, uint8_t k);
void bestMinimiser(uint64_t* mini_and_pos, std::string kmer, uint16_t m);


#endif