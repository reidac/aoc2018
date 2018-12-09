#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
  
int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  f.open("day6.txt",std::ios::in);

  std::vector<std::pair<int,int>> pts;
  int maxr,maxc,minr,minc;

  bool frst = true;
  while(std::getline(f,line)) {
    int r = std::stoi(line.substr(0,line.find(',')));
    int c = std::stoi(line.substr(line.find(',')+1,std::string::npos));
    pts.push_back(std::pair<int,int>(r,c));
    if (frst) {
      maxr = r; minr = r; maxc = c; minc = c; frst = false;
    }
    else {
      maxr = (r > maxr ? r : maxr); minr = (r < minr ? r : minr);
      maxc = (c > maxc ? c : maxc); minc = (c < minc ? c : minc);
    }
  }

  // Generous padding, so that only "infinite" domains are on the boundary.
  int fminr = minr - (maxr-minr)*0.2;
  int fmaxr = maxr + (maxr-minr)*0.2;
  int fminc = minc - (maxc-minc)*0.2;
  int fmaxc = maxc + (maxc-minc)*0.2;

  
  // Build the map.  Iterate over the extended domain, and add up
  // all the distances to all the points.

  int grd[fmaxr-fminr][fmaxc-fminc];
  
  for(int rdx = 0; rdx<(fmaxr-fminr); ++rdx) {
    for(int cdx = 0; cdx<(fmaxc-fminc); ++cdx) {
      grd[rdx][cdx] = 0;
      for(int vdx = 0; vdx < pts.size(); ++vdx) {
	int dst = abs(pts[vdx].first-(rdx+fminr))+abs(pts[vdx].second-(cdx+fminc));
	grd[rdx][cdx]+=dst;
      }
    }
  }

  // Count up how many of these distances are strictly less than 10000.
  // (Magic # from problem statement.)

  int res = 0;
  for(int rdx = 0; rdx<(fmaxr-fminr); ++rdx) {
    for(int cdx = 0; cdx<(fmaxc-fminc); ++cdx) {
      if (grd[rdx][cdx] < 10000) res += 1;
    }
  }

  std::cout << "The answer is " << res << std::endl;
  
}
