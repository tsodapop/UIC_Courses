#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

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


/** @file t10_insert_sorted-A.cpp
  Three functional tests on insert_sorted:
         - insertion of new min
         - insertion of new max
         - insertion of value "in between"
*/



int main(int argc, char *argv[]){
  int n = ___N;
  int ntrials = __NTRIALS;
  int i, dummy;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  printf("~~STARTING AUTO-TEST WITH: \n");
  printf("~~    N (Big Problem Size) = %i\n", n);
  printf("~~    NUM_TRIALS       = %i\n", ntrials);
  printf("~~USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");
  printf("~~    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  printf("~~EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  printf("~~    %s 9999 100000\n\n", argv[0]);

  printf("~~here we go...\n\n");

  START("~~List::insert_sorted test Suite (A) - 9 pts"); 
  {
	  int a0[]        = {5, 5, 6, 9, 12};
	  int a1[]        = {0, 5, 5, 6, 9, 12};  // insert front
	  int a2[]        = {5, 5, 6, 9, 12, 13}; // insert end
	  int a3[]        = {5, 5, 6, 7, 9, 12};  // insert middle (7)

	  int b[]        = {9, 11, 22, 9, 0, 0, 22, 0};
	  int b_sorted[] = {0, 0, 0, 9, 9, 11, 22, 22};

	  int i;

	  PtsPer = 3;


	  lsts[0] = arr2list(a0, 5);
	  lsts[1] = arr2list(a1, 6);
	  lsts[0]->insert_sorted( 0);
	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[1]), 
			"insert_sorted: new min case",
			1, PtsPer);
	  cleanup();

	  lsts[0] = arr2list(a0, 5);
	  lsts[1] = arr2list(a2, 6);
	  lsts[0]->insert_sorted( 13);
	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[1]), 
			"insert_sorted: new max case",
			1, PtsPer);
	  cleanup();

	  lsts[0] = arr2list(a0, 5);
	  lsts[1] = arr2list(a3, 6);
	  lsts[0]->insert_sorted( 7);
	  TEST_RET_MESSAGE(lsts_equal_destructive(lsts[0], lsts[1]), 
			"insert_sorted: middle insertion case",
			1, PtsPer);
	  cleanup();


	  
  }
  END

  printf("~~\n\nPOST-MORTEM...\n");
  printf("~~YOU JUST RAN THIS AUTO-TEST WITH: \n");
  printf("~~    N (Big Problem Size) = %i\n", n);
  printf("~~    NUM_TRIALS       = %i\n\n", ntrials);
  printf("~~IF YOU RECEIVED A ");
  _red_txt();
  printf("~~WARNING ");
  _normal_txt();
  printf("~~ ABOUT UNRELIABLE RUNTIME MEASUREMENTS\n");
  printf("~~AND INCREASING NUMBER OF TRIALS / PROBLEM SIZE\n");
  printf("~~HERE IS HOW YOU DO IT:\n\n");
  printf("~~  USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");


  _cyan_txt();
  printf("~~    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  _normal_txt();
  printf("~~  EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  _cyan_txt();
  printf("~~    %s 9999 100000\n\n", argv[0]);
  _normal_txt();

  cleanup();

  return 0;
}
