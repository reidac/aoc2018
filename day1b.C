#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::map<int,int> histogram;
  
  f.open("day1.txt",std::ios::in);

  std::string line;
  int phase = 0;
  bool done = false;
  histogram[phase]=1;
  while(!done) {
    while(std::getline(f,line)) {
      phase += std::stoi(line);
      int ct = histogram.count(phase);
      if (ct!=0) {
	std::cout << "Duplicate found." << std::endl;
	done = true;
	break;
      }
      else {
	histogram[phase]=1;
      }
    }
    f.clear();
    f.seekg(0);
  }
  std::cout << "First phase to be encountered twice is " << phase << std::endl;
}
