#include "kmerHandler.hpp"

uint8_t convertToInt(char c) {
  switch (c) {
  case 'C':
    return 1;
  case 'T':
    return 2;
  case 'G':
    return 3;
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

std::string convertToString(u_int64_t kmer, uint8_t k) {
  std::string res = "";
  char c;

  for (uint8_t i = 0; i < k; i++) {
    switch (kmer % 4) {
    case 0:
      c = 'A';
      break;
    case 1:
      c = 'C';
      break;
    case 2:
      c = 'T';
      break;
    case 3:
      c = 'G';
      break;
    }
    res.insert(res.begin(), c);

    kmer = kmer >> 2;
  }

  return res;
}

uint64_t nextKmer(char c, uint64_t prev, uint8_t k) {
  // first, we take the previous kmer.
  uint64_t res = prev;

  // we erase the 2k-2th and 2k-1th bits.
  // this is equivalent to erasing the leftmost letter.
  res &= ~(1UL << (k - 1) * 2);
  res &= ~(1UL << ((k * 2) - 1));

  // then we shift left twice.
  // this is equivalent to moving all the letters left once.
  res = res << 2;

  // finally we add the number corresponding to the new letter.
  // this is equivalent to adding the new letter on the right.
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

  // TODO : replace code here with convertToInt(char c) and see if faster

  // TODO : case EOF. is exit(0) acceptable ? by the time we reach EOF we got
  // all mmers

  return res;
}

uint64_t nextKmer(std::ifstream &fs, uint64_t prev, uint8_t k) {
  char c = read1(fs);
  return nextKmer(c, prev, k);
}

void bestMinimiser(uint64_t *mini_and_pos, std::string kmer, uint16_t m) {
  uint64_t mmer_cur = convertToInt(kmer.substr(0, m));
  mini_and_pos[0] = mmer_cur;
  mini_and_pos[1] = 0;

  for (uint8_t i = m; i < kmer.length(); i++) {
    mmer_cur = nextKmer(kmer[i], mmer_cur, m);
    if (mmer_cur < mini_and_pos[0]) {
      mini_and_pos[0] = mmer_cur;
      mini_and_pos[1] = i-m+1;
    }
  }
}