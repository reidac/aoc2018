#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

enum CartState { left, straight, right };
enum CartDirection { du,dr,dd,dl };

static int cartid = 0;

class Cart {
public:
  CartState state;
  CartDirection dir;
  Cart(int id, int row,int col,CartDirection d) : id(id),row(row),col(col),
						  dir(d),state(left),
						  crashed(false) {};
  int id,row,col;
  bool crashed;
  bool operator<(const Cart &other) const {
    return (row < other.row) || ((row==other.row) && (col < other.col));
  }
  void turn() {
    switch (state) {
    case left:
      state = straight;
      break;
    case straight:
      state = right;
      break;
    case right:
      state = left;
      break;
    }
  }
};


class Cell {
public:
  Cell() : u(false),r(false),d(false),l(false) {};
  Cell(bool u, bool r, bool d, bool l) : u(u),r(r),d(d),l(l) {};
  bool u,r,d,l;
  bool corner() {
    return (u && r && !d && !l) || (u && !r && !d && l) ||
      (!u && r && d && !l) || (!u && !r && d && l);
  }
  bool junction() {
    return (u && r && d && l);
  }
  bool thru () {
    return (u && !r && d && !l) || (!u && r && !d && l);
  }
};


// You can't crash into an already-crashed cart.
bool collision(int r, int c, std::vector<Cart> &cts) {
  for(auto &cdx : cts) {
    if ((cdx.row == r) && (cdx.col == c) && !cdx.crashed ) {
      cdx.crashed = true;
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  std::ifstream f;
  std::string line;

  Cell board[151][151];

  std::vector<Cart> carts;
  
  f.open("day13.txt",std::ios::in);

  int rdx = 0;
  while(std::getline(f,line)) {
    for(int cdx=0; cdx<line.size(); ++cdx) {
      switch (line[cdx]) {
      case '|' :
	board[rdx][cdx] = Cell(true,false,true,false);
	break;
      case '-' :
	board[rdx][cdx] = Cell(false,true,false,true);
	break;
      case '\\' :
	if (rdx==0) {
	  board[rdx][cdx] = Cell(false,false,true,true);
	}
	else if (board[rdx-1][cdx].d) {
	  board[rdx][cdx] = Cell(true,true,false,false);
	}
	else {
	  board[rdx][cdx] = Cell(false,false,true,true);
	}
	break;
      case '/' :
	if (rdx==0) {
	  board[rdx][cdx] = Cell(false,true,true,false);
	}
	else if (board[rdx-1][cdx].d) {
	  board[rdx][cdx] = Cell(true,false,false,true);
	}
	else {
	  board[rdx][cdx] = Cell(false,true,true,false);
	}
	break;
      case '+':
	board[rdx][cdx] = Cell(true,true,true,true);
	break;
      case 'v':
	board[rdx][cdx] = Cell(true,false,true,false);
	carts.push_back(Cart(cartid,rdx,cdx,dd));
	cartid += 1;
	break;
      case '^' :
	board[rdx][cdx] = Cell(true,false,true,false);
	carts.push_back(Cart(cartid,rdx,cdx,du));
	cartid += 1;
	break;
      case '>':
	board[rdx][cdx] = Cell(false,true,false,true);
	carts.push_back(Cart(cartid,rdx,cdx,dr));
	cartid += 1;
	break;
      case '<':
	board[rdx][cdx] = Cell(false,true,false,true);
	carts.push_back(Cart(cartid,rdx,cdx,dl));
	cartid += 1;
	break;
      }
    }
    rdx += 1;
  }
  // Board is built and cart list is populated.
  std::cout << carts.size() << std::endl;
  // Iterate.
  bool done = false;
  int collision_r,collision_c;
  while (!done) {
    std::sort(carts.begin(),carts.end());
    for (auto &cdx : carts ) {
      if (cdx.crashed) {
	continue;
      }
      switch (cdx.dir) {
      case du:
	assert(board[cdx.row][cdx.col].u);
	break;
      case dr:
	assert(board[cdx.row][cdx.col].r);
	break;
      case dd:
	assert(board[cdx.row][cdx.col].d);
	break;
      case dl:
	assert(board[cdx.row][cdx.col].l);
	break;
      }

      int newrow = cdx.row + (cdx.dir==dd ? 1 : 0) - (cdx.dir==du ? 1 : 0);
      int newcol = cdx.col + (cdx.dir==dr ? 1 : 0) - (cdx.dir==dl ? 1 : 0);
      if (collision(newrow,newcol,carts)) {
	cdx.crashed = true;
	continue;
      }
      cdx.row = newrow;
      cdx.col = newcol;
      Cell newcell = board[newrow][newcol];
      // Do we need to turn the cart?
      if (newcell.thru()) {
      } // No turns, go to the next cart.
      else if (newcell.junction()) {
	switch (cdx.state) {
	case left:
	  { switch (cdx.dir) {
	    case du: cdx.dir = dl;
	      break;
	    case dr: cdx.dir = du;
	      break;
	    case dd: cdx.dir = dr;
	      break;
	    case dl: cdx.dir = dd;
	      break;
	    }
	    break;
	  } // End of case left
	case straight:
	  break;
	case right:
	  { switch (cdx.dir) {
	    case du: cdx.dir = dr;
	      break;
	    case dr: cdx.dir = dd;
	      break;
	    case dd: cdx.dir = dl;
	      break;
	    case dl: cdx.dir = du;
	      break;
	    }
	    break;
	  } // End of case right.
	} // End of switch on cdx.state.
	cdx.turn();
      } // End if newcell is a junction.
      else if (newcell.corner()) {
	switch(cdx.dir) {
	case du:
	  if (newcell.r) {
	    cdx.dir = dr;
	  }
	  else if (newcell.l) {
	    cdx.dir = dl;
	  }
	  else {
	    std::cout << "Up-facing cart can't turn!" << std::endl;
	  }
	  break;
	case dr:
	  if (newcell.d) {
	    cdx.dir = dd;
	  }
	  else if (newcell.u) {
	    cdx.dir = du;
	  }
	  else {
	    std::cout << "Right-facing cart can't turn!" << std::endl;
	  }
	  break;
	case dd:
	  if (newcell.r) {
	    cdx.dir = dr;
	  }
	  else if (newcell.l) {
	    cdx.dir = dl;
	  }
	  else {
	    std::cout << "Down-facing cart can't turn!" << std::endl;
	  }
	  break;
	case dl:
	  if (newcell.u) {
	    cdx.dir = du;
	  }
	  else if (newcell.d) {
	    cdx.dir = dd;
	  }
	  else {
	    std::cout << "Left-facing cart can't turn!" << std::endl;
	  }
	  break;
	} // End of switch on dirs.
      } // End of literal corner case.
      else {
	std::cout << "Unclassified cell. Disaster!" << std::endl;
	std::cout << "Row, col are " << newrow << "," << newcol << std::endl;
      }
    } // End of loop over carts.
    int cartcount = 0;
    for(auto &cdx : carts) {
      if (!cdx.crashed) {
	cartcount += 1;
      }
    }
    if (cartcount==1) done = true;
  } // End of while-not-done loop.

  for(auto &cdx : carts) {
    if (!cdx.crashed) {
      std::cout << "Uncrashed cart at (x,y) = "
		<< cdx.col << "," << cdx.row << std::endl;
    }
  }
}
