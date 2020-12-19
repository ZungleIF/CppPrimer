#include "ch_17.h"
using namespace std;
bitset<6> bit_num[] = { 1, 2, 3, 5, 8, 13, 21 };
void ch17_10() {
  bitset<6> temp;
  for (auto b : bit_num) {
    temp |= b;
  }
}