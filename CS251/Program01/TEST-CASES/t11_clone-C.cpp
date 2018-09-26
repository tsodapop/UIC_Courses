#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

/** @file t11_clone-C.cpp
  two functional tests on clone:  necessary conditions for
    independence of given list and result of clone (e.g., testing
    for shallow copy).
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

  START("~List::clone test Suite (C) - 4.28 pts"); 
  {

    PtsPer = 2.14286;


    /******* SPLIT ********/


    /******* SPLIT ********/
    lsts[0] = one_to_n_lst(5);
    lsts[1] = lsts[0]->clone();
    lsts[1]->push_back( 99);

    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {1, 2, 3, 4, 5, 99};

    TEST_RET(eq2array(lsts[0], a1, 5), 
        "first test of independence of lists after clone",
        1, PtsPer);
    TEST_RET(eq2array(lsts[1], a2, 6), 
        "second test of independence of lists after clone",
        1, PtsPer);
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
