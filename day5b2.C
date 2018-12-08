#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static int dlta = abs(int('A')-int('a'));

class LLString {
public:
  class LChar {
  public:
    char c;
    LChar *next;
    bool mark;
    LChar(char c) : c(c), next(NULL), mark(false) {} 
  };
  LChar *base;
  int size;
  LLString(std::string s) : base(NULL), size(0) {
    LChar *cur,*prev;
    size = s.size();
    for ( auto &sv : s ) {
      cur = new LChar(sv);
      if (base==NULL) {
	base = cur;
      }
      else {
	prev->next = cur;
      }
      prev = cur;
    }
  }
  ~LLString() {
    LChar *cur = base;
    LChar *swp;
    while (cur->next != NULL) {
      swp = cur->next;
      free(cur);
      cur = swp;
    }
  }
  void prune(char pcl) {
    char pcu = int(pcl)-'a'+'A';
    LChar *cur = base;
    do {
      if ( ((cur->c)==pcl)  || ((cur->c)==pcu) ) cur->mark = true;
      cur = cur->next;
    } while ((cur->next)!=NULL);
    prune_marks();
  }
  
  void react() {
    int ct;
    while ( ct=reactstep()!=0 ) {  }
  }
private:
  void prune_marks() {
    // First, remove marked front cells until there aren't any more.
    while (base->mark) {
      LChar *tmp = base;
      base = base->next;
      free(tmp);
      size -= 1;
    }

    LChar *prev = base;
    LChar *cur = base->next;
    bool done = false;
    do {
      if (cur->mark) {
	LChar *tmp = cur;
	if ((cur->next)==NULL) {
	  prev->next = NULL;
	  done = true;
	}
	else {
	  prev->next = cur->next;
	  cur = cur->next;
	}
	size -= 1;
	free(tmp);
      }
      else { // Not marked, don't prune.
	if ((cur->next)==NULL) {
	  done = true;
	}
	else {
	  prev = cur;
	  cur = cur->next;
	}
      }
    } while (!done);
  }
  
  // Two-step mark-and-remove scheme. Return # of removals.
  int reactstep() { 
    LChar *p0 = base;
    LChar *p1 = p0->next;
    bool done = false;
    int res = 0;
    do {
      if ( abs(int(p0->c)-int(p1->c))==dlta ) {
	p0->mark = true;
	p1->mark = true;
	res += 2;
	if (((p1->next)==NULL) || ((p1->next->next)==NULL) ) {
	  done = true;
	}
	else {
	  p0 = p1->next;
	  p1 = p0->next;
	}
      }
      else { // Non-marking case.
	if ((p1->next)==NULL) {
	  done = true;
	}
	else {
	  p0 = p1;
	  p1 = p1->next;
	}
      }
    } while (!done);
    // Finished with the marking pass.  Now do removals.
    prune_marks();
    return res;
  } // End of "reactstep" function.
  

};

  
int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  f.open("day5.txt",std::ios::in);

  char minlet;
  int minlen = 10866; 
  while(std::getline(f,line)) {
    for(char pc = 'a'; pc<='z'; ++pc) {
      LLString *op = new LLString(line);
      op->prune(pc);
      op->react();
      std::cout << "Char " << pc << ", size " << op->size << std::endl;
      if ((op->size)<minlen) {
	minlen = op->size;
	minlet = pc;
      }
    }
  }
  std::cout << "Minimum of " << minlen << " realized at letter "
	    << minlet << std::endl; 
}
