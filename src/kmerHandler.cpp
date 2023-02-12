#include "kmerHandler.hpp"

uint8_t convertToInt(char c){
  switch(c){
    case 'C' : return 1;
    case 'T' : return 2;
    case 'G' : return 3;
  }
  return 0;
}

uint64_t convertToInt(std::string s) {
  uint64_t res = 0;

  // TODO : replace code here with convertToInt(char c) and see if faster

  for (char &c : s) {
    res = res << 2; // NOTE : yes, first shift is unecessary.
    switch (c) {
    case 'C':
      res += 1;
      break;
    case 'T':
      res += 2;
      break;
    case 'G':
      res += 3;
      break;
    }; // NOTE : no case 'A' since its value is 0
  }

  return res;
}

uint64_t nextKmer(std::ifstream &fs, uint64_t prev, uint8_t k) {
  // first we read the next char in the file
  char c = read1(fs);

  // then we shift left twice the previous kmer
  uint64_t res = prev << 2;

  // then we erase the k*2 and k*2+1 bits
  res &= ~(1 << k * 2);
  res &= ~(1 << ((k * 2) + 1));

  // finally we add the number corresponding to the read letter

  // TODO : replace code here with convertToInt(char c) and see if faster

  switch (c) {
  case 'C':
    res += 1;
    break;
  case 'T':
    res += 2;
    break;
  case 'G':
    res += 3;
    break;
  };

  // TODO : case EOF. is exit(0) acceptable ? by the time we reach EOF we got all mmers

  return res;
}