#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

using namespace std;

/** @file t1-eq_to-C.cpp

	three tests of equal_to() function (one functional; one runtime):

        - functional test: two empty lists
        - runtime test: singleton [1] vs. long list [1 2 ... n]  (O(1))
        - runtime test: [1..n] vs [1..n+1] (THETA(n))
*/

// global array of arrays used to initialize
//   lists...

int arrs[][5] = {
		{ 1, 2, 3, 4, 5} ,  // idx-0
		{ 5, 4, 3, 2, 1},   // idx-1
		{ 1, 2, 3, 4, 5} ,  // idx-2
		{ 0, 2, 3, 4, 5} ,  // idx-3
		{ 1, 2, 3, 4, -99} ,  // idx-4
	     };

int main(int argc, char *argv[]){
  int n = ___N;
  int ntrials = __NTRIALS;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  printf("~STARTING AUTO-TEST WITH: \n");
  printf("~    N (Big Problem Size) = %i\n", n);
  printf("~    NUM_TRIALS       = %i\n", ntrials);
  printf("~USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");
  printf("~    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  printf("~EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  printf("~    %s 9999 100000\n\n", argv[0]);

  printf("~here we go...\n\n");


  START("~List::equal_to TESTS (C) - 4 points"); 
  {
    lsts[0] = arr2list(arrs[0], 5);
    lsts[1] = arr2list(arrs[1], 5);
    lsts[2] = arr2list(arrs[2], 5);

    lsts[3] = arr2list(arrs[3], 5);
    lsts[4] = arr2list(arrs[4], 4);

    lsts[5] = new List<int>();
    lsts[6] = new List<int>();

    PtsPer = 1.0;

    /******* SPLIT ********/

    TEST_RET(lsts[5]->equal_to(*lsts[6]), 
        "eq test - two empty lists", 1, PtsPer);


    PtsPer = 1.5;


    lsts[7] = one_to_n_lst(1);
    lsts[8] = one_to_n_lst(n);
    lsts[9] = one_to_n_lst(2*n);

    set_ntrials(30000*ntrials);

    TIME_RATIO(lsts[7]->equal_to(*lsts[8]), lsts[7]->equal_to(*lsts[9]),
        "runtime test (O(1)) (singleton vs long list)",
        false, 1.25, PtsPer);


    lsts[10] = one_to_n_lst(n);
    lsts[11] = one_to_n_lst(n+1);

    lsts[12] = one_to_n_lst(2*n);
    lsts[13] = one_to_n_lst(2*n+1);
    set_ntrials(20*ntrials);

    TIME_RATIO(lsts[10]->equal_to(*lsts[11]), lsts[12]->equal_to(*lsts[13]),
        "runtime test (THETA(n)) (1..n; vs 1..n+1)",
        false, 2.25, PtsPer);

  }
  END

  printf("~\n\nPOST-MORTEM...\n");
  printf("~YOU JUST RAN THIS AUTO-TEST WITH: \n");
  printf("~    N (Problem Size) = %i\n", n);
  printf("~    NUM_TRIALS       = %i\n\n", ntrials);
  printf("~IF YOU RECEIVED A ");
  _red_txt();
  printf("~WARNING ");
  _normal_txt();
  printf("~ ABOUT UNRELIABLE RUNTIEM MEASUREMENTS\n");
  printf("~AND INCREASING NUMBER OF TRIALS / PROBLEM SIZE\n");
  printf("~HERE IS HOW YOU DO IT:\n\n");
  printf("~  USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");


  _cyan_txt();
  printf("~    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  _normal_txt();
  printf("~  EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  _cyan_txt();
  printf("~    %s 9999 100000\n\n", argv[0]);
  _normal_txt();

  cleanup();

  return 0;
}
