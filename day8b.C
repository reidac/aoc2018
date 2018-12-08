#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Node {
public:
  Node(int nc, int nmeta) : ccount(nc), mcount(nmeta)  {
  }
  int ccount,mcount;
  std::vector<int> meta;
  std::vector<Node*> children;
};

// Stateful container for processing the string, passed through
// the construction process.
class Stringerator {
public:
  Stringerator(std::string str) : data(str),index(0) {
    datasize = str.size();
  }
  std::string data;
  int index;
  bool done() {
    return (index >= data.size());
  }
  int next() {
    int odx = index;
    while((odx<datasize)&&(data[odx]!=' ')) odx+=1;
    int res = std::stoi(data.substr(index,odx-index));
    index = odx+1;
    return res;
  }
private:
  int datasize;
};

Node *treeify(Stringerator &si) {
  
  int n_children = si.next();
  int n_meta = si.next();

  Node *res = new Node(n_children,n_meta);
  for(int cdx=0; cdx<n_children; ++cdx) {
    res->children.push_back(treeify(si));
  }
  for(int mdx=0; mdx<n_meta; ++mdx) {
    res->meta.push_back(si.next());
  }
  return res;
}


int traverse(Node *t) {
  if ((t->children).size()==0) {
    int res = 0;
    for( auto &mv : t->meta ) res += mv;
    return res;
  }
  else {
    int res = 0;
    for (auto &mv : t->meta ) {
      if (mv <= (t->children).size()) {
	res += traverse((t->children)[mv-1]);
      }
    }
    return res;
  }
}
  
int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  f.open("day8.txt",std::ios::in);
  Node *tree;

  while(std::getline(f,line)) {
    Stringerator si(line);
    tree = treeify(si);
  }

  std::cout << "Answer is " << traverse(tree) << std::endl;
}
