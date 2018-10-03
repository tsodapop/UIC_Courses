

#ifndef __UTIL_H
#define __UTIL_H

#define ___N 2000

#ifdef SMALL_TRIALS
#define __NTRIALS 500
#else
#define __NTRIALS 1000
#endif

#include <vector>

/** GLOBAL LISTS AND ARRAYS FOR CONVENIENT ACCESS **/




void pvec(vector<int> &vec) {
  int i;

  cout << " [ ";
  for(i=0; i<vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << "]\n";
}




#endif
