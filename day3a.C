#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

typedef std::map<std::pair<int,int>,int> pairmap;

class Claim {
public:
  Claim(std::string &s) {
    id = std::stoi(s.substr(s.find('#')+1,s.find('@')-1));
    int atlcn = s.find('@'), colcn = s.find(':');
    std::string ustr = s.substr(atlcn+1,colcn-atlcn-1);
    lc = std::stoi(ustr.substr(0,ustr.find(',')));
    tc = std::stoi(ustr.substr(ustr.find(',')+1,ustr.length()));

    ustr = s.substr(s.find(':')+1,s.length());
    w =std::stoi(ustr.substr(0,ustr.find('x')));
    h = std::stoi(ustr.substr(ustr.find('x')+1,ustr.length()));
  }
  friend std::ostream& operator<<(std::ostream &os, const Claim &c);
  //
  // Mark (or increment) the map squares covered by this claim.
  pairmap& mark(pairmap &m) {
    for(int c=lc; c<(lc+w); ++c)
      for(int r=tc; r<(tc+h); ++r) {
	std::pair<int,int> rc = std::make_pair(r,c);
	pairmap::iterator ip = m.find(rc);
	if (ip != m.end()) {
	  m[rc]+=1;
	}
	else {
	  m[rc]=1;
	}
      }
    return m;
  }
private:
  int id, lc, tc, w, h; // ID, left coord, top coord, width, height

};

std::ostream& operator<<(std::ostream &os, const Claim &c) {
  return os << "#" << c.id << " @ " << c.lc << "," << c.tc << ": " <<
    c.w << "x" << c.h;
}

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;
  
  f.open("day3.txt",std::ios::in);

  pairmap pm;
  
  while(std::getline(f,line)) {
    Claim c = Claim(line);
    pm = c.mark(pm);
  }
  int count = 0;
  for(auto &pmi : pm ) {
    if (pmi.second > 1) count += 1;
  }
  std::cout << "Count of overlap cells: " << count << std::endl;
}
