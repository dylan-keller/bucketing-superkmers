#include "../include/fastaReader.hpp"

bool skipFirstLine(std::ifstream& fs) {
  if (fs.get() == '>') {
    std::string skipped;
    std::getline(fs, skipped);
    return true;
  }
  return false;
}

char read1(std::ifstream &fs) {
  char res;
  do {
    res = fs.get();
  // } while (res == 'N'); // assuming missing nucleotides are labeled "N", otherwise :
  } while ((res!='A') && (res!='C') && (res!='T') && (res!='G') && (res!=EOF));
  return res;
}