#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"




// char *Desc= "bst_to_array test 2";

int test(int h, int n) {
  bst<int> *t = build_balanced_rem_evens(h);
  int success = 1;
  int i, tgt;

  int nodd = (n+1)/2;

  std::vector<int> *a = t->to_vector();

  if(a->size() == nodd) {
    for(i=0, tgt=1; i<nodd; i++, tgt+=2) {
      if((*a)[i] != tgt)
        success = 0;
    }
  }
  else
    success = 0;
  bst_free(t);
  delete a;
  return success;
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



  START("[to_array]: balanced tree + remove_evens + to_array");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 2.0); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 3.0); 
  TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.4, 5.0);


  report();

  END;
}

