#include <iostream>
#include "fastaReader.hpp"
#include "kmerHandler.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  /*if (argc != 4) {
    std::cout << "Invalid arguments. Expected format is :\n"
              << "' ./main file_in rep_out k m '\n"
              << "With - file_in : path to a FASTA file\n"
              << "     - file_out : path to a repository where the outputs will be stocked\n"
              << "     - k : k-mer size, integer <= 31\n"
              << "     - m : minimizer size, integer < k";
              exit(1);
  }*/

  ifstream fs("../../fastafiles/sequence.fasta");
  cout << "a" << endl;
  skipFirstLine(fs);
  cout << "b" << endl;
  cout << read1(fs) << read1(fs) << read1(fs) << endl;

  uint64_t n = 10;
  n = n << 1;
  cout << n << endl;

  cout << convertToInt("ACTT") << endl;

  return 0;
}