#include <iostream>
#include <string.h>
#include <fstream>
#include <bitset>
#include <cmath>
#include <sstream>
#include <time.h>

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
      val = val / 1.2;
      bs[i] = bs[i].test(index) == 1 ? bs[i].reset(index) : bs[i].set(index);
      if (index % 3 == 0) {
        bs[i].flip();
      }
    }
  }

  return bitsetToHex(bs);
}

std::string readFromFile(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::string input;
  getline(inFile, input);
  inFile.close();
  return hash(input);
}

double measureTime(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  std::string input;
  double timeElapsed = 0;

  while (getline(inFile, input)) {
    clock_t tStart = clock();
    hash(input);
    timeElapsed += (double)(clock() - tStart)/CLOCKS_PER_SEC;
  }
  inFile.close();
  return timeElapsed;
}

void compare(std::string filename) {
  std::ifstream inFile;
  inFile.open(filename);
  double percentage;
  double mean = 0;
  double max = 0;
  double min = 100;
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

  std::ofstream outFile;
  outFile.open("outputs/comparison.txt");
  outFile << "Mean: " << mean << "%" << std::endl;
  outFile << "Max: " << max << "%" << std::endl;
  outFile << "Min: " << min << "%" << std::endl;

  if (k == 0) {
    outFile << "TEST PASSED!" << std::endl;
  } else {
    outFile << "TEST FAILED...  " << std::endl;
    outFile << "Failed pairs: " << k;
  }
  outFile.close();
  std::cout << "Output file: outputs/comparison.txt" << std::endl;
}

int main(int argc, const char * argv[]) {
  if(std::string(argv[1]) == "--files") {
    std::ofstream outFile;
    outFile.open("outputs/files.txt");
    for (int i = 2; i < argc; i++) {
      outFile << argv[i] << ": " << readFromFile(std::string(argv[i])) << std::endl;
    }
    outFile.close();
    std::cout << "Output file: outputs/files.txt" << std::endl;
  }
  
  else if(std::string(argv[1]) == "--compare") {
    compare(std::string(argv[2]));
  }
  
  else if(std::string(argv[1]) == "--string") {
    std::ofstream outFile;
    outFile.open("outputs/string.txt");
    outFile << hash(std::string(argv[2]));
    outFile.close();
    std::cout << "Output file: outputs/string.txt" << std::endl;
  }
  
  else if(std::string(argv[1]) == "--time") {
    std::ofstream outFile;
    outFile.open("outputs/measured.txt");
    outFile << measureTime(std::string(argv[2])) << " s.";
    outFile.close();
    std::cout << "Output file: outputs/measured.txt" << std::endl;
  }
  
  else {
    std::cout << "Something went wrong, look at README.md for more help." << std::endl;
  }

  return 0;
}