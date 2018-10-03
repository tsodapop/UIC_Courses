
#include "GridWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::cin;
using std::string;

// /*
//  * defaults to a 5x5 grid.
//  *
//  * Recommendation:  why not modify so you can take command-line
//  *  arguments specifying the grid dimensions?
//  */

bool t2A(int n) {
  GridWorld *gw = new GridWorld(20, 20);
  int i, id;
  vector<int> ref;
  vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(0, 0, id);
    if(id != i) {
      // std::cout << "FAILURE type-1:  id mismatch on birth\n";
      return false;
    }
    ref.push_back(i);
  }
  m = gw->members(0, 0);
  if(*m != ref) {
    // std::cout << "FAILURE type-2:  members wrong?\n";
    return false;
  }
  for(i=n/2; i<n; i++) {
    if(!gw->death(i)) {
      /*
      std::cout << "FAILURE type-3:  attempted death failed?\n";
      std::cout << "    attempted kill:  " << i << "\n";
      */
      return false;
    }
  }
  if(gw->population() != n/2) {

    std::cout << "FAILURE type-4:  world pop wrong?\n";
    std::cout << "  expected:  " << n/2 << "\n";
    std::cout << "  reported:  " << gw->population() << "\n";
    return false;
  }
  cout << gw->population() << endl;
  return true;
}


int main(){
  int etest = 0;
  int id;
  int i;
  int n = 10;
  int row = 1;
  int col = 1;
  int moveRow = 2;
  int moveCol = 2;
  int k = 5;
  // GridWorld *gw = new GridWorld(5, 5);

  GridWorld *gw = new GridWorld(20, 20);
  vector<int> ref;
  vector<int> *m;

    for(i=0; i<n; i++) {
    gw->birth(0, 0, id);
    if(id != i) {
      // std::cout << "FAILURE type-1:  id mismatch on birth\n";
      return 0;
    }
    ref.push_back(i);
  }

  m = gw->members(0, 0);
  if(*m != ref) {
    // std::cout << "FAILURE type-2:  members wrong?\n";
    return 0;
  }

// cout << gw->population() << endl;
// return false;
  // for(i=n/2; i<n; i++) {
  //   if(!gw->death(i)) {
  //     /*
  //     std::cout << "FAILURE type-3:  attempted death failed?\n";
  //     std::cout << "    attempted kill:  " << i << "\n";
  //     */
  //     return 0;
  //   }
  // }
  // cout << gw->population() << endl;
  // t2A(n);
  // gw->birth(0,0, id);
  cout << gw->move(5,1,1) << endl;
  // gw->move(1,1,1);
  cout << gw->move(6,1,1) << endl;
  cout << gw->move(7,1,1) << endl;
  cout << gw->move(8,1,1) << endl;
  cout << gw->move(9,1,1) << endl;
  // t2A(2*n);
  // cout << gw->population(0,0) << endl;
  // gw->printDistrict(2,2);
  // gw->printDistrict(4,1);
  // gw->printDistrict(1,1);
  // gw->whereis(0, row, col);
  // cout << row << " " << col << endl;
  // gw->printVector();
  gw->printDistrict(0,0);
  gw->printDistrict(1,1);

  /*----------------------------testing members vector----------------------------*/ 
  // vector<int> *test = gw->members(2,2);
  // gw->printMembersVector(test);
  /*----------------------------testing members vector----------------------------*/ 

  /*----------------------------testing graveyard----------------------------*/ 
  // gw->printGraveyard();




  return 0;
}
