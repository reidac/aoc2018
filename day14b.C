#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#define INPUT "824501"
// #define INPUT "51589"

int main() {
  std::vector<char> recipes;
  recipes.reserve(21000000);
  recipes.push_back('3');
  recipes.push_back('7');
  int el0 = 0;
  int el1 = 1;

  int rsize = 2;
  
  std::string istring = INPUT;
  int isize = istring.size(); // # of digits in the input, as a string.
  
  bool done = false;
  int sofar = 0;
  while (!done) {

    int el0i = recipes[el0]-'0';
    int el1i = recipes[el1]-'0';
    
    int score = el0i+el1i;
    
    std::stringstream ss;
    ss << score;
    std::string scorestr = ss.str();
    for(auto &sdx : scorestr) {
      recipes.push_back(sdx);
      rsize += 1;
    }

    el0 = (el0+1+(recipes[el0]-'0'))%(rsize);
    el1 = (el1+1+(recipes[el1]-'0'))%(rsize);

    while ((sofar+isize)<rsize) {
      done = true;
      for(int idx=0;idx<isize;++idx) {
	if (istring[idx]!=recipes[sofar+idx]) {
	  done = false;
	  break;
	}
      }
      if (done) {
	break; // Breaks out of the "sofar<size" loop.
      }
      else {
	sofar += 1;
      }
    }
  }
  std::cout << "Found at " << sofar << std::endl;
}
