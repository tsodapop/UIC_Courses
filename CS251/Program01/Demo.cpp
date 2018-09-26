#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>

using namespace std;

List<int> * slow_list(int n) {

  // placeholder
  return nullptr;
}

int main(int argc, char *argv[]){
  List<string> *list2 = new List<string>();
  List<int> *list = new List<int>();
  List<string> *list3 = new List<string>();
  List<double> *list4 = new List<double>();
  int x;
  int n, ndel;
  int testInt;
  string testString;
  double testDouble;
  List<int> *list5 = new List<int>();
  List<int> *list6 = new List<int>();
  List<int> *list7 = new List<int>();
  List<int> *list8 = new List<int>();

  n = 1000;

  if(argc == 2) {
    n = atoi(argv[1]);
  }

  string words[] = {"alice", "bob", "cathy", "donald"};
  for(int i=0; i<4; i++) {
      list2->push_front(words[i]);
      list3->push_back(words[i]);
  }

  list4->push_front(3.1415);

  // for(x=1; x<=4; x++) {
  //   list->push_front(x);
  // }
  // list->print();

  for(x=1; x<=8; x++) {
    list->push_back(x);
  }

  for(x=1; x<=4; x++) {
    list5->push_back(x);
  }

  list->print();

  for (x=1; x<=20; x++) {
    list6->push_front(1);
  }
  // for (x=1; x<=100; x++) {
  //   list6->push_front(x);
  // }

 for(x=1; x<=8; x++) {
    list8->push_back(x);
  }


   /*______________________________________________LENGTH TEST______________________________________________*/
  // cout << endl << "This will return the length of the list\n";
  // cout << "List length: " << list->length() << endl << endl;
  // list->print();
  // cout << "List2 length: " << list2->length() << endl << endl;
  /*______________________________________________ LENGTH TEST_________________________ _____________________*/
  
/*______________________________________________ COUNT TEST______________________________________________*/
  // cout << "This is the beginning of testing count function.\n";
  // cout << list2->count("donald") << endl;
  // cout << "This is the end of testing for testing count function.\n";
  /*______________________________________________ COUNT TEST______________________________________________*/


  // list->pop_front(x);
  // cout << "popped " << x <<endl;
  // list->print();

  // list->slow_remove_all(2);
  // cout << "after remove-all(2):\n";
  // list->print();

   /*______________________________________________LENGTH TEST______________________________________________*/
  // cout << endl << "This will return the length of the list\n";
  // cout << "List length: " << list->length() << endl << endl;
  // list->print();
  // cout << "List2 length: " << list2->length() << endl << endl;
  /*______________________________________________ LENGTH TEST_________________________ _____________________*/

  // string words[] = {"hello", "goodbye", "sunrise", "sunset"};

  list2->print();
  list3->print();


  // cout << "list  sorted?  " << list->is_sorted() << endl;
  // cout << "list2 sorted?  " << list2->is_sorted() << endl;
  // cout << "list3 sorted?  " << list3->is_sorted() << endl;

  /*______________________________________________ CONCAT TEST______________________________________________*/
  // cout << "This is testing the concat function\n";
  // // list2->concat(*list3);
  // // list2->print();
  // // list3->print();
  // // cout << list2->returnNumNodes() << endl;
  // // cout << list3->returnNumNodes() << endl;
  // // cout << "hello\n";
  // list->concat(*list6);
  // list6->concat(*list);

  // list->print();
  // list6->print();
  // cout << list->returnNumNodes() << endl;
  // cout << list6->returnNumNodes() << endl;
  /*______________________________________________ CONCAT TEST______________________________________________*/

  /*_________________________________________ insert_sorted TEST_________________________ _____________________*/
  // cout << "\nThis will test the insert_sorted function\n";
  // List<int> *testList = new List<int>;

  // testList->insert_sorted(9);
  // testList->insert_sorted(11);
  // testList->insert_sorted(22);
  // testList->insert_sorted(9);
  // testList->insert_sorted(0);
  // testList->insert_sorted(0);
  // testList->insert_sorted(22);
  // testList->insert_sorted(0);
  // testList->print();

  // "test inserting [9, 11, 22, 9, 0, 0, 22, 0] 1-by-1",
  /*_________________________________________ insert_sorted TEST_________________________ _____________________*/

  /*_________________________________________ suffix_max TEST_________________________ _____________________*/
  // list7->push_back(6);
  // list7->push_back(-18);
  // list7->push_back(12);
  // list7->push_back(4);
  // list7->push_back(1);
  // list7->push_back(7);
  // list7->push_back(2);
  // list7->push_back(5);
  // list7->push_back(4);

  // cout << "\ntesting suffix_max\n\n";
  // cout << "Original List: "; 
  // list7->print();
  // List<int> *suffixList = list7->suffix_maxes();
  // cout << "New List: ";
  // suffixList->print();
  /*_________________________________________ suffix_max TEST_________________________ _____________________*/


  // list2->front = NULL;
  
  unsigned long int s1, s2, s3, s4;

  // cout << "\nlist: ";
  // list->print();
  // cout << "\nlist2: ";
  // list2->print();
  // cout << "\nlist3: ";
  // list3->print();
  // cout << "\nlist4: ";
  // list4->print();
/*______________________________________________ COUNT TEST______________________________________________*/
  // cout << "This is the beginning of testing count function.\n";
  // cout << list2->count("donald") << endl;
  // cout << "This is the end of testing for testing count function.\n";
/*______________________________________________ COUNT TEST______________________________________________*/

 /*___________________________________________ POP_BACK TEST_________________________ _____________________*/
  // cout << endl << "This will test the pop_back function for the list\n";
  // list->print();
  // list->pop_back(testInt);
  // cout << list3->pop_back(testString) << endl;
  // cout << testInt << endl;
 /*___________________________________________ POP_BACK TEST_________________________ _____________________*/

 /*___________________________________________ PRINT_REV TEST_________________________ _____________________*/
  // cout << endl << "This will test reverse printing the list\n";
  // list3->print();
  // cout << endl;
  // list3->print_rev();
  // cout << endl;
 /*___________________________________________ PRINT_REV TEST_________________________ _____________________*/
  

  int dummy;
  // list->pop_front(dummy);

  /*___________________________________________ CLONE TEST_________________________ _____________________*/
  // cout << "\nClone test function\n";
  // cout << "Original list: \n";
  // list->print();
  // cout << "A cloned list is now being created... \n";
  // List<int> *newList = list->clone();

  // list->pop_back(dummy);
  // cout << "Original list updated: \n";
  // list->print();
  // cout << "Cloned list: \n";
  // newList->print();
  /*___________________________________________ CLONE TEST_________________________ _____________________*/


/*___________________________________________ EQUAL_TO TEST_________________________ _____________________*/
  // cout << endl << "This will tell if the second list is equal to the list\n";
  // cout << list2->equal_to(*list2) << endl;
/*___________________________________________ EQUAL_TO TEST_________________________ _____________________*/

/*___________________________________________ MERGE_W TEST_________________________ _____________________*/
cout << "Testing the merge_with function\n";
list->print();
list5->print();
cout << "Merging in progress...\n";
list->merge_with(*list5);
list->print();
list5->print();
// cout << list->length() << endl;
/*___________________________________________ MERGE_W TEST_________________________ _____________________*/

/*___________________________________________ PREFIX TEST_________________________ _____________________*/
// cout << "\ntesting prefix function\n"; //run some more tests on prefix
// // list->print();
// List<int> *testList = new List<int>;
// for (int i=1; i<=5; i++) {
//   testList->push_back(i);
// }
// testList->print();

// List<int> *testList2 = new List<int>;
// testList2 = testList->prefix(6);

// testList->print();
// // cout << testList->returnNumNodes() << endl;
// // cout << list->back->dat

// testList2->print();
// // cout << testList2->returnNumNodes() << endl;
// // list->print();
/*___________________________________________ PREFIX TEST_________________________ _____________________*/

// /*___________________________________________ LEQ TEST_________________________ _____________________*/
// cout <<"\ntesting leq\n\n";
// list7->print();
// // list7->filter_leq(4);
// List<int> *leqList = list7->filter_leq(4);
// list7->print();
// leqList->print();
// /*___________________________________________ LEQ TEST_________________________ _____________________*/

/*___________________________________________ REVERSE TEST_________________________ _____________________*/
// cout << "testing reverse.\n\n";
// list2->print();
// list2->reverse();
// list2->print();
/*___________________________________________ REVERSE TEST_________________________ _____________________*/

/*_________________________________________ compare_with TEST_________________________ _____________________*/
// cout << "\ntesting compare with\n\n";
// list->print();
// // list8->print();
// list8->push_back(8);
// list8->print();
// //show list 6 and then try to do last ite m ocmpare
// //need to account for if lists are empty
// int j = list->compare_with(*list8);
// cout << j << endl;
/*_________________________________________ compare_with TEST_________________________ _____________________*/

/*___________________________________________ FAST_REMOVE TEST_________________________ _____________________*/
// cout << "Testing fast_remove\n";
// list6->print();
// list6->fast_remove_all(1);
// cout << "fast_remove complete\n";
// list6->print();

// list->print();
// list->fast_remove_all(7);
// list->print();

/*___________________________________________ FAST_REMOVE TEST_________________________ _____________________*/
  

  list->clear();
  list2->clear();
  list3->clear();
  list4->clear();

  delete list;
  delete list2;
  delete list3;
  delete list4;
  /***  UNCOMMENT THIS CODE ONCE YOU HAVE WRITTEN YOUR
   *     slow_list FUNCTION
   *
   *    THIS WILL BE YOUR LAB EXERCISE FOR WEEK-03

  list = slow_list(n);

  cout << "starting slow_remove_all (n=" << n << ")" << endl;
  ndel = list->slow_remove_all(0);
  cout << "slow_remove_all done!" << endl;
  cout << "    num-deleted:    " << ndel << endl;
  cout << "    list-len after: " << list->length()   << endl;

  delete list;

  **************************************/

  return 0;
}
