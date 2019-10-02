#include <iostream>
#include <string.h>
#include <fstream>
#include <bitset>
#include <cmath>
#include <sstream>
const int HASH_LENGTH = 64;

long getCharsSum(std::string str) {
  long sum = 0;
  int d = 0;
  for(int i = 0; i < str.length(); i++) {
    sum += int(str[i]) * (i + 3);
    d = (i + 7) * int(str[i]);
  }
  sum = sum * 1337 * (64 % str.length() + int(str[0])) + d;
  return sum;
}

std::string bitsetToHex(std::bitset<HASH_LENGTH> bs[4]) {
  std::string hashStr = "";
  for(int i = 0; i < 4; i++) {
    std::string str;
    std::stringstream ss;
    ss << std::hex << bs[i].to_ulong();
    ss >> str;
    str = std::string((HASH_LENGTH / 4) - str.length(), '0').append(str);
    hashStr.append(str);
  }
  return hashStr;
}

std::string HexToBin(std::string hexdec) 
{ 
    long int i = 0; 
    std::string binStr = "";

    while (hexdec[i]) { 
        switch (hexdec[i]) { 
          case '0': 
              binStr += "0000"; 
              break; 
          case '1': 
              binStr += "0001"; 
              break; 
          case '2': 
              binStr += "0010"; 
              break; 
          case '3': 
              binStr += "0011"; 
              break; 
          case '4': 
              binStr += "0100"; 
              break; 
          case '5': 
              binStr += "0101"; 
              break; 
          case '6': 
              binStr += "0110"; 
              break; 
          case '7': 
              binStr += "0111"; 
              break; 
          case '8': 
              binStr += "1000"; 
              break; 
          case '9': 
              binStr += "1001"; 
              break;
          case 'a': 
              binStr += "1010"; 
              break;
          case 'b': 
              binStr += "1011"; 
              break;
          case 'c': 
              binStr += "1100"; 
              break;
          case 'd': 
              binStr += "1101"; 
              break;
          case 'e': 
              binStr += "1110"; 
              break;
          case 'f': 
              binStr += "1111"; 
              break; 
          default:
            break;
        } 
        i++; 
    }
    return binStr;
} 

double getPercentage(std::string str1, std::string str2) {
  double sameBits = 0;
  if (str1.length() == str2.length()) {
    for (int i = 0; i < str1.length(); i++) {
      if (str1[i] == str2[i]) {
        sameBits += 1;
      }
    }
    return sameBits / str1.length() * 100;
  } else {
    std::cout << "You can only compare same length strings.";
    return -1;
  }
}

std::string hash(std::string input) {
  std::bitset<HASH_LENGTH> bs[4];
  for(int i = 0; i < 4; i++) {
    bs[i] = std::bitset<HASH_LENGTH>{}.set();
  }

  long test = getCharsSum(input);
  for(int i = 0; i < 4; i++) {
    long val = test * (i + 3);
    while (val >= HASH_LENGTH) {
      int index = val % HASH_LENGTH;
      val = val / 2.5;
      bs[i] = bs[i].test(index) == 1 ? bs[i].reset(index) : bs[i].set(index);
      if (index % 3 == 0) {
        bs[i].flip();
      }
    }
  }

  return bitsetToHex(bs);
}

void readFromFile(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::string input;
  getline(inFile, input);
  std::cout << hash(input) << std::endl;
  inFile.close();
}

void compare(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  double percentage;
  double mean = 0;
  double max = 0;
  double min = 100;
  // one line
  std::string input;
  int i = 0, k = 0;
  while (getline(inFile, input)) {
    std::istringstream iss(input);
    std::string sub1;
    std::string sub2;
    iss >> sub1;
    iss >> sub2;
    
    if (hash(sub1).compare(hash(sub2)) == 0) {
      k++;
    }
    percentage = getPercentage(hash(sub1), hash(sub2));

    mean += percentage;
    if (percentage < min) {
      min = percentage;
    }
    if (percentage > max) {
      max = percentage;
    }
    i++;
  }

  mean = (double)mean / i;

  std::cout << "mean: " << mean << std::endl;
  std::cout << "max: " << max << std::endl;
  std::cout << "min: " << min << std::endl;

  if (k == 0) {
    std::cout << "TEST PASSED!" << std::endl;
  } else {
    std::cout << "TEST FAILED...  " << std::endl;
    std::cout << "Failed pairs: " << k << std::endl;
  }
  inFile.close();
}

int main(int argc, const char * argv[]) {
  std::cout << hash("kietuva") << std::endl;
  if(std::string(argv[1]) == "--file") {
    std::cout << argv[2] << std::endl;
    readFromFile(std::string(argv[2]));
  }
  // if(std::string(argv[1]) == "--compare") {
  //   std::cout << argv[2] << std::endl;
  //   compare(std::string(argv[2]));
  // }
  return 0;
}