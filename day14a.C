#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INPUT 824501

int main() {
  std::vector<int> recipes = {3,7}; // Also input.
  int el0 = 0;
  int el1 = 1;

  bool done = false;
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

    if (recipes.size()>(INPUT+10)) done=true;
  }
  for(int rdx=0; rdx<10; ++rdx) {
    std::cout << recipes[rdx+INPUT];
  }
  std::cout << std::endl;
}
