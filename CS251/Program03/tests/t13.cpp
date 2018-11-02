#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"



// char *Desc= "num_range test 3";
/**
 * func: test
 * desc: creates a balanced BST just like range_testA
 *       (tree has 2^(h+1)-1 entries with values 1..2^(h+1)-1)
 *
 *       BUT, then all even entries are removed one-by-one.
 *       Result:  an O(logN) height tree storing odd values
 *                of which there are 2^h
 *
 *       THEN:  the bst_num_range() function is tested
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
 */
int test(int h, int init_n) {
  int lo, hi, delta, i, passed, answer;
  int max;
  

  bst<int> *t = build_balanced_rem_evens(h);
                            //   there are 2^h odd entries
                            //    (before and after removing evens)

  max = two_to_x(h+1)-1;
  int n   = two_to_x(h);

  lo = max/5;
  hi = max-lo;
  cout << "testsetset\n" << n << " " <<  lo << " " << hi << endl;
  answer = (hi-lo)/2;
  if((hi%2) || (lo%2))
    answer++;
  cout << "answer: " << answer << endl;
  cout << "leq hi: " << t->num_leq(hi);
  cout << "leq lo: " << t->num_leq(lo);
  passed = 1;
  for(i=0; i<n; i++) {
    if(t->num_range( lo, hi) != answer)
      // cout << "BROKEN BY THE ANSWER: " << t->num_range(lo,hi) << " IT SHOULD BE " << answer << endl;
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



  START("[num_range]: balanced tree + remove-evens + num_range(<middle 60%>) n-times");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 1.0); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 1.5); 
  TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.5, 2.5);


  report();

  END;
}

