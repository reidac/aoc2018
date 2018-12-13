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
  bhb = line.size()+130;

  // std::cout << std::setw(4) << 0 << " ";
  // drawboard(blb,bhb,board);
  
  std::getline(f,line); // Eat the blank line.

  while(std::getline(f,line)) {
    rules[line.substr(0,5)]=line[9];
  }

  // Begin the iterations.
  for(int ict = 0; ict < 130; ++ict) {
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
    // std::cout << std::setw(4) << ict+1 << " ";
    // drawboard(blb,bhb,board);
    if (ict>100) {
      int ptotal = 0;
      int lowpot = 120;
      int highpot = 0;
      for (auto &bdx : board) {
	ptotal += bdx;
	lowpot = (bdx < lowpot ? bdx : lowpot);
	highpot = (bdx > highpot ? bdx : highpot);
      }
      int formula = (highpot+lowpot)*(highpot-lowpot+1)/2;
      std::cout << ict+1 << ": " << ptotal << ":" << lowpot << ","
		<< highpot << ": " << formula << ":" <<
	(highpot-lowpot+1) << std::endl;
    }
  }
  // From the foregoing, we deduce that, in the long term,
  // after i iterations, the low pot is i-87, the high pot
  // is i+98, all pots from low to high inclusive have plants,
  // and the sum is just the sum of the integers from low to high.
  // After fifty billion (50000000000) iterations:
  // lowpot = 49999999913
  // highpot = 50000000098
  // diff = 185, but high-low+1 is of course 186, divided by 2 is 93.
  // sum = 100000000011.
  // Formula is sum*93, or...
  long long lowpot = 49999999913;
  long long highpot = 50000000098;
  long long formula = (highpot+lowpot)*(highpot-lowpot+1)/2;
  std::cout << "By extrapolation, pot sum at 50000000000 is " <<
    formula << std::endl;
}
