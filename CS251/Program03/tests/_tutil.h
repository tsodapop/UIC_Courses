

/**
 * General description:   utility functions for
 *     building BSTs and testing bst_XXX functions.
 *
 *     Includes a variety of tree building procedures
 *     and tests.
 */
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

#define __N 1023
#define __N2 2047
#define __NTRIALS 1000
#define __HEIGHT 9
#define __HEIGHT2 10



bst<int>  * bst_create() {
  return new bst<int>();
}

void bst_free(bst<int> *t) {
  delete t;
}

int two_to_x(int x) {
  if(x<1) return 1;
  return 2*two_to_x(x-1);
}

/* function:  max_sb_height
 ** desc:      returns maximum possible height of a
 **            size-balanced tree with n nodes.
 **
 ** Idea:  if you have a size-balanced tree with n
 **        nodes, it can't be any taller than what
 **        this function reports.
 **/
int max_sb_height(int n) {
  unsigned int big;

  if(n<=0) return -1;
  if(n==1) return 0;
  big = (n-1) - (n/3);  
  // makes as imbalanced as possible within rules
  //    of being size-balanced
  //
  return 1 + max_sb_height(big);
}

int sb_height_ok(bst<int> *t) {
  int height, max_h, n;

  n = t->size();
  height = t->height();

  max_h = max_sb_height(n);

  if(height > max_h) {
    return 0;
  }
  return 1;
}

/*
 * func: seq_build ("build BST via sequential insertions")
 * desc: creates an empty BST and inserts n
 *       values sequentially with first insertion
 *       being being start.
 *
 *       Resulting tree stored in *pt
 *
 * example:  if n==5 and start==-2, the following 
 *           values are inserted in sequence:
 *
 *           -2, -1, 0, 1, 2
 */
void seq_build(int n, int start, bst<int> *&pt) {
  int i, x;
    pt = new bst<int>();
    for(i=1, x=start; i<=n; i++, x++)
        pt->insert(x);
}

void seq_build_descending(int n, int start, bst<int> *&pt) {
  int i, x;

    pt = new bst<int>();
    for(i=1, x=start; i<=n; i++, x--)
        pt->insert(x);
}

/*
 * func: build_1_N
 * desc: creates an empty BST and then sequentially
 *       inserts 1..n
 *
 *       Resulting tree stored in *pt
 *
 *       Always returns 1
 */
void build_1_N(int n, bst<int> *&pt) {
  int i;
  
  seq_build(n, 1, pt);
}

/*
 * func: build_N_1
 * desc: creates an empty BST and then sequentially
 *       inserts n..1 (descending order). 
 *
 *       Resulting tree stored in *pt
 *
 *       Always returns 1
 */
void build_N_1(int n, bst<int> *&pt) {
  int i;
  
  seq_build_descending(n, n, pt);
}
/*
 * func: build_1_N_free
 * desc: starting from an empty BST insertes
 *       integers 1..n sequentially.
 *       Frees tree on completion and returns 1
 *       (thus only useful for time trials).
 */
int build_1_N_free(int n) {
  bst<int> *t;

    build_1_N(n, t);
    delete t;
    return 1;
}



/*
 * func: rem_range
 * desc: calls bst_remove on given BST with all values between
 *       lo and hi inclusive.
 *
 *       Expected use case:  given tree does indeed contain
 *         all values in the range when called.  Thus all
 *         removals should succeed.
 *
 *       return:  number of successful removals.
 */
int rem_range(bst<int> *t, int lo, int hi){
  int x;
  int ndel = 0;

  for(x=lo; x<=hi; x++) {
    if(!t->remove(x)) {
      fprintf(stderr, 
          "WARNING - rem_range(), x=%i NOT IN TREE?\n", x);
      fprintf(stderr, 
          "   IF TREE ASSUMED TO INITIALLY CONTAIN ELEMENTS 1..%i\n", hi);
      fprintf(stderr, 
          "   SUBSEQUENT RESSULTS LIKELY TO BE MEANINGLESS\n\n");
    }
    else {
      ndel++;
    }
  }
  return ndel;
}

