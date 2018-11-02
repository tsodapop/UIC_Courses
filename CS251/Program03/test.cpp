#include <iostream>
#include "bst.h"


int main(){
    int x;
    int nleaves;
    int h;

    bst<int> *t = new bst<int>();

    // while( (std::cin >> x)) 
        // t->insert(x);
    for ( int i =1; i <= 6; i++) {
        t->insert(i);
    }
    x = 2;
    t->remove(x);
    x = 1;
    t->remove(x);
    // x = 5; t->remove(x);

    // if(t->size() <= 20) {
    //   t->inorder();
	    // t->preorder();
    // }
    // _________________________ to_vector _________________________
    // cout << "Testing to_vector\n";
    vector<int> *newVec = t->to_vector(); cout << "Vector of BST: "; t->printVector(newVec);
    // cout << endl; t->printNodeVal();
    // t->preorder();
    cout << endl;
    // _________________________ to_vector _________________________

    // _________________________ get_ith _________________________
    // cout << "Testing get_ith\n";
    // t->get_ith(1,x);
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
