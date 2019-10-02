#include <iostream>
#include <string.h>
#include <fstream>
#include <bitset>
#include <cmath>
const int HASH_LENGTH = 64;

long calcVal(long val) {
  if(val < 1000000000) {
    while(val < 1000000000) {
      val = val * 7;
    }
    return val;
  }
  return val;

}

long getCharsSum(std::string str) {
  long sum = 0;
  for(int i = 0; i < str.length(); i++) {
    // sum += (str.length() + int(str[i]) + (i + 3)) * 3;
    sum += int(str[i]) + (i + 1);
  }
  return sum;
}

void hash(std::string input) {
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
  char buffer[32];
  sprintf(buffer, "%08x%08x%08x%08x", bs[0].to_ullong(), bs[1].to_ullong(), bs[2].to_ullong(), bs[3].to_ullong());
  std::cout << buffer;
  if(strcmp(buffer, "81165010e5faafb63ffeaefb10000280") == 0) {
    // std::cout << "TRUE" << std::endl;
    // TRUE
  }
  std::cout << std::endl;
}

void readFromFile(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::string input;
  getline(inFile, input);
  hash(input);
  inFile.close();
}

void compare(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::string input;
  getline(inFile, input);
  hash(input);
  inFile.close();
}

int main(int argc, const char * argv[]) {
  // hash("kietuva");
  hash("lietuva");
  // if(std::string(argv[1]) == "--file") {
  //   std::cout << argv[2] << std::endl;
  //   readFromFile(std::string(argv[2]));
  // }
  // if(std::string(argv[1]) == "--compare") {
  //   std::cout << argv[2] << std::endl;
  //   compare(std::string(argv[2]));
  // }
  // for (int i = 0; i < argc; ++i) 
  //     std::cout << argv[i] << "\n"; 
  return 0;
}