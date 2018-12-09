#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// A Board is a circular linked list of marbles, with intelligence
// about how the game works.  Next-pointers point clockwise.
class Board {
public:
  class Marble {
  public:
    int id;
    Marble *next;
    Marble *prev;
    Marble(int id) : id(id), next(NULL), prev(NULL) {}
  };
  int count;
  Marble *current;
  Board() : count(0), current(NULL) {}
  // Insert the next marble according to the rules.  Return the score
  // for this move.
  int move() {
    if (count==0) {
      current = new Marble(0);
      current->next = current;
      current->prev = current;
      count += 1;
      return 0;
    }
    else if (count==1) {
      current->next = new Marble(1);
      current->next->next = current;
      current = current->next;
      current->prev = current->next; // There are only two...
      current->prev->prev = current; 
      count += 1;
      return 0;
    }
    else if ((count%23)==0) { // Nontrivial scoring.
      int res = count;
      count += 1;
      // Find the marble eight positions ccw from the current one.
      // The seven-cc one will be removed, but we need its predecessor,
      // which is the eighth one.  Linear search.  TODO: better.
      Marble *egtcc = current->prev->prev->prev->prev->prev->prev->prev->prev;
      Marble *sevencc = egtcc->next;
      Marble *sixcc = sevencc->next;
      res += sevencc->id;
      egtcc->next = sixcc;
      sixcc->prev = egtcc;
      current = sixcc;
      free(sevencc);
      return res;
    }
    else { // General case.  Insert between p1 and p2, guaranteed distinct.
      Marble *p1 = current->next;
      Marble *p2 = current->next->next;
      Marble *add = new Marble(count);
      add->next = p2;
      p2->prev = add;
      p1->next = add;
      add->prev = p1;
      current = add;
      count += 1;
      return 0;
    }
  }
  std::string repr() const {
    if (current==NULL) {
      return "Empty board.";
    }
    else {
      std::stringstream ss;
      Marble *wrk = current;
      do {
	ss << wrk->id << "->";
	wrk = wrk->next;
      } while(wrk!=current);
      return ss.str();
    }
  }
  friend std::ostream &operator<<(std::ostream&, const Board &);
};


std::ostream &operator<<(std::ostream &o, const Board &b) {
  return o << b.repr();
}
  
int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;
  
  f.open("day9.txt",std::ios::in);
  int pls, mbls;
  while(std::getline(f,line)) {
    pls = std::stoi(line.substr(0,line.find("play")-1));
    mbls = std::stoi(line.substr(line.find("worth")+5,std::string::npos))*100;
    mbls += 1;  // Input is marble value, but count starts from zero.
  }

  // Testing.  Ignore the input, do this:
  // pls = 13;
  // mbls = 7999+1;
  
  std::cout << "Players: " << pls << ", marbles: " << mbls-1 << std::endl;

  std::vector<long long> scores(pls, 0);
  Board b = Board();
  long long maxscore = 0;
  for(int mdx=0; mdx<mbls; ++mdx) {
    int pid = mdx%pls;
    int delta = b.move();
    long long newscore = scores[pid]+delta;
    if (newscore>maxscore) maxscore = newscore;
    scores[pid]=newscore;
  }
  std::cout << "High score: " << maxscore << std::endl;
}
