#include "kmerHandler.hpp"

uint64_t convertToInt(std::string s) {
  uint64_t res = 0;

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
  std::cout << "[" << c;

  // then we shift left twice the previous kmer
  std::cout << " prev:" << prev ;
  uint64_t res = prev << 2;
  std::cout << " res1:" << res;

  // then we erase the k*2 and k*2+1 bits
  res &= ~(1 << k * 2);
  res &= ~(1 << ((k * 2) + 1));
  std::cout << " res2:" << res;

  // finally we add the number corresponding to the read letter
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
  std::cout << " res3:" << res <<"]";

  // TODO : remove std::cout (debugging)
  return res;
}