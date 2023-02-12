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

  uint16_t k = (uint16_t)atoi(argv[3]);
  uint16_t m = (uint16_t)atoi(argv[4]);

  if ((k<=0) || (k>31) || (m<=0) || (m>=k)) {
    std::cout << "FAILED : Invalid parameters for k or m. ";
    invalid_message_exit();
  }

  ifstream fs(argv[1]);

  if (!skipFirstLine(fs)) {
    std::cout << "FAILED : Invalid FASTA file. ";
    invalid_message_exit();
  }

  
  ofstream outf;
  outf.open(argv[2]);

  string s = "";
  char c;
  uint16_t mmer_pos;
  uint64_t mmer_mini=0;
  uint64_t mmer_cur=0;
  uint64_t kmer_cur=0;

  s += read1(fs);

  for(int w=0; w<100; w++){
    mmer_pos = 0;

    for(uint16_t i=1; i<k; i++){
      c = read1(fs);
      s += c;

      // TODO : put if (i>m-1) else if (i==m-1) faster

      if (i>=m-1){
        if (i==m-1){
          mmer_mini = convertToInt(s);
          mmer_cur = mmer_mini;
        } else {
          mmer_cur = nextKmer(c, mmer_cur, m);
          if (mmer_cur < mmer_mini) {
            mmer_pos = i-m+1;
            mmer_mini = mmer_cur;
          }
        }
      }
    }
    kmer_cur = convertToInt(s);
    cout << s;
    cout << " pos:" << mmer_pos << " mini:" << mmer_mini << endl; //debugging

    outf << s;
    s="";

    c = read1(fs);
    
    while (mmer_pos>0){
      kmer_cur = nextKmer(c, kmer_cur, k); 
      mmer_cur = nextKmer(c, mmer_cur, m);
      mmer_pos--;

      if (mmer_cur < mmer_mini) {
        outf << s << "\n";
        outf << convertToString(kmer_cur, k);
        s = "";
        mmer_mini = mmer_cur;
        mmer_pos=0;
      }

      s += c;

      c = read1(fs);
    }
    


  }
  
  
  // OLD TESTS

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

  fs.close();
  outf.close();
  return 0;
}