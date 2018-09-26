#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

/** @file t5_prefix-B.cpp

	four functional tests of the prefix function:

	- the first two tests are based on a prefix length equal
		to the list length itself: one test for each of 
		the lists.
	- the other two tests are request a prefix of length-1: then
		there is one test for each of the lists.

*/

int arrs[][5] = {
		{ 1, 2, 3, 4, 5} ,
		{ 5, 4, 3, 2, 1},
		{ 0, 2, 3, 4, 5} ,
		{ 1, 2, 3, 4, 0} ,
		{ 0, 0, 0, 0, 0} ,   //IDX-4
		{ 1, 0, 0, 0, 0} ,   //IDX-5
		{ 0, 0, 0, 0, 1},    //IDX-6
		{ 0, 1, 0, 1, 0}     //IDX-7
	     };

using namespace std;



int main(int argc, char *argv[]){
  int n = ___N;
  int ntrials = __NTRIALS;
  int i, dummy;

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

  START("~List::prefix test Suite (B)  (8 pts)"); 
  {
	int i;

	  PtsPer = 2.0;

    /******* SPLIT ********/

	  cleanup();
	  lsts[0] = arr2list(arrs[0], 5);
	  lsts[1] = lsts[0]->prefix( 5);
	  TEST_RET(eq2array(lsts[1], arrs[0], 5), 
			"n-length prefix test: LHS correct?",
			1, PtsPer);

	  TEST_RET(lsts[0]->is_empty(), 
			"n-length prefix test: RHS correct?",
			true, PtsPer);

	  cleanup();

	  int a[] = {1, 2, 3, 4, 5, 6};
	  int left1[] = {1};
	  int right1[] = {2, 3, 4, 5, 6};

	  int left3[] = {1, 2, 3};
	  int right3[] = {4, 5, 6};

	  int left5[] = {1, 2, 3, 4, 5};
	  int right5[] = {6};

	  lsts[0] = arr2list(a, 6);
	  lsts[1] = lsts[0]->prefix( 1);
	  TEST_RET(eq2array(lsts[1], left1, 1), 
			"length-1 prefix test: LHS correct?",
			1, PtsPer);
	  TEST_RET(eq2array(lsts[0], right1, 5), 
			"length-1 prefix test: RHS correct?",
			1, PtsPer);

    /******* SPLIT ********/



  }
  END













  printf("~\n\nPOST-MORTEM...\n");
  printf("~YOU JUST RAN THIS AUTO-TEST WITH: \n");
  printf("~    N (Big Problem Size) = %i\n", n);
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
