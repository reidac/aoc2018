#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

enum Evtype {guard, sleep, wake};

class Event {
public:
  Event(std::string s) {
    day = std::stoi(s.substr(6,7))*100+std::stoi(s.substr(9,10));
    min = std::stoi(s.substr(12,13))*60+std::stoi(s.substr(15,16));
    if (s[19]=='G') {
      code = guard;
      gid = std::stoi(s.substr(s.find('#')+1,
			       s.find("be")-s.find('#')-1));
    }
    else if (s[19]=='f') {
      code = sleep;
      gid = 0;
    }
    else {
      code = wake;
      gid = 0;
    }
  }
  int day;
  int min;
  friend std::ostream &operator<<(std::ostream&, const Event &);
  Evtype code;
  int gid;
};


std::ostream &operator<<(std::ostream &o, const Event &e) {
  o << e.day << ":" << e.min << ":";
  if (e.code == guard) { o << " Guard " << e.gid; }
  if (e.code == sleep) { o << " Asleep"; }
  if (e.code == wake) { o << " Awake"; }
  return o;
}

bool eventLessThan(const Event &e1, const Event &e2) {
  return e1.day*10000+e1.min < e2.day*10000+e2.min;
}

typedef std::map<int, std::map<int,int>> gmap;

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  std::vector<Event> ev;
  
  f.open("day4.txt",std::ios::in);

  while(std::getline(f,line)) {
    Event e = Event(line);
    ev.push_back(e);
  }
  std::sort( ev.begin(), ev.end(), eventLessThan);

  // Guard-indexed map of minute-indexed frequency of sleep.
  gmap guards;

  // Loop through the events.  This should really be all polymorphic
  // and stuff, switching on event types, instead of being a bunch of
  // conditionals. 
  int current_gid = 0;
  int sstart = 0;
  for( auto &ei : ev ) {
    switch(ei.code) {
    case guard :
      current_gid = ei.gid;
      break;
    case sleep:
      sstart = ei.min;
      break;
    case wake:
      std::map<int,int> mmap;
      gmap::iterator gi = guards.find(current_gid);
      if (gi == guards.end()) {
	mmap = std::map<int,int>();
      }
      else {
	mmap = gi->second;
      }
      for(int i = sstart; i < ei.min; ++i ) {
	std::map<int,int>::iterator mi = mmap.find(i);
	if (mi == mmap.end()) {
	  mmap[i]=1;
	}
	else {
	  mmap[i]+=1;
	}
      }
      guards[current_gid] = mmap;
      break;
    }
  }
  // At this point, the "guards" gmap is populated with guard histograms.

  // Strategy 2: Which guard is the most frequently asleep at the same
  // minute?  Translation:  Which guard has the highest histogram
  // maximum, and at what index?

  int max_guard = 0;
  int max_minute = 0;
  int actual_max = 0;
  for(auto &gmi : guards) {
    int local_minute = 0;
    for(auto &mmi : gmi.second ) {
      if (mmi.second > actual_max) {
	actual_max = mmi.second;
	max_minute = mmi.first;
	max_guard = gmi.first;
      }
    }
  }
  std::cout << "Local sleep max is guard " << max_guard << " at minute " <<
    max_minute << std::endl;
  std::cout << "Answer: " << max_guard*max_minute << std::endl;
}
