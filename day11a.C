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

  // Convolution...
  int maxp = 0;
  int maxx, maxy;
  for(int i=0;i<298;++i) {
    for(int j=0;j<298;++j) {
      int p = 0;
      for(int di = 0; di<3; ++di) {
	for(int dj = 0; dj < 3; ++dj) {
	  p += grid[i+di][j+dj];
	}
      }
      if (p > maxp) {
	maxp = p;
	maxx = j+1;
	maxy = i+1;
      }
    }
  }
  std::cout << "Max-power coords are " << maxx << "," << maxy << std::endl;
}
  

