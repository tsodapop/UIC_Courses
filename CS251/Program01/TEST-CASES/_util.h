
#ifndef __UTIL_H
#define __UTIL_H

#define ___N 5000

#ifdef SMALL_TRIALS
#define __NTRIALS 1000
#else
#define __NTRIALS 10000
#endif

/** GLOBAL LISTS AND ARRAYS FOR CONVENIENT ACCESS **/


List<int> * lsts[20] = {nullptr};

/** END GLOBALS **/


int checksum_tst(List<int> *lst, 
    unsigned long int expected) {

  return lst->checksum() == expected;
}

int checksum_tst_2lists(List<int> *lst1, List<int> *lst2,
    unsigned long int expected) {

  return (lst1->checksum() ^ lst2->checksum()) == expected;
}


void cleanup(){
  int n = sizeof(lsts)/sizeof(List<int> *);
  int i;


  for(i=0; i<n; i++) {
    if(lsts[i] != nullptr) 
      delete lsts[i];
    lsts[i]=nullptr;
  }
}

List<int> * one_to_n_lst(int n) {
List<int> *lst;

  lst = new List<int>();
  while(n) {
    lst->push_front(n);
    n--;
  }
  return lst;
}

List<int> * lst_of_n_ones(int n) {
List<int> *lst;

  lst = new List<int>();
  while(n) {
    lst->push_front(1);
    n--;
  }
  return lst;
}
  
// destructive
bool eq2array(List<int> *lst, int a[], int n) {
  int ret = true;
  int i, x;

  if(lst->length() != n){
    if(Verbose) {
       ERRMSG("eq2array: TYPE-1 err - list and array not of same length");
    } 
    return false;
  }

  for(i=0; i<n; i++) {
    if(!lst->pop_front(x) ) {
      if(Verbose) {
         ERRMSG("eq2array: TYPE-2 err - unexpected pop_front failure");
      }
      return false;
    }
    if(x != a[i]){
      ret = false;
      if(Verbose) {
        ERRMSG("eq2array: TYPE-3 err - mismatch [i, a[i], x] = ", 
            i, a[i], x);

      }
    }
  }
  return ret;

}

bool cksum_and_eq2array(List<int> *lst, int a[], int n,
    unsigned long int expected_sum) {

  if(lst->checksum() != expected_sum) {
    return false;
  }
  return eq2array(lst, a, n);
}

/**
void parray(int a[], int n) {
int i;

  printf("    [ ");
  for(i=0; i<n; i++) {
    printf(" %i ", a[i]);
  }
  printf("]\n");
}
**/

int eq2arrayP(List<int> *lst, int a[], int n) {
  printf("~      Expected Contents:  ");
  parray(a, n);
  printf("~      Your List        :  ");
  lst->print();
  return eq2array(lst, a, n);
}


List<int> * arr2list(int a[], int n) {
  List<int> *lst = new List<int>();

  int i;

  for(i=0; i<n; i++)
    lst->push_back(a[i]);
  return lst;
}

bool lst_eq_arr(List<int> *lst, int a[], int n) {
int n2=0;
int i=0;
int x;

  while(i<n && !lst->is_empty()) {

    if(!lst->pop_front(x)){
      return false;
    }
    if(x != a[i])
      return false;
    i++;
  }
  if(i<n || !lst->is_empty())
    return false;
  return true;

}

// determines if lists a and b have same elements
//   (in the same order) without relying on the 
//   equal_to function.
//
//   This function is destructive -- it empties the
//   lists in the process.
bool lsts_equal_destructive(List<int> *a, List<int> *b) {
  int n;
  bool ret=true;
  int x, y;

  while(!a->is_empty() && !b->is_empty()) {
    if(!a->pop_front(x)|| !b->pop_front(y)){
      ret = false;
      if(Verbose) 
        ERRMSG("lsts_equal_destructive: TYPE-1 err; one or both pop_front calls failed");

    }
    if(x != y) {
      ret = false;
      if(Verbose) 
        ERRMSG("lsts_equal_destructive: TYPE-2 err; popped values do not match");
    }
  }
  if(!b->is_empty() || !a->is_empty()){
    ret = false;
    if(Verbose) 
      ERRMSG("lsts_equal_destructive: TYPE-3 err; one list non-empty");
  }
  return ret;
} 

/*
* first checks if the checksum(a) ^ checkum(b) == target;
* (i.e., all nodes among both lists have a specified 
*   checksum).
*
* returns false if not.
*
* otherwise (checksum test passed), the 
bool lsts_equal_destructive_plus_cksum(
     List<int> *a, List<int> *b, unsigned int long cksum) {
**/
/**********************************************/

/**
int num_occ(int a[], int n, int x) {
int matches=0;
int i;

  for(i=0; i<n; i++) {
	if(a[i]==x) matches++;
  }
  return matches;
}

int same_contents_arr(int a[], int b[], int n) {
int i, x;

  for(i=0; i<n; i++) {
	x = a[i];
	if(num_occ(a, n, x) != num_occ(b, n, x))
		return 0;
  }
  return 1;
}
**/



int same_contents(List<int> *a, List<int> *target, int print) {
  int n, i;

  if(print) {
    printf("~        Expected Contents:  ");
    target->print();
    printf("~        Actual Contents  :  ");
    a->print();
  }

  n = a->length();
  if(n != target->length()) return 0;

  int aa[n];
  int t[n];
  for(i=0; i<n; i++){
    a->pop_front(aa[i]);
    target->pop_front(t[i]);
  }

  return same_contents_arr(aa, t, n);
}
  
  

List<int> * rem_all_hard_caseA(int nzeros) {
  int i;

  List<int> *lst =  new List<int>();

  for(i=0; i<nzeros; i++) {
    lst->push_front( 0);
  }
  for(i=0; i<nzeros; i++) {
    lst->push_front( 1);
  }
  return lst;
}

  
List<int> * rem_all_hard_caseB(int nzeros) {
  int i;

  List<int> *lst =  new List<int>();

  for(i=0; i<nzeros/2; i++) {
    lst->push_front( 0);
  }
  for(i=0; i<nzeros/2; i++) {
    lst->push_front( 1);
  }
  for(i=0; i<nzeros-(nzeros/2); i++) {
    lst->push_front( 0);
  }
  for(i=0; i<nzeros-(nzeros/2); i++) {
    lst->push_front( 1);
  }
  return lst;
}


/*
* expects list to contain only ones AND for
*  there to be exactly n of them.
* returns 0/1 accordingly
*
* Note:  empties the list
*/
int n_ones(List<int> *lst, int n) {
  int cnt=0;
  int x;

  while(!lst->is_empty()) {
    lst->pop_front(x);
    if(x != 1) return 0;
    cnt++;
  }
  return cnt==n;
}






#endif
