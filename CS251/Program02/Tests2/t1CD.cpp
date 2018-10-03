
#include "GridWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "_test.h"
#include "_util.h"

using std::cout;
using std::cin;
using std::string;



int t1A(int n) {
  GridWorld *gw = new GridWorld(5, 5);
  int i, id;
  bool found;
  int row, col;
  // vector<int> ref;
  // vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(1, 1, id);
    if(id != i) {
      std::cout << "FAILURE:  id mismatch on birth\n";
      return 0;
    }
    // ref.push_back(i);
  }
  for(id=0; id<n; id++) {

    found = gw->whereis(id, row, col);

    if(!found || row != 1 || col != 1) {
      std::cout << "FAILURE:  whereis result incorrect\n";
      std::cout << "  expected: (return-val,row,col) = (1, 1, 1)\n";
      std::cout << "  received: (return-val,row,col) = (" 
        << found << ", " << row << ", " << col << ")\n";
      return 0;
    }
  }
  return 1;
}

int t1B(int n) {
  GridWorld *gw = new GridWorld(5, 5);
  int i, id;
  bool found;
  int r, c, pop;
  // vector<int> ref;
  // vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(1, 1, id);
    if(id != i) {
      std::cout << "FAILURE:  id mismatch on birth\n";
      return 0;
    }
    // ref.push_back(i);
  }
  pop = gw->population();
  if(pop != n) {
      std::cout << "FAILURE:  gw->population() returned "<< pop 
        << "; expected " << n << "\n";
      return 0;
  }
  pop = gw->population(1, 1);
  if(pop != n) {
      std::cout << "FAILURE:  gw->population(1,1) returned "<< pop 
        << "; expected " << n << "\n";
      return 0;
  }
    
  for(r=0; r<5; r++ ){
    for(c=0; c<5; c++) {
      if(r!=1 || c!=1) {
        pop = gw->population(r, c);
        if(pop != 0) {
          std::cout << "FAILURE:  gw->population(r,c) returned "<< pop 
            << "; expected " << 0 << "\n";
          return 0;
        }
      }
    }
  }
  return 1;
}



int t1C(int n) {
  GridWorld *gw = new GridWorld(5, 5);
  int i, id;
  bool found;
  int row, col;
  // vector<int> ref;
  // vector<int> *m;



  int nrows, ncols;

  nrows = gw->num_rows();
  ncols = gw->num_cols();
  if(nrows != 5 || ncols != 5) {
      std::cout << "FAILURE:  num_rows or num_rows failed\n";
      std::cout << "  expected (nrows, ncols): (5, 5)\n";
      std::cout << "  received (nrows, ncols): (" << nrows << ", " << ncols << ")\n";
      return 0;
  }
  return 1;
}


int t1D(int n) {
  GridWorld *gw = new GridWorld(5, 5);
  int i, id;
  vector<int> ref;
  vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(0, 0, id);
    if(id != i) {
      std::cout << "FAILURE:  id mismatch on birth\n";
      return 0;
    }
    ref.push_back(i);
  }

  m = gw->members(0, 0);
  if(*m != ref) {
    std::cout << "FAILURE:  members wrong\n";
    std::cout << "  expected: ";
    pvec(ref);
    std::cout << "  received: ";
    pvec(*m);

    return 0;
  }
  delete m;
  delete gw;
  return 1;
}

int t1E(int n) {
  GridWorld *gw = new GridWorld(5, 5);
  int i, id;
  vector<int> ref00;
  vector<int> ref11;
  vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(0, 0, id);
    if(id != i) {
      std::cout << "FAILURE:  id mismatch on birth\n";
      return 0;
    }
  }

  for(i=n/2; i<n; i++) {
    if(!gw->move(i, 1, 1) ) {
      std::cout << "FAILURE:  attempted move failed?\n";
      return 0;
    }
    ref11.push_back(i);
  }
  for(i=0; i<n/2; i++) {
    ref00.push_back(i);
  }
  m = gw->members(1, 1);
  if(*m != ref11) {
    std::cout << "FAILURE:  members(1,1) wrong?\n";
    std::cout << "  expected: ";
    pvec(ref11);
    std::cout << "  received: ";
    pvec(*m);
    return 0;
  }
  delete m;
  m = gw->members(0, 0);
  if(*m != ref00) {
    std::cout << "FAILURE:  members(0,0) wrong?\n";
    std::cout << "  expected: ";
    pvec(ref11);
    std::cout << "  received: ";
    pvec(*m);
    return 0;
  }


  if(gw->population(1, 1) != n-(n/2)) {
    std::cout << "FAILURE:  (1,1) pop wrong?\n";
    std::cout << "  expected:  " << n-(n/2) << "\n";
    std::cout << "  reported:  " << gw->population(1,1) << "\n";
    return 0;
  }
  if(gw->population(0, 0) != (n/2)) {
    std::cout << "FAILURE:  (0,0) pop wrong?\n";
    std::cout << "  expected:  " << (n/2) << "\n";
    std::cout << "  reported:  " << gw->population(0,0) << "\n";
    return 0;
  }
  int r, c;
  r=-1; c=-1;
  for(i=0; i<n/2; i++) {
    if(!gw->whereis(i, r, c)) {
      std::cout << "FAILURE:  whereis failed?\n";
      return 0;
    }
    if(r != 0 || c != 0) {
      std::cout << "FAILURE:  whereis " << i << " wrong\n";
      std::cout << "  expected:  (0, 0)\n";
      std::cout << "  reported:  (" << r << ", " << c << ")\n";
      return 0;
    }
  }
  for(i=n/2; i<n; i++) {
    if(!gw->whereis(i, r, c)) {
      std::cout << "FAILURE:  whereis failed (moved id)\n";
      return 0;
    }
    if(r != 1 || c != 1) {
      std::cout << "FAILURE:  whereis" << i << " wrong?\n";
      std::cout << "  expected:  (1, 1)\n";
      std::cout << "  reported:  (" << r << ", " << c << ")\n";
      return 0;
    }
  }
  delete m;
  delete gw;
  return 1;
}

/*
 * test case operates on a 5x5 grid.
 *
 * Optional cmd-line arg is "n" which is used to determine
 *   number of operations (births, etc.) performed.
 *
 * This test case focuses on birth, move and whereis
 */
int main(int argc, char *argv[]){
  int n=10;

  if(argc==2) {
    n = atoi(argv[1]);
  }

  START("~ COLLECTION OF BASIC FUNCTIONAL-TESTS ");
  {

    PtsPer = 5.0;
    
    /**
    TEST_RET(t1A(n), 
        "n births + n whereis ops (functional only)",
        1, PtsPer);
    TEST_RET(t1B(n), 
        "n births + population calls (functional only)",
        1, PtsPer);
        **/

    TEST_RET(t1C(n), 
        "simple num_rows, num_cols functional test",
        1, PtsPer);
    TEST_RET(t1D(n), 
        "simple birth + members functional test",
        1, PtsPer);

    /**
    TEST_RET(t1E(n), 
        "birth + move + members + whereis functional test",
        1, PtsPer);
        **/

  }
  END
  return 0;
}
