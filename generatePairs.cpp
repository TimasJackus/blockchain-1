#include <iostream>
#include <fstream>
#include <random>

const std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\"!@#$%^&*()_+'-.,/;:?`{}[]|";

std::string getRandomString() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, str.size() - 1);
  int index = dist6(rng);
  std::string randomString = "";
  for (int i = 0; i < 5; i++) {
    randomString += str[dist6(rng)];
  }
  return randomString;
}

std::string changeRandomString(std::string str1) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, str.size() - 1);
  std::uniform_int_distribution<std::mt19937::result_type> selectChar(0, 4);
  int index = dist6(rng);
  std::string str2 = str1;
  str2[selectChar(rng)] = str[dist6(rng)];
  if (str1.compare(str2) == 0) {
    return changeRandomString(str1);
  } else {
    return str2;
  }
}


int main() { 
  std::ofstream ofs("test-data/string-pairs-1.txt", std::ofstream::out);
  for (int i = 0; i < 1000000; i++) {
    ofs << getRandomString() << " " << getRandomString() << std::endl;
  }
  ofs.close();

  // std::ofstream ofs("test-data/string-pairs-2.txt", std::ofstream::out);
  // for (int i = 0; i < 100000; i++) {
  //   std::string str1 = getRandomString();
  //   std::string str2 = changeRandomString(str1);
  //   ofs << str1 << " " << str2 << std::endl;
  // }
  // ofs.close();
}