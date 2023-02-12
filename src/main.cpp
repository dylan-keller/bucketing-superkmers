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
  uint16_t mmer_pos=0;
  uint64_t mmer_mini=0;
  uint64_t mmer_cur=0;
  uint64_t kmer_cur=0;
  uint64_t mini_and_pos[2];

    // when we first start, we have to create the first kmer.
    for(uint16_t i=0; i<k; i++){
      // so, we read chars one by one until we have enough letters
      c = read1(fs);
      // we will use the string s to store the kmer.
      s += c;

      // if we have enough letters to form mmers : 
      if (i>=m-1){
        // if we have exactly m chars, we form the first mmer.
        if (i==m-1){
          mmer_mini = convertToInt(s);
          mmer_cur = mmer_mini;
        // if we have more, we find the minimiser and note its position.
        } else { 
          mmer_cur = nextKmer(c, mmer_cur, m);
          if (mmer_cur < mmer_mini) {
            mmer_pos = i-m+1;
            mmer_mini = mmer_cur;
          }
        }
      }
    }
    // we use this variable to save the current kmer.
    kmer_cur = convertToInt(s);
    // the very first kmer is always going to be at the beginning of the file.
    outf << s;   

    // TODO : remove debugging
    //cout << s;
    //cout << " pos:" << mmer_pos << " mini:" << mmer_mini << endl; //debugging

    // now, we will use the s variable to add text in the output file.
    // let's clear it since we already wrote the first kmer into the file.
    s="";

    c = read1(fs);

    // now, let's continue reading until the end of the file
    while(c!=EOF){
      // we update the current kmer and mmer
      kmer_cur = nextKmer(c, kmer_cur, k); 
      mmer_cur = nextKmer(c, mmer_cur, m);

      // if the minimiser is still part of the kmer :
      if (mmer_pos>0){
        // since we advanced 1 letter, we decrease mmer_pos
        mmer_pos--;

        // if we find a better minimiser (on the right) :
        if (mmer_cur < mmer_mini) {
          // we end the bucket : we print the collected chars and newline
          outf << s << "\n";
          // we start a new bucket with the current kmer
          outf << convertToString(kmer_cur, k);
          // we clear out the string s variable
          s = "";
          // and we update the minimser status
          mmer_mini = mmer_cur;
          // since the new minimser is on the right,
          // its first letter is at the k-m th letter of the current kmer
          mmer_pos = k-m;
        } else {
          // if we didn't find a better minimser, we add the new letter to the bucket
          s += c;
        }
      // otherwise, the bucket is finished :
      } else {
        // we end the bucket : we print the collected chars and newline
        outf << s << "\n";
        // we start a new bucket with the current kmer
        s = convertToString(kmer_cur, k);
        outf << s;
        
        // and we update the minimser status
        bestMinimiser(mini_and_pos, s, m);
        mmer_mini = mini_and_pos[0];
        mmer_pos = mini_and_pos[1];

        // we clear out the string s variable
        s = "";
      }

      c = read1(fs);
    }
 
  fs.close();
  outf.close();
  return 0;
}