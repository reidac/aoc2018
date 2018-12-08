#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>

class Task {
public:
  char label;
  Task(char id) : label(id) {}
  std::set<char> prereqs, followers;
  bool ready() {
    return prereqs.size()==0;
  }
};

// Confusion -- this is a map to Task* because otherwise the compiler
// really wanted a default constructor for Task, but that makes
// no sense.  Why does it want one?

typedef std::map<char,Task*> taskmap;

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  f.open("day7.txt",std::ios::in);

  taskmap tmap;
  
  while(std::getline(f,line)) {
    char before = line[5];
    char after = line[36];

    taskmap::iterator ti = tmap.find(before);
    if (ti!=tmap.end()) {
      (*ti).second->followers.insert(after);
    }
    else {
      Task *t = new Task(before);
      t->followers.insert(after);
      tmap[before]=t;
    }

    ti = tmap.find(after);
    if (ti!=tmap.end()) {
      (*ti).second->prereqs.insert(before);
    }
    else {
      Task *t = new Task(after);
      t->prereqs.insert(before);
      tmap[after]=t;
    }
      
  }

  std::set<char> workset;

  for(auto &ti : tmap) {
    if ( ti.second->ready()) workset.insert(ti.first);
  }

  std::string res;
  
  while( workset.size() != 0 ) {
    char op = *(workset.begin()); // C++ sets are ordered.
    workset.erase(op);
    res += op;

    Task *tcurrent = tmap[op];
    for(auto &ci : tcurrent->followers) {
      (tmap[ci]->prereqs).erase(op);
      if ((tmap[ci]->prereqs).size()==0) workset.insert(ci);
    }
  }
  std::cout << "Answer: " << res << std::endl;
}
