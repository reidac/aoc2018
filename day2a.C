#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

typedef std::map<char,int> cmap;

cmap histify(std::string l) {
  cmap res;
  for( char c : l) {
    cmap::iterator ix = res.find(c);
    if (ix != res.end()) {
      res[c]+=1;
    }
    else {
      res[c]=1;
    }
  }
  return res;
}

bool hastwo(cmap htg) {
  bool res = false;
  for(auto &cp : htg) 
    if (cp.second==2)
      res = true;
  return res;
}

bool hasthree(cmap htg) {
  bool res = false;
  for(auto &cp : htg)
    if (cp.second==3)
      res = true;
  return res;
}

int main(int argc, char *argv[]) {
  std::ifstream f;

  cmap htg;
  
  f.open("day2.txt",std::ios::in);

  int twocount = 0;
  int threecount = 0;
  std::string line;
  while(std::getline(f,line)) {
    htg = histify(line);
    if (hastwo(htg)) twocount += 1;
    if (hasthree(htg)) threecount += 1;
  }
  std::cout << "Product is " << twocount*threecount << std::endl;
}
