#include "../include/fastaReader.hpp"

void skipFirstLine(std::ifstream& fs) {
  if (fs.get() == '>') {
    std::string skipped;
    std::getline(fs, skipped);
  }
}

char read1(std::ifstream &fs) {
  char res;
  do {
    res = fs.get();
  } while (res == 'N'); // assuming missing nucleotides are labeled "N" maybe fix by != A,C,G,T
  return res;
}