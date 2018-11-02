#include <iostream>
#include "bst.h"


int main(){
    int x;
    int nleaves;
    int h;
    int success = 5;
    int target;
    int n = 1023;

    bst<int> *t = new bst<int>();

    // while( (std::cin >> x)) 
//         // t->insert(x);
// int n4 = n/4;
//   int n2 = n/2;
//   int lo = n2-n4;
//   int hi = n2+n4;        
    for ( int i =1; i <= 1000; i++) {
        t->insert(i);
    }
//     for ( int i=n2; i <= n2+n4; i++ ) {
//         t->remove(i);
//     }
//     for ( int i=n2-1; i >= n2-n4; i-- ) {
//         t->remove(i);
//     }
// int n4 = n/4;
//   int n2 = n/2;
//   int lo = n2-n4;
//   int hi = n2+n4;

//  int new_n = n - (hi-lo+1);
//   target = new_n;
//   cout << t->size() << endl;
//   cout << target << endl;
// cout <<target << endl;
//   for(int i=1; i<lo; i++, target--) {
//     x = t->num_geq( i);
//     if(x != target){
//       cout << "THIS BREAKS HERE AT: " << x << endl;
//       success = 0;
//     }
//   }
// cout << hi-lo+1 << endl;
// int v = 0;
// cout << t->size() << endl;
// v = t->num_geq( 1);
// cout << v << endl;
// cout << target - 0<< endl;
//   if(t->num_geq( n+2) != 0)
//       success = 0;
// //   bst_free(t);
//   return success;

// int k = t->num_leq(2);
// cout << k << endl;

      
    // int j = t->num_geq(-2);
    // cout << j << endl;
    // cout << success << endl;
    // _________________________ to_vector _________________________
    // cout << "Testing to_vector\n";
    vector<int> *newVec = t->to_vector(); cout << "Vector of BST: "; t->printVector(newVec);
    // cout << endl; t->printNodeVal()
    t->printSize();;
    // t->preorder();

    // _________________________ to_vector _________________________

    // _________________________ get_ith _________________________
    // cout << "Testing get_ith\n";
    // t->get_ith(6,x);
    // cout << "the ith value is: " << x << endl;
    // _________________________ get_ith _________________________

    // _________________________ size_bal _________________________
    // cout << "TESTING SIZE BAL\n";
    // t->printSize();
    // vector<int> *newVec = t->to_vector(); cout << "Vector of BST: "; t->printVector(newVec);
    // _________________________ size_bal _________________________
    // if(t->size() <= 20) {
    //   t->inorder();
	    // t->preorder();
    // }


    // h = t->height();
    // std::cout << "\n#### Reported height of tree:   " << h << "\n";

    // nleaves = t->num_leaves();
    // std::cout << "\n#### Reported number of leaves:   " << nleaves  << "\n";

    // delete t;
    
    return 0;
}
