#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"



// char *Desc= "num_range test 2";
/* func: test
 * desc: creates a balanced BST just like range_testA
 *       (tree has 2^(h+1)-1 entries with values 1..2^(h+1)-1)
 *
 *       On this tree, the bst_num_range() function is tested
 *       with n calls using min and max set so that:
 *
 *         the range covers the middle 60% of the tree.
 *
 *       returns 1 if bst_num_range returns correct answer.
 *
 *       Notes:  repeated identical calls to bst_num_range 
 *       are for runtime benchmarking experiments.
 *
 *       Overall runtime should be ~NlogN
 *
 *       If n is small (<20), range_testA is simply called instead.
 */
int test(int h, int n) {
  int lo, hi, delta, i, passed;
  

  bst<int> *t = build_balanced(h);

  lo = n/5;
  hi = n-lo;

  delta = hi-lo+1;
  cout << delta << endl;
  cout << lo << " " << hi << endl;
  // int del = t->num_range( lo, hi);
int del;
  passed = 1;
  for(i=0; i<n; i++) {
    del = t->num_range( lo, hi);
    cout << del << endl;
    if(t->num_range( lo, hi) != delta)
      // del = t->num_range( lo, hi);
      // cout << "BROKEN AT: " << del <<endl;
      passed = 0;
  }
  bst_free(t);
  return passed;
}




int main(int argc, char *argv[]) {
  int n = __N;
  int n2 = __N2;
  int height = __HEIGHT;
  int height2 = __HEIGHT2;
  int ntrials = __NTRIALS;
  clock_t budget;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);



  START("[num_range] : balanced tree + num_range(<middle 60%>) n-times");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 1.0); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 1.5); 
  TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.5, 2.5);


  report();

  END;
}

