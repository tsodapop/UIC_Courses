#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"



// char *Desc= "size-balanced test 1";
/**
 * func: test
 * desc: tests size-balancing by inserting elements 1..n sequentially
 *
 *       Overall runtime should be ~NlogN
 *
 */
int test(int n) {
  int success1 = 1;
  int success2 = 1;
  int i;
  static int first = 1;
  

  bst<int> *t;

  build_1_N(n, t);

  if(!sb_height_ok(t))
    success1 = 0;

  for(i=1; i<=n; i++) {
    if(!t->contains( i))
      success2 = 0;
  }

  if(first) {
    if(!success1)
      printf("   FAILED HEIGHT TEST\n");
    if(!success2)
      printf("   FAILED bst_contains TEST after build\n");
  }
  first = 0;

  bst_free(t);

  return success1 && success2;
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



  START("[size-balancing] test: insert 1..N in order (size-balanced test)");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 4.0); 
  TEST_RET_MESSAGE(test(n), "CORRECTNESS-ONLY-TEST", 1, 6.0); 
  TIME_RATIO(test(n), test(n2), "", 1, 2.5, 10.0);


  report();

  END;
}

