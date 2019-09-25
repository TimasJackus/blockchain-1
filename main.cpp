#include <iostream>
#include <string.h>
#include <bitset>
#include <cmath>
const int HASH_LENGTH = 64;

long calcVal(long val) {
  if(val > 99999999) {
    while(val > 99999999) {
      val = val / 7;
    }
    return val;
  }
  if(val < 10000000) {
    while(val < 99999999) {
      val = val * 7;
    }
    return val;
  }
  return val;

}

long getCharsSum(std::string str) {
  long sum = 0;
  for(int i = 0; i < str.length(); i++) {
    sum += int(str[i]) * (i + 1);
  }
  return sum;
}

std::string hash(std::string input) {
  std::bitset<HASH_LENGTH> bs[4];
  for(int i = 0; i < 4; i++) {
    bs[i] = std::bitset<HASH_LENGTH>{}.set();
  }

  long test = calcVal(getCharsSum(input));
  for(int i = 0; i < 4; i++) {
    long val = test * (i + 3);
    while (val >= 64) {
      int index = val % 64;
      val = val / 2.5;
      bs[i] = bs[i].test(index) == 1 ? bs[i].reset(index) : bs[i].set(index);
      if (index % 3 == 0) {
        bs[i].flip();
      }
    }
  }
  for(int i = 0; i < 4; i++) {
    printf("%08x", bs[i].to_ullong());
  }
  std::cout << std::endl;
  return input;
}

int main() {
  hash("lietuva");
  return 0;
}