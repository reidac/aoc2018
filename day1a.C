#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream f;

  f.open("day1.txt",std::ios::in);

  std::string line;
  int phase = 0;
  while(std::getline(f,line)) {
    phase += std::stoi(line);
  }
  std::cout << "Phase is " << phase << std::endl;
}
