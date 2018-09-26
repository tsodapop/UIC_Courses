#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

/** @file t6_filter-D.cpp

        tests filter_leq function in scenario where calling list is
	[10 8 6 4 2 0] and cutoff=5.  
	The two lists are tested
	independently after operation.
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

  START("~List::filter_leq test Suite (D) - 4 pts"); 
  {
	int i;

	  PtsPer = 2.0;

	cleanup();
	{
	 int a[] = {10, 8, 6, 4, 2, 0};
	 int leq[] = {4, 2, 0};
	 int gt[] = {10, 8, 6};

	 lsts[0] = arr2list(a, 6);

	unsigned long int cksum_before;

	cksum_before = lsts[0]->checksum();

	 lsts[1] = lsts[0]->filter_leq( 5);

	 lsts[2] = arr2list(leq, 3); // leq reference list
	 lsts[3] = arr2list(gt, 3); // greater-than reference list

	  TEST_RET(checksum_tst_2lists(lsts[0], lsts[1], cksum_before),
			"test: [10 8 6 4 2 0]; cutoff=5: 'no-new-nodes' test",  
			1, 1.5);

	  TEST_RET(same_contents(lsts[1], lsts[2], 1),
			"test: [10 8 6 4 2 0]; cutoff=5 - is LEQ correct?",
			1, 1.25);
	 
	  TEST_RET(same_contents(lsts[0], lsts[3], 1),
			"test: [10 8 6 4 2 0]; cutoff=5 - is RHS correct?",
			1, 1.25);
	}
        cleanup();

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
  printf("~ ABOUT UNRELIABLE RUNTIME MEASUREMENTS\n");
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
