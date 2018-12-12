#include <iostream>

#define GRIDSERIAL 1955 // Input.

int main(int argc, char *argv[]) {
  int grid[300][300];
  
  for(int i=0;i<300;++i) {
    for(int j=0;j<300;++j) {
      int x = j+1;
      int y = i+1; // Clearer, maybe the compiler will fix it?
      grid[i][j] = (((((x+10)*y+GRIDSERIAL)*(x+10))/100)%10)-5;
    }
  }

  // Convolutions...
  int maxp = 0;
  int maxx, maxy,maxs;
  for(int i=0; i<299; ++i) {
    for(int j=0; j<299; ++j) {
      // For each coordinate, do all the box sizes you can in
      // sequence, and accumulate p.  This is maybe faster than
      // multiple convolutions?
      int shell = 0;
      int p = 0;
      do {
	for(int rdx = 0; rdx<shell; ++rdx) {
	  p += grid[i+shell][j+rdx] + grid[i+rdx][j+shell];
	}
	p += grid[i+shell][j+shell];
	if (p>maxp) {
	  maxp = p;
	  maxx = j+1;
	  maxy = i+1;
	  maxs = shell+1;
	}
	shell += 1;
      } while( ((i+shell)<299) && ((j+shell)<299) );
    }
  }
  std::cout << "Max-power coords are " << maxx << "," << maxy << "," << maxs << std::endl;

}
  

