#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream f;

  f.open("day1.txt",std::ios::in);

  std::string line;
  while(std::getline(f,line)) {
    std::cout << line << std::endl;
  }
}
