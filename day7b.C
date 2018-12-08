#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>

// Workers have a label (can be blank if the worker is idle), and an
// amount of time remaining until their current task is completed.
struct Worker {
  char label = '.';
  int cdown = 0;
};

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

  int elapsed = 0;
  bool done = false;
  // Each task takes 60+x seconds to complete, x is position in the
  // alphabet, A=1.  We have five workers (problem input).

  std::vector<Worker> elves;

  for(int i=0; i<5; ++i) elves.push_back(Worker());

  while( !done ) {
    // Each iteration of this loop is a tick of the clock.

    // Assign tasks to workers, where possible.
    for (auto &ei : elves) {
      if ((ei.cdown == 0) && (workset.size()!=0)) {
	char op = *(workset.begin()); // Alphabetically first.
	ei.label = op;
	ei.cdown = 61+(op-'A');
	workset.erase(op);
      }
    }

    // Move the clock.
    elapsed += 1;

    // Decrement all the workers who are not idle.  If any complete,
    // make appropriate adjustments to the task graph.
    for (auto &ei : elves) {
      if (ei.cdown > 1) {
	ei.cdown -= 1;
      }
      else if (ei.cdown==1) {
	// Task ei.label is complete.
	Task *tcompleted = tmap[ei.label];
	for(auto &ci : tcompleted->followers) {
	  (tmap[ci]->prereqs).erase(ei.label);
	  if ((tmap[ci]->prereqs).size()==0) workset.insert(ci);
	}
	ei.cdown = 0;
	ei.label = '.';
      }
    } // All elves are incremented.

    int ctotal = 0;
    for (auto &ei : elves) ctotal += ei.cdown;
    if ((workset.size()==0) && ( ctotal == 0)) done = true;

  } // End of the clock loop.

  
  std::cout << "Elapsed time: " << elapsed << std::endl;
}
