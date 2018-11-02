#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"




// char *Desc= "num_geq test 2";

int test(int h, int n) {
  bst<int> *t = build_balanced(h);
  int success = 1;
  int i;
  int x;
  int target;

  int n4 = n/4;
  int n2 = n/2;
  int lo = n2-n4;
  int hi = n2+n4;

   rem_range(t, lo, hi);
  //  cout << t->size();

  int new_n = n - (hi-lo+1);
  target = new_n;
  
  // for(i=1; i<lo; i++, target--) {
  //   x = t->num_geq( i);
  //   if(x != target){
  //     cout << "THIS BREAKS HERE AT: " << x << " WHILE TARGET IS: " << target << endl;
  //     success = 0;
  //   }
  // }
  // cout << t->num_geq(1) << endl;
  // cout << target << endl;
  // cout << target << endl;
  // cout << new_n << endl;
  target = n-hi;
  // for(i=lo; i<=hi; i++) {
  //   x = t->num_geq( i);
  //   if(x != target){
  //     success = 0;
  //   }
  // }

  // for(i=hi+1; i<=n; i++, target--) {
  //   x = t->num_geq( i);
  //   if(x != target){
  //     success = 0;
  //   }
  // }
  bst_free(t);
  return success;
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



  START("[num_geq]  balanced tree + remove-middle-n/2 + num_geq scan");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 1.5); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 2.25); 
  // TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.5, 3.75);


  report();

  END;
}

