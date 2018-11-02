#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"



// char *Desc= "num_range test 1";

/* func: test
 * desc: creates a complete binary tree of height h.
 *       tree has 2^(h+1)-1 entries with values 1..2^(h+1)-1
 *
 *       Balance is forced by insertion sequence --  even
 *       if size-balancing not implemented, the tree will
 *       be balanced.
 *
 *       Then, n identical calls are made to bst_num_range with
 *       min==-1 and max==n+2 (i.e., all elements are in the
 *       range).
 *
 *       returns 1 if bst_num_range returns correct answer.
 *               0 otherwise
 *
 *       Notes:  repeated identical calls to bst_num_range 
 *       are for runtime benchmarking experiments.
 *
 *       Overall runtime should be ~NlogN
 *
 */
int test(int h, int n) {
  bst<int> *t = build_balanced(h);
  int x, passed, i;

  passed = 1;
  for(i=0; i<n; i++) {
    if(t->num_range( -1, n+2) != n)
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

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);



  START("[num_range]:  balanced tree + num_range(-1,n+2) n-times");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 1.0); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 1.5); 
  TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.5, 2.5);


  report();

  END;
}

