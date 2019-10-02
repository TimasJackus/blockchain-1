#include <iostream>
#include <fstream>
#include <random>

std::string getRandomString() {
  std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\"!@#$%^&*()_+'-";
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

int main() { 
  std::ofstream ofs("test-data/string-pairs-1.txt", std::ofstream::out);
  for (int i = 0; i < 100000; i++) {
    ofs << getRandomString() << " " << getRandomString() << std::endl;
  }
  ofs.close();
  //  std::cout << dist6(rng) << " " << dist6(rng);
}