/*
 * functions rem_XXX_third
 * desc:  these functions do the following:
 *
 *        - these functions assume that the given tree
 *          is populated with ints 1..n
 *        - Then then delete their specified 'third'
 *        - each returns the number of deletions successfully
 *          performed.
 *
 * the "out parameters" described below allow caller to determine
 *    which elements remain after operation.
 *
 *    rem_first_third:  *hi stores the largest value deleted.
 *    rem_last_third:  *lo stores the smallest value deleted.
 *    rem_middle_third:  *lo stores the smallest value deleted.
 */
int rem_first_third(bst<int> *t, int n, int &hi) {
  int third;

  third = n/3;
  hi = third;
  return rem_range(t, 1, third);
}
int rem_last_third(bst<int> *t, int n, int *lo) {

  *lo = (2*n)/3;
  return rem_range(t, *lo, n);
}

int rem_middle_third(bst<int> *t, int n, int *lo, int *hi) {

  *lo = n/3;
  *hi = 2*(*lo);
  return rem_range(t, *lo, *hi);
}


/*
 * func: build_balanced
 * desc: builds a complete BST of height h.
 *       keys:  1..2^(h+1)-1
 *
 *       Tree is perfectly balanced by construction.
 *       (insertion sequence ensures balanced structure
 *       without any kind of balancing).
 *
 *       returns resulting BST
 */
bst<int>* build_balanced(int h) {
  bst<int> *t = bst_create();
  int n, nleaves, i, level, start, delta, x;

  if(h==-1) return t;

  nleaves=1;
  for(i=0; i<h; i++) {
    nleaves *= 2;
  }
  n = 2*nleaves - 1;

  delta=2*nleaves;
  start=(n+1)/2;
  for(level=0; level<=h; level++) {
      for(x=start; x<=n; x+=delta) {
        // printf("balanced-insert:  insert(%i)\n", x);
        t->insert( x);
      }
      delta /= 2;
      start /= 2;
  }

  return t;
}

bst<int> * build_balanced_rem_evens(int h) {
  bst<int> *t = build_balanced(h);
  int x;
  int n = two_to_x(h+1)-1;

  for(x=2; x<=n; x+=2) {
    t->remove( x);
  }
  return t;
}



/* func: leq_testA
 * desc: builds a perfectly balanced BST of specified height
 *       and containing n=2^(h+1)-1 nodes.
 *       (Values:  1..n)
 *
 *       Then:  performs n+2 bst_num_leq tests
 *
 *       Results communicated via:
 *
 *           *ntests:   number of tests performed
 *           *npassed:  number of tests passed.
 *
 *       return:  always returns 1 
 *
 *       Runtime:  should be prop to nlogn even if size-balancing
 *         has not been implemented.
 */
int leq_testA(int h, int *ntests, int *npassed) {
  bst<int> *t = build_balanced(h);
  int x;
  int n = two_to_x(h+1)-1;

  *ntests=0;
  *npassed=0;

  if(t->num_leq( -2) == 0)
    (*npassed)++;
  (*ntests)++;

  for(x=1; x<=n; x++) {
    if(t->num_leq( x)==x)
      (*npassed)++;
    (*ntests)++;
  }
  if(t->num_leq( n+2) == n)
    (*npassed)++;
  (*ntests)++;
  delete t;
  return 1;
}






/* func: leq_testB
 * desc: builds a perfectly balanced BST of specified height
 *       and containing n=2^(h+1)-1 nodes.
 *       (Values:  1..n)
 *
 *       Then:  removes all of the even entries by calling
 *              bst_remove
 *
 *       Then:  performs n+2 bst_num_leq tests
 *
 *       Results communicated via:
 *
 *           *ntests:   number of tests performed
 *           *npassed:  number of tests passed.
 *      
 *       return:  always returns 1 
 *
 *       Runtime:  should be ~nlogn even if size-balancing 
 *       not implemented.
 */
