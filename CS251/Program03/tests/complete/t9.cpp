#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#include "_test.h"
#include "_tutil.h"



// char *Desc= "num_geq test 1";


/* func: test
 * desc: builds a perfectly balanced BST of specified height
 *       and containing n=2^(h+1)-1 nodes.
 *       (Values:  1..n)
 *
 *       Then:  performs n+2 bst_num_geq tests
 *
 *       return:  success/failure
 *
 *       Runtime:  should be prop to nlogn even if size-balancing
 *         has not been implemented.
 */
int test(int h, int n) {
  bst<int> *t = build_balanced(h);
  int x;
  int success = 1;
  int target;

  cout << n << endl;
  if(t->num_geq( -2) != n)
    success = 0;

  target = n;
  for(x=1; x<=n; x++, target--) {
    if(t->num_geq( x)!=target)
      success = 0;
  }
  if(t->num_geq( n+2) != 0)
      success = 0;
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



  START("[num_geq]  balanced tree + num_geq scan");

  TEST_RET_MESSAGE(baseline(), "COMPILATION", 1, 1.5); 
  TEST_RET_MESSAGE(test(height, n), "CORRECTNESS-ONLY-TEST", 1, 2.25); 
  // cout << height << " " << n << endl;
  TIME_RATIO(test(height, n), test(height2, n2), "", 1, 2.5, 3.75);


  report();

  END;
}

