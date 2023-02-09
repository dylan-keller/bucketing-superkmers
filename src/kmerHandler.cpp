#include "kmerHandler.hpp"

uint64_t convertToInt(std::string s) {
  uint64_t res = 0;

  for (char &c : s) {
    res = res << 2; // NOTE : yes, first shift is unecessary
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