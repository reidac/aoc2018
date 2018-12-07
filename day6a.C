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
  std::map<std::pair<int,int>,int> grd;
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

  // Build the map.  Iterate over the extended domain, find each point's
  // nearest neighbor (by index in the vector).

  for(int rdx = fminr; rdx<fmaxr; ++rdx) {
    for(int cdx = fminc; cdx<fmaxc; ++cdx) {
      int neard = (fmaxr-fminr)+(fmaxc-fminc); // Large initial value.
      int nearx = 0; // Index of the value.
      for(int vdx = 0; vdx < pts.size(); ++vdx) {
	int dst = abs(pts[vdx].first-rdx)+abs(pts[vdx].second-cdx);
	if (dst<neard) {
	  neard = dst;
	  nearx = vdx;
	}
	else if (dst == neard) {
	  nearx = -1; // Two or more "nearest", doesn't count.
	}
      }
      grd[std::pair<int,int>(rdx,cdx)]=nearx;
    }
  }
  // Count things.

  std::map<int,int> counts;

  for( auto &mdx : grd ) {
    int idx = mdx.second;
    std::map<int,int>::iterator countdx = counts.find(idx);
    if (countdx != counts.end()) { 
      counts[idx]+=1;
    }
    else {
      counts[idx]=1;
    }
  }
  
  // At this point "counts" has a map from ID to # of occurrences.
  
  std::set<int> prphs;
  for(int rdx = fminr; rdx < fmaxr; ++rdx) {
    prphs.insert(grd[std::pair<int,int>(rdx,fminc)]);
    prphs.insert(grd[std::pair<int,int>(rdx,fmaxc-1)]);
  }
  for(int cdx = fminc; cdx < fmaxc; ++cdx) {
    prphs.insert(grd[std::pair<int,int>(fminr,cdx)]);
    prphs.insert(grd[std::pair<int,int>(fmaxr-1,cdx)]);
  }

  // Remove the peripheral indices from the map.

  for( auto &pdx : prphs) {
    counts.erase(pdx);
  }

  // Now, the largest non-infinite area is the largest value (not index)
  // in the truncated "counts" map.

  int res = 0;
  for( auto &cdx : counts) {
    if (cdx.second > res) res = cdx.second;
  }

  std::cout << "The answer is " << res << std::endl;
  
}
