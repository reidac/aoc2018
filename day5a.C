#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  f.open("day5.txt",std::ios::in);

  int dlta = abs(int('A')-int('a'));
  while(std::getline(f,line)) {
    int sz, newsz;
    do {
      sz = line.size();
      newsz = line.size();
      for(int idx=0;idx<(sz-1);++idx) {
	if (abs(int(line[idx])-int(line[idx+1]))==dlta ) {
	  line = line.substr(0,idx)+line.substr(idx+2,sz);
	  newsz = line.size();
	  break;
	}
      }
    } while (newsz != sz);
    std::cout << "The answer: " << line.size() << std::endl;
  }
}
