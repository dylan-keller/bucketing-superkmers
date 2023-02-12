#include "fastaReader.hpp"
#include "kmerHandler.hpp"
#include <iostream>

using namespace std;

void invalid_message_exit() {
  std::cout << "Expected format is :\n\n"
            << "./main file_in rep_out k m\n\n"
            << "With - file_in : path to a FASTA file\n"
            << "     - file_out : path to a repository where the outputs will be stocked\n"
            << "     - k : k-mer size, integer <= 31\n"
            << "     - m : minimizer size, integer < k\n";
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cout << "FAILED : Invalid number of arguments. ";
    invalid_message_exit();
  }

  uint64_t k = atoi(argv[3]);
  uint64_t m = atoi(argv[4]);

  if ((k==0) || (m==0) || (m>=k)) {
    std::cout << "FAILED : Invalid parameters for k or m. ";
    invalid_message_exit();
  }

  ifstream fs(argv[1]);

  if (!skipFirstLine(fs)) {
    std::cout << "FAILED : Invalid FASTA file. ";
    invalid_message_exit();
  }

  
  /*
  cout << "---------- a" << endl;
  skipFirstLine(fs);
  cout << read1(fs) << read1(fs) << read1(fs) << read1(fs) << read1(fs) << endl;

  cout << "---------- b" << endl;
  cout << argc << " ----- " << argv[0] << " ----- " << argv[1] << endl;

  cout << "---------- c" << endl;
  uint64_t n1 = 10;
  n1 = n1 << 1;
  cout << n1 << endl;

  uint64_t n2 = convertToInt("CCTT");

  cout << n2 << endl;

  cout << "---------- d" << endl;

  n2 &= ~(1 << 1);
  cout << n2 << endl;

  cout << "---------- e" << endl;

  for(int i=0; i<10; i++){
    n2 = nextKmer(fs, n2, 4);
    cout << n2 << endl;
  }
  */

  return 0;
}