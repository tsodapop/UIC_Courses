#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

/** @file t7_merge-B.cpp

        two functional tests of the merge function:

	- first test does a push_back after merge to test
		state of list after merge (esp. if
		back pointer set correctly).
	- second test merges [1 2 3 4 5] & [6 7 8 9 10] 
		and checks the result.
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

  START("~List::merge_with test Suite (B) 6.67 pts"); 
  {
	int i;

	int a[] = {5, 7, 7, 10, 12};
	int b[] = {0, 1, 6, 11, 20};
	int ab[] = {0, 1, 5, 6, 7, 7, 10, 11, 12, 20, 99}; 

	int x[] = {1, 2, 3, 4, 5};
	int y[] = {6, 7, 8, 9, 10};
	int xy[] ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	  PtsPer = 3.33333;



	  lsts[0] = arr2list(a, 5);
	  lsts[1] = arr2list(b, 5);

	  lsts[0]->merge_with(*lsts[1]);
	  lsts[0]->push_back( 99);
	  TEST_RET(eq2array(lsts[0], ab, 11), 
			"Test push-back(99) after merge",
			1, PtsPer);


	 cleanup();
	  lsts[0] = arr2list(x, 5);
	  lsts[1] = arr2list(y, 5);

	unsigned long int cksum_before;
	cksum_before = lsts[0]->checksum() ^ lsts[1]->checksum();;

	  lsts[0]->merge_with(*lsts[1]);

	  TEST_RET(cksum_and_eq2array(lsts[0], xy, 10, cksum_before), 
	"merge [1 2 3 4 5] & [6 7 8 9 10] (including 'no-new-nodes' rule",
			1, PtsPer);
	


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
