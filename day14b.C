#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INPUT 824501

int main() {
  std::vector<int> recipes = {3,7}; // Also input.
  int el0 = 0;
  int el1 = 1;
  
  std::stringstream is;
  is << INPUT;
  std::string istring = is.str();
  int isize = istring.size(); // # of digits in the input, as a string.
  
  bool done = false;
  int sofar = 0;
  while (!done) {
    int score = recipes[el0]+recipes[el1];
    std::stringstream ss;
    ss << score;
    std::string scorestr = ss.str();
    for(int c=0; c<scorestr.size(); ++c) {
      recipes.push_back(std::stoi(scorestr.substr(c,1)));
    }
    el0 = (el0+1+recipes[el0])%(recipes.size());
    el1 = (el1+1+recipes[el1])%(recipes.size());

    while ((sofar+isize)<recipes.size()) {
      bool matched = true;
      for(int idx=0;idx<isize;++idx) {
	if (std::stoi(istring.substr(idx,1))!=recipes[sofar+idx]) matched=false;
      }
      if (matched) {
	done=true;
	break;
      }
      else {
	sofar += 1;
      }
    }
  }
  std::cout << "Found at " << sofar << std::endl;
}
