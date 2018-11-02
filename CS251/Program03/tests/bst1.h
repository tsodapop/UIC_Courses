#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      bst_node *left;
      bst_node *right;
      int lSize = 0;
      int numNodes = 0;

      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr)
        : val { _val },  left { l }, right {r} 
      { }
    };


 

  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:

/************************************************************
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 * returns:   pointer to root of tree after insertion.
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success, bst_node *rootNode){
      if(r == nullptr){
        success = true;
        bst_node *newNode = new bst_node(x, nullptr, nullptr);
        return newNode;
      }

      if(r->val == x){
        success = false;
        return r;
      }

      if(x < r->val){
        r->left = _insert(r->left, x, success, r);
        if (success) { //add num nodes below +1 if successful
          r->numNodes++;
          r->lSize++;
        }
        if (!sizeBalanced(r)) {
          // cout << "Size balancing issue on insert of " << x << " for node " << r->val << endl;
          vector<T> *sizeBalVector = to_vector(r); 
          // printVector(sizeBalVector); cout << endl;
          r = correctNodesForBal(sizeBalVector, r); //remove nodes
        } 
        return r;
      } 

      else {
        r->right = _insert(r->right, x, success, r);
        if (success) { //add num nodes below +1 if successful
          r->numNodes++;
        }
        if (!sizeBalanced(r)) {
          // cout << "Size balancing issue on insert of " << x << " for node " << r->val << endl;
          vector<T> *sizeBalVector = to_vector(r); 
          // printVector(sizeBalVector); cout << endl;
          r = correctNodesForBal(sizeBalVector, r); //remove nodes
        }         
        return r;
      }
    }

  //removes the values stored in the vector from the bst
  static bst_node* correctNodesForBal(vector<T> *sizeBalVector, bst_node* r) {
    vector<T> newVec = *sizeBalVector;
    vector<T> test;
    bool success;
    int high = sizeBalVector->size();
    int low = 0;

    for (int i =0; i < high; i++) {
      r = _removeBal(r, newVec[i], success, r);
    }
    r = _from_vec(newVec, low, high-1); 

    return r;
  }  

  public:
  void printNodeVal() {
    _printNodeVal(root);
  }

  void _printNodeVal(bst_node *root) {
    bst_node* node = root;

    if (node == nullptr) { //if null
      return;
    }
    if (node->left != nullptr) { //if there is a left side
      _printNodeVal(node->left);
    }
    cout << "Node val: " << node->val << " left tree size: " << node->lSize << " " <<
            "nodes below: " << node->numNodes << endl;
    if (node->right != nullptr) { //if there is a right side
      _printNodeVal(node->right);
    }
  }
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   * note:      helper function does most of the work.
   */
   bool insert(T & x){
      bool success;
      bst_node *rootNode = root;
      root = _insert(root, x, success, rootNode); 
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }
/****************************************************************/
    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node * _remove(bst_node *r, T & x, bool &success, bst_node * rootNode){
      bst_node *tmp;
      bool sanity;

      if(r==nullptr){
        success = false;
        return nullptr;
      }
      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
          return tmp;
        }
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
          return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->right = _remove(r->right, r->val, sanity, rootNode);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        return r;
      }
      if(x < r->val){
        r->left = _remove(r->left, x, success, rootNode);
        if (success) {
          r->numNodes--;
          r->lSize--;
        }
        if (!sizeBalanced(r)) {
          // cout << "Size balancing issue on insert of " << x << " for node " << r->val << endl;
          vector<T> *sizeBalVector = to_vector(r); 
          // printVector(sizeBalVector); cout << endl;
          r = correctNodesForBal(sizeBalVector, r); //remove nodes
        }         
      }
      else {
        r->right = _remove(r->right, x, success, rootNode);
        if (success) {
          r->numNodes--;
        }
        if (!sizeBalanced(r)) {
          // cout << "Size balancing issue on insert of " << x << " for node " << r->val << endl;
          vector<T> *sizeBalVector = to_vector(r); 
          // printVector(sizeBalVector); cout << endl;
          r = correctNodesForBal(sizeBalVector, r); //remove nodes
        }            
      }
      return r;
    }

static bst_node * _removeBal(bst_node *r, T & x, bool &success, bst_node * rootNode){
      bst_node *tmp;
      bool sanity;

      if(r==nullptr){
        success = false;
        return nullptr;
      }
      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
          return tmp;
        }
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
          return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->right = _removeBal(r->right, r->val, sanity, rootNode);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        return r;
      }
      if(x < r->val){
        r->left = _removeBal(r->left, x, success, rootNode);
        if (success) {
          // r->numNodes--;
          // r->lSize--;
        }          
      }
      else {
        r->right = _removeBal(r->right, x, success, rootNode);
        if (success) {
          // r->numNodes--;
        }            
      }
      return r;

    }

  public:
/********************************************************************/
    bool remove(T & x){
      bool success;
      bst_node *rootNode = root;
      root = _remove(root, x, success, rootNode);
      return success;
    }



  private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      return _size(root);
    }

    void printSize() {
      cout << "Root: " << root->val << endl;
      cout << "Size of tree: " << _size(root) << endl;
      cout << "Size of left: " << _size(root->left) << endl;
      cout << "Size of right: " << _size(root->right) << endl;
    }

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/

    // TODO

  private: 
    //helper function for to_vector
    static void insToVec(bst_node *r, vector<T> *vector) {
      // cout << r->val << endl;
      if(r == nullptr) {  //if null, return
        return;
      }

      if (r->left != nullptr) { //run through all left sides
        insToVec(r->left, vector);
      }

      vector->push_back(r->val);  //this puts it in-order for the vector

      if (r->right != nullptr) {  //run through all the right sides
        insToVec(r->right, vector);
      }

      return;
    }  

  public:
