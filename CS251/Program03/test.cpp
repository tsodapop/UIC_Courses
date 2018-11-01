#include <iostream>
#include "bst.h"


int main(){
    int x;
    int nleaves;
    int h;

    bst<int> *t = new bst<int>();

    // while( (std::cin >> x)) 
        // t->insert(x);

    // if(t->size() <= 20) {
    //   t->inorder();
	//     t->preorder();
	//     t->postorder();
    // }
    // _________________________ to_vector _________________________
    x = 4;
    t->insert(x);
    x = 2;
    t->insert(x);
    x = 1;
    t->insert(x);
    x = 3;
    t->insert(x);
    x = 5;
    t->insert(x);
    x = 8;
    t->insert(x);
    // cout << "Testing to_vector\n";
    vector<int> *newVec = t->to_vector();
    t->printVector(newVec);
    cout << endl;
    // _________________________ to_vector _________________________

    // _________________________ get_ith _________________________
    // t->get_ith_SLOW(9, x);
    // cout << x << endl;
    // t->printNodeVal();
    t->get_ith(1,x);
    cout << "the ith value is: " << x << endl;
    // _________________________ get_ith _________________________



    // h = t->height();
    // std::cout << "\n#### Reported height of tree:   " << h << "\n";

    // nleaves = t->num_leaves();
    // std::cout << "\n#### Reported number of leaves:   " << nleaves  << "\n";

    // delete t;
    
    return 0;
}
