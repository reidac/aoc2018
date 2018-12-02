#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int ndiffs(std::string s1, std::string s2) {
  int res = 0;
  auto i1 = s1.begin();
  auto i2 = s2.begin();
  for(; i1 != s1.end(); ++i1, ++i2) {
    if ((*i1)!=(*i2)) res += 1;
  }
  return res;
}

std::string commons(std::string s1, std::string s2) {
  std::string res = "";
  auto i1 = s1.begin();
  auto i2 = s2.begin();
  for(; i1!=s1.end(); ++i1,++i2) {
    if ((*i1)==(*i2)) res.push_back(*i1);
  }
  return res;
}

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;
  
  f.open("day2.txt",std::ios::in);

  std::vector<std::string> s;

  // A cleverer algorithm would not store all the data.
  while(std::getline(f,line)) {
    s.push_back(line);
  }
  for(auto vi = s.begin(); vi!=s.end(); ++vi) {
    for(auto vj=vi; vj!=s.end(); ++vj) {
      // Find the pair of strings which differ in exactly one place,
      // and print out the common portion of these two strings.
      int nd = ndiffs(*vi,*vj);
      if (nd==1) {
	std::cout << commons(*vi,*vj) << std::endl;
      }
    }
  }
}
