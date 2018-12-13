#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>

typedef std::map<std::string,char> ruleset;

void drawboard(int bl, int bh, std::set<int> brd) {
  std::string outcheck;
  for(int bdx = bl; bdx<=bh; ++bdx) {
    std::set<int>::iterator bdi = brd.find(bdx);
    if (bdi!=brd.end()) {
      outcheck += '#';
    }
    else {
      outcheck += '.';
    }
  }
  std::cout << outcheck << std::endl;
}

int main(int argc, char *argv[]) {
  std::ifstream f;

  f.open("day12.txt",std::ios::in);

  std::set<int> board; // Set of indices of 'live' cells.
  int blb,bhb; // Low and high bounds.

  ruleset rules;

  std::string line;
  std::getline(f,line);
  std::string rline = line.substr(15,std::string::npos);
  for(int ldx = 0; ldx < rline.size(); ++ldx) {
    if (rline[ldx]=='#') {
      board.insert(ldx);
    }
  }

  blb = -20;
  bhb = line.size()+20;

  std::getline(f,line); // Eat the blank line.

  while(std::getline(f,line)) {
    rules[line.substr(0,5)]=line[9];
  }

  // Begin the iterations.
  for(int ict = 0; ict < 20; ++ict) {
    std::set<int> newboard;
    for(int sdx = blb; sdx < bhb; ++sdx) {
      std::string key;
      for(int kdx = 0;kdx<5;++kdx) {
	std::set<int>::iterator bdi=board.find(sdx+kdx);
	if (bdi!=board.end()) {
	  key += '#';
	}
	else {
	  key += '.';
	}
      }
      if (rules[key]=='#') {
	newboard.insert(sdx+2); // sdx is left edge of five-cell window.
      }
    }
    // New board is complete.
    board = newboard;
    // Iteration is complete.
  }
  int ptotal = 0;
  for(auto &bdx : board) ptotal += bdx;
  
  std::cout << "Number of plants: " << board.size() << std::endl;
  std::cout << "Pot total " << ptotal << std::endl;
}
