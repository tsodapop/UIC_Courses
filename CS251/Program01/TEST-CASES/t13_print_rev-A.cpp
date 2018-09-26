#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

/** @file t13_print_rev-A.cpp
  three functional tests on print_rev (not auto-scored; must examine output):: 
    - print_rev on [1 2 3 4 5]
    - exact same test again (to make sure list itself wasn't reversed)
    - print_rev on an empty list
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

  START("~List::print_rev Suite (15 pts)"); 
  {
	  lsts[0] = arr2list(arrs[0], 5);
	  lsts[1] = new List<int>();  // empty list


	  PtsPer = 5.0;
	  MANUAL(lsts[0]->print_rev(), "5 4 3 2 1", PtsPer);
	  // make sure they didn't actually reverse the list!
	  MANUAL(lsts[0]->print_rev(), "5 4 3 2 1", PtsPer);

	  MANUAL(lsts[1]->print_rev(), "[] (empty)", PtsPer);


  }
  END_MANUAL

  printf("~\n\nPOST-MORTEM...\n");
  printf("~THIS TEST REQUIRES MANUAL INSPECTION OF OUTPUT...\n");
  printf("~     (NOT AUTO-GRADED, BUT LOG INDICATES EXPECTED OUTPUT\n");
  cleanup();

  return 0;
}