//puts the values of a bst into a vector in-order
    vector<T> * to_vector() {
      vector<T> *toVector = new vector<T>;  //creates new vector pointer to vector
      // cout << "hi\n";
      insToVec(root, toVector); //inserts into the vector with helper function

      return toVector;
    }

    static vector<T> * to_vector(bst_node *node) {
      vector<T> *toVector = new vector<T>;  //creates new vector pointer to vector

      insToVec(node, toVector); //inserts into the vector with helper function

      return toVector;
    }

    // print out a vector
    static void printVector(vector<T> *pvector) {
      vector<T> temp = *pvector;

      for (int i=0; i < temp.size(); i++) {
        cout << temp[i] << " ";
      }
    }


    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    //helper recursive funciton for get ith
    bool _get_ith(int i, T &x, bst_node *root) {
      int testVal = root->lSize+1;
      if (i == testVal) {
        x = root->val;
        return true;
      }
      if (i < testVal) {
        _get_ith(i, x, root->left);
        return true;
      }
      else {
        _get_ith((i-testVal), x, root->right);;
        return true;
      }
    }

    //get ith function
    bool get_ith(int i, T &x) {
      if (i < 1 || i > size()) {
        return false;
      }
      _get_ith(i, x, root);
      return true;   // placeholder
    }


    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }


    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
    int num_geq(const T & x) {
      int rootNodes = root->numNodes+1;
      int geq =  _num_geq(root,x, rootNodes);

      // if (x > root->size()) { return 0;}
      // if (x < 1) { return size();}
      return geq;
    }
    //helper function
    static int _num_geq(bst_node *r,const T&x, int rootNodes) {
      int num = 0;
      if (r == nullptr) {
        return 0;
      }

      if (r->val == x) {
          num = _num_geq(r->right, x,rootNodes) + _num_geq(r->left, x, rootNodes) + 1; 
        return num;
      }

      if (r->val > x) {
        // cout << "left!!\n";
        num = _num_geq(r->left, x,rootNodes);
        int j = (r->numNodes - r->lSize)+1;
        num = num + j;
        return num;
      }

      if (r->val < x) {
        // cout << "right!!\n";
        num = _num_geq(r->right, x,rootNodes);
        return num;
      }
      return num;
    }

    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *
     */
    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }
    

    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_leq(const T &x) {
      return 0;  // placeholder
    }

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_range(const T & min, const T & max) {
      return 0;
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *
     */
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:


    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }

    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }

  private:
    bool static sizeBalanced(bst_node *root) {
      if (root == nullptr) {
        return true;
      }
      // int size1 = _size(root->left);
      // int size2 = _size(root->right);
      int size1 = 0;
      int size2 = 0;
      
      if (root->left != nullptr) {
          size1 = root->lSize;
      }
      if (root->right != nullptr) {
          size2 = root->numNodes - root->lSize;
      }
      // cout << size1 << " " << size2 << endl;
      int min;
      int max;

      //setting up which side, left or right, has more nodes
      if (size1 >= size2) {
        max = size1;
        min = size2;
      }
      else {
        max = size2;
        min = size1;
      }
      // cout << "min: " << min << " " << "max: " << max << endl;
      if ((min*2)+1 >= max) {
        // cout << "Size Balance Is Okay.\n";
        return true;
      }
      if ((min*2)+1 < max) {
        // cout << min << " " << max << endl;
        // cout << "Size Balance Error on node: " << root->val << endl;
        return false;
      }
      return true;
    }



  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }

    /* 
     * TODO:
     * Complete the (recursive) helper function for the post-order traversal.
     * Remember: the indentation needs to be proportional to the height of the node!
     */
    static void _postorder(bst_node *r, int margin){

      std::cout << "\n   WARNING:  POSTORDER UNIMPLEMENTED...\n";
    }

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

    // indentation is proportional to depth of node being printed
    //   depth is #hops from root.
    void postorder() {

      std::cout << "\n======== BEGIN POSTORDER ============\n";
      _postorder(root, 0);
      std::cout << "\n========  END POSTORDER  ============\n";

    }

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * bst_from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
      int m;
      bst_node *root;

      if(hi < low) {
        return nullptr;
      }
      m = (low+hi)/2;
      root = new bst_node(a[m]);
      // cout << "value: " << root->val << endl;
      root->left  = _from_vec(a, low, m-1); 
      root->right = _from_vec(a, m+1, hi);

      if (root->left != nullptr) {
        root->lSize = _size(root->left);
        root->numNodes = _size(root)-1;
      }
      if (root->right != nullptr) {
        root->numNodes = _size(root)-1;
      }      
      return root;

    }

  public:
    static bst * from_sorted_vec(const std::vector<T> &a, int n){

      bst * t = new bst();
      t->root = _from_vec(a, 0, n-1);
      return t;
    }

    // TODO:  num_leaves
    //   Hint:  feel free to write a helper function!!
    int num_leaves() {

      std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
      return 0;
    }

    // TODO:  num_at_level
    // description:  returns the number of nodes at specified level
    //   in tree.
    // note:  the root is at level 0.
    // Hint:  recursive helper function?
    int num_at_level(int level) {

      std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
      return 0;
    }


  private:
    bst_node *root;


}; // end class bst

#endif
