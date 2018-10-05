#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>



using namespace std;


/**
* TODO: implement merge-sort using the "primitives"
*    provided by the List class.
*/

template <typename T> 
void msort(List<T> *lst) {

  // BASE CASE
  if (lst->length() == 0 || lst->length() == 1) {
    return;
  }

  // SPLIT INTO TWO LISTS
  int split = (lst->length())/2;
  List<T> *firstList = lst->prefix(split);
  List<T> *secondList = lst->prefix(lst->length());

  // RECURSIVELY SORT FIRST LIST
    msort(firstList);
  // RECURSIVELY SORT SECOND LIST
    msort(secondList); 
  // MERGE THEM INTO A SINGLE SORTED LIST
  //    make sure it is stored in *lst!	
  //    cleanum any mess you made (temporary lists?, etc.)
    firstList->merge_with(*secondList);
    lst->merge_with(*firstList);
    delete firstList;
    delete secondList;
}



int main(int argc, char *argv[]){
  List<string> *words = new List<string>;
  string s;
  // cout << " hello\n";
  // read strings to sort from standard input
  while(cin >> s ) {
    words->push_back(s);
  }
  cout << "BEFORE SORTING:\n";
  words->print();

  msort(words);
  cout << "AFTER SORTING:\n";
  words->print();

  delete words;

  return 0;
}