int leq_testB(int h, int *ntests, int *npassed) {
  bst<int> * t = build_balanced_rem_evens(h);
  int x, n_odds, n_evens;
  int n = two_to_x(h+1)-1;

  *ntests=0;
  *npassed=0;

  if(t->num_leq( -2) == 0)
    (*npassed)++;
  (*ntests)++;

  n_odds = 0;
  for(x=1; x<=n; x++) {
    n_odds += (x%2);
    if(t->num_leq( x)==n_odds)
      (*npassed)++;
    (*ntests)++;
  }
  n_evens = (n+1)/2;
  if(t->num_leq( n+2) == n_evens)
    (*npassed)++;
  (*ntests)++;
  delete t;
  return 1;
}


/* func: range_testA
 * desc: creates a complete binary tree of height h.
 *       tree has 2^(h+1)-1 entries with values 1..2^(h+1)-1
 *
 *       Balance is forced by insertion sequence --  even
 *       if size-balancing not implemented, the tree will
 *       be balanced.
 *
 *       Then, n identical calls are made to bst_num_range with
 *       min==-1 and max==n+2 (i.e., all elements are in the
 *       range).
 *
 *       returns 1 if bst_num_range returns correct answer.
 *               0 otherwise
 *
 *       Notes:  repeated identical calls to bst_num_range 
 *       are for runtime benchmarking experiments.
 *
 *       Overall runtime should be ~NlogN
 *
 */
int range_testA(int h) {
  bst<int> *t = build_balanced(h);
  int x, passed, i;
  int n = two_to_x(h+1)-1;

  passed = 1;
  for(i=0; i<n; i++) {
    if(t->num_range( -1, n+2) != n)
      passed = 0;
  }
  delete t;
  return passed;
}

/* func: range_testB
 * desc: creates a balanced BST just like range_testA
 *       (tree has 2^(h+1)-1 entries with values 1..2^(h+1)-1)
 *
 *       On this tree, the bst_num_range() function is tested
 *       with n calls using min and max set so that:
 *
 *         the range covers the middle 60% of the tree.
 *
 *       returns 1 if bst_num_range returns correct answer.
 *
 *       Notes:  repeated identical calls to bst_num_range 
 *       are for runtime benchmarking experiments.
 *
 *       Overall runtime should be ~NlogN
 *
 *       If n is small (<20), range_testA is simply called instead.
 */
int range_testB(int h) {
  int lo, hi, delta, i, passed;
  int n = two_to_x(h+1)-1;
  
  if(n<20)
    return range_testA(h);

  bst<int> *t = build_balanced(h);

  lo = n/5;
  hi = n-lo;

  delta = hi-lo+1;

  passed = 1;
  for(i=0; i<n; i++) {
    if(t->num_range( lo, hi) != delta)
      passed = 0;
  }
  delete t;
  return passed;
}

/**
 * func: range_testC
 * desc: creates a balanced BST just like range_testA
 *       (tree has 2^(h+1)-1 entries with values 1..2^(h+1)-1)
 *
 *       BUT, then all even entries are removed one-by-one.
 *       Result:  an O(logN) height tree storing odd values
 *                of which there are 2^h
 *
 *       THEN:  the bst_num_range() function is tested
 *       with n calls using min and max set so that:
 *
 *         the range covers the middle 60% of the tree.
 *
 *       returns 1 if bst_num_range returns correct answer.
 *
 *       Notes:  repeated identical calls to bst_num_range 
 *       are for runtime benchmarking experiments.
 *
 *       Overall runtime should be ~NlogN
 *
 */
int range_testC(int h) {
  int lo, hi, delta, i, passed, answer;
  int max, n;
  
  if(n<40)
    return range_testA(h);

  bst<int> *t = build_balanced_rem_evens(h);
                            //   there are 2^h odd entries
                            //    (before and after removing evens)

  max = two_to_x(h+1)-1;
  n   = two_to_x(h);

  lo = max/5;
  hi = max-lo;

  answer = (hi-lo)/2;
  if((hi%2) || (lo%2))
    answer++;
  
  passed = 1;
  for(i=0; i<n; i++) {
    if(t->num_range( lo, hi) != answer)
      passed = 0;
  }
  delete t;
  return passed;
}


