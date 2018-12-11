#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Coord {
  int row, col;
};

struct Bbox {
  int maxr,minr,maxc,minc;
};
  
class Star {
public:
  Star(int r0, int c0, int vr, int vc) : r0(r0),c0(c0),vr(vr),vc(vc) {}
  Coord att(int t) {
    Coord res;
    res.row = r0+t*vr;
    res.col = c0+t*vc;
    return res;
  }
private:
  int r0,c0,vr,vc;
};



Bbox bounds(int t, std::vector<Star> s) {
  Bbox res;
  Coord satt = s[0].att(t);
  res.maxr = res.minr = satt.row;
  res.maxc = res.minc = satt.col;
  for(auto &star : s) {
    satt = star.att(t);
    res.maxr = (satt.row > res.maxr ? satt.row : res.maxr );
    res.minr = (satt.row < res.minr ? satt.row : res.minr );
    res.maxc = (satt.col > res.maxc ? satt.col : res.maxc );
    res.minc = (satt.col < res.minc ? satt.col : res.minc );
  }
  return res;
}

long long area(int t, std::vector<Star> s) {
  Bbox b = bounds(t,s);
  return ((long long)(b.maxr-b.minr))*((long long)(b.maxc-b.minc));
}

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;
  
  f.open("day10.txt",std::ios::in);

  std::vector<Star> stars;
  
  while(std::getline(f,line)) {
    int pstart = line.find('<');
    int pmid = line.find(',');
    int pend = line.find('>');
    int rowval = std::stoi(line.substr(pstart+1,pmid-pstart-1));
    int colval = std::stoi(line.substr(pmid+1,pend-pmid-1));
    std::string vstr = line.substr(pend+1,std::string::npos);
    pstart = vstr.find('<');
    pmid = vstr.find(',');
    pend = vstr.find('>');
    int rowvel = std::stoi(vstr.substr(pstart+1,pmid-pstart-1));
    int colvel = std::stoi(vstr.substr(pmid+1,pend-pmid-1));
    
    stars.push_back(Star(colval,rowval,colvel,rowvel));
  }

  int ft = 0; // Fiduciary time.
  long long ar = area(ft,stars);
  
  bool done = false;
  // Linear search. NR was too unstable in round 1.
  while (!done) {
    int cft = ft+1;
    long long newar = area(cft,stars);
    if (newar > ar) {
      done = true;
    }
    else {
      ar = newar;
      ft = cft;
    }
  }
  std::cout << "Time: " << ft << std::endl;
  std::cout << "Area: " << area(ft,stars) << std::endl;

  Bbox b = bounds(ft,stars);
  std::cout << "Bounding box:" << std::endl;
  std::cout << b.minr << ":" << b.maxr << std::endl;
  std::cout << b.minc << ":" << b.maxc << std::endl;
  char sky[b.maxr-b.minr+1][b.maxc-b.minc+1];
  for( int rdx = 0; rdx < (b.maxr-b.minr)+1; ++rdx) {
    for (int cdx = 0; cdx < (b.maxc-b.minc)+1; ++cdx) {
      sky[rdx][cdx] = '.';
    }
  }
  for( auto &st : stars ) {
    Coord stc = st.att(ft);
    sky[stc.row-b.minr][stc.col-b.minc]='#';
  }
  for(int rdx = 0; rdx < (b.maxr-b.minr)+1; ++rdx) {
    for(int cdx = 0; cdx < (b.maxc-b.minc)+1; ++cdx) {
      std::cout << sky[rdx][cdx];
    }
    std::cout << std::endl;
  }
}
