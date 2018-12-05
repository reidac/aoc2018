#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static int dlta = abs(int('A')-int('a'));

// Takes the lower-case version to prune.
std::string prune(std::string sin, char pcl) {
  char pcu = int(pcl)-'a'+'A';
  std::string res;
  for( auto &i : sin ) {
    if (( i != pcl ) && (i != pcu )) res = res + i;
  }
  return res;
}

int react(std::string str) {
  std::string lcl = str;
  int sz,newsz;
  do {
    sz = lcl.size();
    newsz = lcl.size();
    for(int idx=0;idx<(sz-1);++idx) {
      if (abs(int(lcl[idx])-int(lcl[idx+1]))==dlta ) {
	lcl = lcl.substr(0,idx)+lcl.substr(idx+2,sz);
	newsz = lcl.size();
	break;
      }
    }
  } while (newsz != sz);
  return lcl.size();
}
  
int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  f.open("day5.txt",std::ios::in);

  std::string wrk;
  char mc;
  int min = 10866; // Answer from part A.  Cheating slightly....
  while(std::getline(f,line)) {
    for(char c = 'a'; c<='z'; ++c) {
      wrk = prune(line,c);
      int plen = react(wrk);
      if (plen < min) { min=plen; mc=c; }
    }
    std::cout << "Min length is " << min << " after pruning " << mc << std::endl;
  }
}
