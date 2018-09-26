#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

/** @file t14-compare-C.cpp

	two functional tests:
        
	- lists of same length and identical except at last position.
        - longer list comes before shorter lists (lexicographically)
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

  START("~List::compare_with test Suite (C) - 3.75 pts"); 
  {
    PtsPer = 1.875;


    /******* SPLIT ********/
    cleanup();

    int aa[] = {1, 2, 3};
    int bb[] = {1, 2, 4};

    lsts[0] = arr2list(aa, 3);
    lsts[1] = arr2list(bb, 3);
    TEST_RET(lsts[0]->compare_with(*lsts[1]), 
        "differ at last position",
        -1,  PtsPer);

    cleanup();

    int c[] = {3, 3, 1, 3, 8, 12};
    int d[] = {3, 4, 99};

    lsts[0] = arr2list(c, 6);
    lsts[1] = arr2list(d, 3);
    TEST_RET(lsts[0]->compare_with(*lsts[1]), 
        "longer list comes first",
        -1,  PtsPer);

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
