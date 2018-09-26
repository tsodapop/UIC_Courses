#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

/**
 * class List<T>
 * 
 * General description:  class for storing and manipulating sequences of items 
 *    where item type is specified via template.
 * 
 * Underlying organization:  the implementation uses a singly-linked list data structure
 *    with pointers to both the front (first node) and back (last node) of the list.
 * 
 *    A private struct Node is used to represent individual nodes in a list.
 */


template <typename T>
class List
{
private:
  // struct for singly-linked list nodes
  struct Node
  {
    T data;
    Node *next;

    Node(const T &d = T{}, Node *n = nullptr)
        : data{d}, next{n} {}
  };

  /* Data members of List class:  a front and back pointer */
  Node *front;
  Node *back;
  int numNodes = 0;


    void recursivePrint_Rev(Node* node) const {
    if (node == nullptr) { //when it hits the end of the recursive call, or if the list is empty
      return;
    }
      recursivePrint_Rev(node->next); //recursive call
      cout << node->data << " "; //printout
    return;
  }

public:
  // constructor
  List() {
    front = nullptr;
    back = nullptr;
  }

  // destructor
  ~List() {
    clear();
  }
  /**
     * Disclaimer:  C++ conventions tell us that we should have a couple
     * of additional constructors here (a copy constructor, assignment operator
     * etc.)
     *
     * However, to keep things simple for now we will ignore that convention
     * (since the exposure to C++ is pretty variable it seems -- some students
     * having taken 141 before last semester; some students coming from 107,
     * etc.)
     */

  /**
     * function: clear
     * desc:  makes the calling list empty (but the list still
     *        exists).
     */
  void clear()
  {
    Node *p = front;
    Node *pnext;

    while (p != nullptr)
    {
      pnext = p->next;
      delete p;
      numNodes--;
      p = pnext;
    }
    front = back = nullptr;
  }

  /**
     * TODO
     *
     * function: length
     * desc:  returns the length of the calling list
     *        
     * REQUIREMENTS:  this is a working implementation, but
     *   it takes linear time.
     *
     *   Your job (todo):  make modifications so that this
     *     operation becomes constant time (O(1)).
     *
     *   This task is different from most others in that most of
     *       the "real" work you do to make this work
     *	in O(1) time will be in _other_ functions which affect
     *	the length of lists.
     *
     *	HINT:  you are free to add data members to the List class...
     *	       maybe for "bookkeeping"??
     */
  int length() const
  {
    // Node *p = front;
    // int n = 0;

    // while (p != nullptr)
    // {
    //   n++;
    //   p = p->next;
    // }

    // return n;

    return numNodes;
  }

public:
  /**
    * function: is_empty
    * desc:   Returntrue if the list is empty, false otherwise.
    */
  bool is_empty() const
  {
    return front == nullptr;
  }

  /**
    * function: print
    * desc:  self-evident:  simply prints the elements/values of the list in order.
    */
  void print() const
  {
    Node *p = front;

    std::cout << "[ ";
    while (p != nullptr)
    {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << "]\n";
  }

  /**
    * function: push_front
    * desc:  adds a new element to the front of the list (calling object) containing val.
    *        Equivalently, you can think of this as an "prepend" operation.
    */
  void push_front(const T &data)
  {
    numNodes++;

    front = new Node(data, front);

    if (back == nullptr)
      back = front;
  }

  /**
    * function: pop_front
    * desc:  if the list (calling object) is non-empty, the first element (front of list)
    *        is removed and the value it stored is 'passed back' to the caller via the reference
    *        parameter val.  In this case (non-empty list), true is returned for success.
    * 
    *        Otherwise (the list is empty), false is returned and the reference parameter val has
    *        no meaning.
    */
  bool pop_front(T &val)
  {
    Node *tmp;

    if (front == nullptr)
      return false;
    val = front->data;


    numNodes--;    
    tmp = front;
    front = front->next;
    delete tmp;
    if (front == nullptr)
      back = nullptr;
    return true;
  }

  /**
    * function: push_back
    * desc:  adds a new element to the end of the list (calling object) containing val.
    *        Equivalently, you can think of this as an "append" operation.
    */
  void push_back(const T &val)
  {
    numNodes++;

    Node *tmp = new Node(val, nullptr);

    if (front == nullptr)
    {
      front = back = tmp;
    }
    else
    {
      back->next = tmp;
      back = tmp;
    }
  }

  /**
    * function: remove_first
    * desc:  removes first occurrence of x (if any) in given list (calling object).
    *        if a match is found (and removed), true is returned.
    *        Otherwise (no match found), false is returned and the list is unchanged.
    */
  bool remove_first(const T &x)
  {

    Node *p, *tmp;
    T dummy;

    if (front == nullptr)
      return false;
    if (front->data == x)
    {
      pop_front(dummy);
      numNodes--;
      return true;
    }
    p = front;
    while (p->next != nullptr)
    {
      if (x == p->next->data)
      {
        numNodes--;
        tmp = p->next;
        p->next = tmp->next;
        if (tmp == back)
          back = p;
        delete tmp;
        return true;
      }
      p = p->next;
    }
    return false;
  }

  /**
    * function: slow_remove_all
    * desc:  removes all occurrences of x (if any) in given list (calling object).
    *        returns number of matches found/deleted.  Relative order of undeleted elements
    *        is unchanged.
    * 
    * approach:  repeatedly calls remove_first until it fails.
    * 
    * Note:  function is designated with the slow_ prefix because, in the worst case, it can
    *        take quadratic time.
    */
  int slow_remove_all(const T &x)
  {
    int n = 0;

    while (remove_first(x))
      n++;
    return n;
  }

  /**
    * function: is_sorted
    * desc:  returns true if elements in list are in sorted order from
    *        smallest to largest (duplicates allowed); returns false otherwise.
    *
    * Note:  requires that type T has the > operator defined on it (perhaps via
    *        operator overloading as in the case of the string class)
    */
  bool is_sorted() const
  {
    Node *p = front;

    while (p != nullptr && p->next != nullptr)
    {
      if (p->data > p->next->data)
        return false;
      p = p->next;
    }
    return true;
  }

  /** TODO
     *    function:  count
     *     description:  Counts number of occurrences 
     *     		of x in the list and returns that count.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
  int count(const T &x) const
  {
    int occurrences = 0;
    Node *head = front;

    //
    while (head != nullptr) {
      if (head->data == x) {
      occurrences += 1;
      }
      head = head->next; 
    }
    return occurrences;
  }

  /* TODO 
     *    
     *  function:  pop_back
     *
     *  if list is empty, we do nothing and return false 
     *  otherwise, the last element in the list is removed, its
     *      value (data field) is assigned to the reference parameter 
     *      data (so the removed element can be 'passed-back' to the
     *      caller) and true is returned.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     * 
     */
  bool pop_back(T &data)
  {
    Node *p = front;
    Node *end;
    //this is the case if the list is empty
    if (p == nullptr) {
      return false;
    }
    //this is the 1 item list case
    if (p->next == nullptr) {
      end = p;
      front = back = nullptr;
      data = end->data;
      delete end;
      numNodes--;
      return true;
    }
    //this is for the 2+ case
    while(p->next != back) {
      p = p->next; //p will end up as the second to last value after this while loop
    }
    //the following code will run only after the while loop and if it is a 2+ item list
    end = p->next;
    p->next = nullptr;
    back = p;
    data = end->data;
    numNodes--;
    delete end;
    return true;
  }

  /**   
     * TODO:  
     *   function:  equal_to 
     *   description:  returns true if calling List and parameter 
     *      List other contain exactly the same sequence of values.
     *      Returns false otherwise.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is MIN(len1,len2)
     *    and len1 and len2 are the respective lengths of the two lists.
     **/
  bool equal_to(const List<T> &other) const
  {
    Node *p = this->front;
    Node *pOther = other.front;

    //if they do not have the same number of items, they are not equal to 
    if (this->numNodes != other.numNodes) {
      return false;
    }
    //run through the rest of the list and check if their data matches
    while (p != nullptr) {
      if (p->data != pOther->data) {
        return false;
      }
      p = p->next;
      pOther = pOther->next;
    }
    return true; 
  }

  /**
     * TODO:  print in reverse order 
     *
     * Try to do without looking at notes!
     * Hints:  recursive helper function
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */

  void print_rev() const
  {
    recursivePrint_Rev(front);
  }

  /* TODO
     *  For full credit, you cannot allocate any new memory!
     *
     *  description:  self-evident 
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
  void reverse()
  {
    if (this->back == nullptr) { //if it is an empty list
      return;
    }
    if (front == back) { //if it is a one item list
      return;
    }

    Node *temp = front;
    Node *forwardTraverse = front->next;
    Node *backTraverse = front->next;

    front->next = nullptr;
    front = back;
    back = temp;
    back->next = nullptr;

    while(forwardTraverse != front) {
      forwardTraverse = forwardTraverse->next;
      backTraverse->next = temp;
      temp = backTraverse;
      backTraverse = forwardTraverse;
    }
    if (forwardTraverse == front) {
      forwardTraverse->next = temp;
    }
  }

  /** TODO
     *   function:  fast_remove_all
     *   description:  same behavior/semantics as
     *      slow_remove_all.  However, this function
     *      must guarantee linear time worst case 
     *      runtime (hence, "fast").
     *
     *   REQUIREMENT:  linear worst-case runtime.
     *
     *   Note:  your solution may be either recursive or 
     *   iteratieve.
     **/
  int fast_remove_all(const T &x)
  {
    Node *p = front;
    Node *traverseList = front;
    Node *lagNode = front;
    // int dummy;
    int numDeletes = 0;

    if (back == nullptr) { //if list is empty, nothing to remove
      return numDeletes;
    }
    while(p != nullptr) {
      traverseList = traverseList->next;    
      if (p->data == x) {
        if (front == p) {
          lagNode = front;
          front = traverseList;
        }
        if (back == p) {
          back = lagNode;
        }
        lagNode->next = traverseList;
        delete p;
        numNodes--;
        numDeletes++;
        }
      else {
        lagNode = p;
      }
        p = traverseList;
    }
    return numDeletes;
  }

  /** TODO
     * function:  insert_sorted
     *
     * description:  assumes given list is already in sorted order from
     *     smallest to largest and inserts x into the appropriate position
     * 	   retaining sorted-ness.
     * Note 1:  duplicates are allowed.
     *
     * Note 2:  assume sorted list input in
     *
     * REQUIREMENTS:
     *   O(n) runtime
     */
  void insert_sorted(const T &x)
  {
    Node *p = front;
    Node *insertNode = new Node(x,nullptr);

    if (front == nullptr) { //empty list returns without operation
      front = insertNode;
      insertNode->next = nullptr;  
      numNodes++;
      return; 
    }

    while (p->data <= insertNode->data) {
      if (p->next == nullptr) { //p is the last item on the list and insertNode->data is largest
        p->next = back = insertNode;
        numNodes++;
        return;
      }
      if (p->next != nullptr) { //p is not the last item, so we perform a check on the next item
        if (p->next->data > insertNode->data) { //if the next item is greater, we insert in between
          insertNode->next = p->next;
          p->next = insertNode;
          numNodes++;
          return;
        }
        else {  //the next one is not greater than insertNode->data, so check the next item
          p = p->next;
        }
      }
    }
    //these lines will only run if the there is a list and the first item > insertNode->data
    insertNode->next = front;
    front = insertNode;
    numNodes++;
    return;
  }

  /** TODO
     * function:  merge_with
     *
     * description:  assumes both list a and b are in
     * 	sorted (non-descending) order and merges them
     * 	into a single sorted list with the same
     * 	elements.  
     *
     * 	This single sorted list is stored in a while
     * 	b becomes empty.
     *
     * 	if either of given lists are not sorted, 
     * 	we blame the caller and the behavior is
     * 	implementation dependent -- i.e., don't worry
     * 	about it!
     *
     *      Condition in which both parameters are the same
     *      list (not merely "equal"), the function simply 
     *      does nothing and returns.  This can be tested
     *      with simple pointer comparison.
     *
     * 	Example:
     *
     * 		a:  [2 3 4 9 10 30]
     * 		b:  [5 8 8 11 20 40]
     *
     * 		after call a.merge_with(b):
     *
     * 		  a:  [2 3 4 5 8 8 9 10 11 20 30 40]
     * 		  b:  []
     * 
     *
     * REQUIREMENTS:
     *
     * 	Runtime Must be linear in the length of the 
     * 	resulting merged list (or using variables above, 
     * 	O(a.length()+b.length()).
     *
     *  should not allocate ANY new list
     * 	nodes -- it should just re-link existing
     * 	nodes.
     */
  // void merge_with(List<T> &other)
  // {
  //   Node *traverseMainList = this->front;
  //   Node *traverseOtherList = other.front;

  //   if (this == &other) //this is a check on if it runs onto itself. if yes, do nothing
  //   {
  //     std::cerr << "warning:  List::merge_with():  calling object same as parameter";
  //     std::cerr << "\n          list unchanged\n";
  //     return;
  //   }

  //   //if list a is empty, bring everything from b to a
  //   if (this->back == nullptr) {
  //     this->front = other.front;
  //     this->back = other.back;
  //     other.front = nullptr;
  //     other.front = nullptr;
  //     this->numNodes = other.numNodes;
  //     return;
  //   }
  //   //if list b is empty, no action required
  //   if (other.back == nullptr) {
  //     cout << "The second list is empty. No action taken.\n";
  //     return;
  //   }

  //   while (traverseOtherList != nullptr) {
  //     //if a <= b, run the following code
  //     if (traverseMainList->data <= traverseOtherList->data) {
  //     //if main has nothing left in list, remainder of b are all greater so append to a
  //       if (traverseMainList->next == nullptr) {
  //         traverseMainList->next = traverseOtherList;
  //         numNodes = numNodes + other.numNodes;
  //         this->back = other.back;
  //         other.front = nullptr;
  //         other.back = nullptr;
  //         return;
  //       }
  //       else if (traverseMainList->next->data >= traverseOtherList->data) {
  //         other.front = traverseOtherList->next;
  //         traverseOtherList->next = traverseMainList->next;
  //         traverseMainList->next = traverseOtherList;
  //         traverseMainList = traverseMainList->next;
  //         traverseOtherList = other.front;
  //         other.numNodes--;
  //         numNodes++;
  //       }
  //       else {
  //         traverseMainList = traverseMainList->next;
  //       }
  //     }
  //     //if a > b, run the following code
  //     else if (traverseMainList->data > traverseOtherList->data) {
  //       if (traverseMainList == this->front) { //if this is the beginning,update front
  //         this->front = traverseOtherList;
  //       }
  //         other.front = traverseOtherList->next;
  //         traverseOtherList->next = traverseMainList;
  //         traverseMainList = traverseOtherList;
  //         traverseOtherList = other.front;
  //         numNodes++;
  //         other.numNodes--;
  //     }      
  //   }
  //   other.front = nullptr;
  //   other.back = nullptr;
  //   return;
  // }

  void merge_with(List<T> &other)
{
Node *p; //first line Node *q; //secondline Node *tempMerge = other.front; //sorting Node *new_head = nullptr;
if (p == nullptr) return q; if (q == nullptr) return p; if (p && q) {
if(p->data <= q-> data) {
tempMerge = p; p->data= tempMerge->next; } else
{
tempMerge = q; q = tempMerge->next; } new_head = tempMerge; } while (p && q) {
if(p->data <= q->data) {
tempMerge->next = p ; tempMerge = p; p = tempMerge ->next; } else
{
tempMerge->next = q; tempMerge = q; q=tempMerge->next; } } if (p == nullptr) {
tempMerge->next = q; } if (q == nullptr) {
tempMerge->next = p; } return new_head; }


  /**
     * TODO
     * function:  clone
     *
     * description:  makes a "deep copy" of the given list a
     *   and returns it (as a List pointer).
     *
     * NOTE:  this functionality would normally be folded into
     *  a "copy constructor"
     *
     */
  List<T> *clone() const
  {
    Node *p = this->front;
    List<T> *newList = new List<T>(); //newList is a List pointer that points to new List<T>
    
    while (p != nullptr) {
      newList->push_back(p->data);
      // newList->numNodes++;
      p = p->next;
    }
    //ned to also add newlist's front and back

    return newList;
  }

  /**
     * TODO
     * function:  prefix
     *
     * description:  removes the first k elements from the
     *               calling list which are used to form a new list
     *		            which is then returned.
     *
     *		if n is the length of the given list, we have the
     *		following boundary conditions:
     *
     *		  if k==0:
     *			    calling list unchanged and an empty list returned
     *		  if k>=n:
     *			    calling becomes empty and a list containing
     *			    all elements previously in lst is returned.
     *
     *		examples:
     *
     *		  EX1:  lst:  [2, 3, 9, 7, 8]
     *			k:    3
     *
     *			call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [7, 8]
     *			   returned list (prefix):  [2, 3, 9]
     *
     *		  EX2  lst:  [2, 3, 9, 7, 8]
     *			k:    0
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [2, 3, 9, 7, 8]  (unchanged)
     *			   returned list:  []
     *
     *		  EX3  lst:  [2, 3, 9, 7, 8]
     *			k:    5
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(5);
     *
     *			after call:
     *			   lst:  []
     *			   returned list:  [2, 3, 9, 7, 8]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) worst case where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned prefix should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be 
     *                  allocated or deallocated; you should just 
     *                  "re-use" the existing nodes.  HOWEVER, you will
     *		               need to allocate a List object for the returned
     *		               prefix (but, again, the underlying Nodes should be
     *		               re-used from the calling list).
     */
  List<T> *prefix(unsigned int k)
  {
    List<T> *prefixList = new List<T>;
    Node *traverseMainList = this->front;

    if (this->back == nullptr) { //if the list is empty, do nothing
      cout << "This list is currently empty. No action taken.\n";
      return prefixList;
    }

    for (int i=0; i<k; i++) { 
      if (this->front == nullptr) { //once the list is empty, if you call for more k, it will just finish
        this->back = nullptr;
        return prefixList;
      }
      this->front = front->next;
      traverseMainList->next = nullptr;
      
      if (prefixList->back == nullptr) { //if the prefix list is currently empty, update the front and back
        prefixList->front = traverseMainList;
        prefixList->back = traverseMainList;
        prefixList->numNodes++;   
        this->numNodes--;     
      }
      else { 
        prefixList->back->next = traverseMainList;
        prefixList->back = prefixList->back->next;
        prefixList->numNodes++;
        this->numNodes--;
      }
      traverseMainList = this->front;
    }
    return prefixList;
  }

  /**
     * TODO
     * function:  filter_leq
     *
     * description:  removes all elements of the given list (lst) which
     *		are less than or equal to a given value (cutoff)
     *		
     *		A list containing the removed elements is returned.
     *
     * examples:
     *
     *	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
     *		cutoff:  4
     *
     *		after call:
     *			lst:  [9, 8, 12, 7]
     *			returned list:  [4, 2, 4, 3]
     *
     *       -----------------------------------------
     *	EX2: 	lst:  [6, 5, 2, 1]
     *		cutoff:  6
     *
     *		after call:
     *			lst:  []
     *	 		returned list:  [6, 5, 2, 1]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned list should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
     *		   you should just "re-use" the existing nodes.  HOWEVER, you will
     *		   need to allocate a LIST structure itself (i.e., for the returned
     *		   list).
     *			
     */
  List<T> *filter_leq(const T &cutoff)
  {
    List<T> *newList = new List<T>;
    Node *traverseMainList = this->front;
    Node *p = this->front;
    Node *lagNode = this->front;
    Node *traverseNewList = newList->front;

    if (this->back == nullptr) { //nothing in the list to filter out
      return newList;
    }

    
    while(p != nullptr) {   
      traverseMainList = traverseMainList->next;
      if (p->data <= cutoff) {
        if (p == front) {
          this->front = traverseMainList;
          lagNode = front;
          //update p into new list
          if (newList->back == nullptr) {
            newList->front = newList->back = p;
            p->next = nullptr;
            newList->numNodes++;
            this->numNodes--;
          }
          else {
            newList->back->next = p;
            newList->back = p;
            p->next = nullptr;
            newList->numNodes++;
            this->numNodes--;
          }

          p = traverseMainList;
        }
        else {
          lagNode->next = traverseMainList;
          //update p into new list
          if (newList->back == nullptr) {
            newList->front = newList->back = p;
            p->next = nullptr;
            newList->numNodes++;
            this->numNodes--;
          }          
          else {
            newList->back->next = p;
            newList->back = p;
            p->next = nullptr;
            newList->numNodes++;
            this->numNodes--;
          }          

          p = traverseMainList;
        }
      }
      else {
        if (lagNode == p) {
          p = p->next;
        }
        else {
          p = p->next;
          lagNode = lagNode->next;
        }
      }
    }

    return newList;
  }

  /**
     * TODO
     * function:  concat
     *
     * description:  concatenates the calling list with parameter list (other)
     *    The resulting concatenation is reflected the calling list; the 
     *    parameter list (other) becomes empty.
     *
     *    example:
     *
     *	EX1:  a: [2, 9, 1]
     *	      b: [5, 1, 2]
     *
     *	      call:  
     *	            a.concat(b);
     *
     *	after call:
     *
     *		a: [2, 9, 1, 5, 1, 2]
     *		b: []
     *
     * REQUIREMENTS:  
     *
     *     runtime:  O(1)
     *
     *			List<int> *my_list = new List<int>();;
     *
     *			my_list->push_front(my_lst, 4);
     *			my_list->push_front(my_lst, 2);
     *
     *			my_lst->concat(my_lst);
     *
     *		your implementation must detect if it is being
     *		called this way.  If so the function does nothing
     *		and (optionally) prints an error message to
     *		stderr.
     *	
     */
  void concat(List<T> &other)
  {

    if (this == &other) //this is a check on if it runs onto itself. if yes, do nothing
    {
      std::cerr << "warning:  List::concat():  calling object same as parameter";
      std::cerr << "\n          list unchanged\n";
      return;
    }
    // if the first list is empty, run this
    if (this->back == nullptr) {
      this->front = other.front;
      this->back = other.back;
      other.front = nullptr;
      other.back = nullptr;
      this->numNodes = other.numNodes;
      other.numNodes = 0;
    }
    else if (other.back == nullptr) { //if second list is empty, do nothing
      return;
    }
    else { //the list has at least 1 item and the second list is not empty
      this->back->next = other.front;
      this->back = other.back;
      other.front = nullptr;
      other.back = nullptr;
      this->numNodes = numNodes + other.numNodes;
      other.numNodes = 0;
    }
    return;
  }

  /**
     * TODO
     *
     * function:  compare_with
     * description: compares the calling list with parameter list (other)
     *    "LEXICALLY" (essentially a generalization of dictionary
     *    ordering).
     *
     *    link:  https://en.wikipedia.org/wiki/Lexicographical_order
     *
     *    Return Value:
     *
     *       o if the two lists are identical, 0 is returned.
     *       o if the calling list is lexically BEFORE the other list,
     *             -1 is returned
     *       o otherwise, the other list is lexically before the calling
     *             list and 1 (positive one) is returned.
     *
     *    Properties and examples:
     *
     *        The empty list is lexically before all non-empty lists
     *          (you can say it is "less than" all non-empty lists).
     *
     *        Examples (using mathematical notation):
     *
     *          [2 5 1] < [3 1 1 1 1]    (think dictionary ordering!)
     *
     *          [4 1 3] < [4 1 3 0 0 0]  (prefix: just like "car" is before
     *                                            "cartoon" in the dictionary).
     * 
     *          [4 5 6 1 2 3 9 9 9] < [4 5 6 1 4 0 0] 
     *                   ^                     ^
     *                      (they have a common prefix of length 4; but at
     *                      the fifth position they differ and the left list
     *                      is the winner (smaller) -- no need to look further)
     *
     *                      
     *        Templates?
     *
     *          Since List is a template class, the elements of a particular
     *          list need not be integers.  For example, we could have
     *          lists of strings.
     *
     *          Good news:  the exact same principle applies because 
     *          strings can be compared just like integers can be compared!
     *
     *          Great news:  you don't need to think about this at all!
     *          The exact same code you would write if you assumed the element
     *          type is integer will work for other types like strings.
     *
     *          Why?  Because, for example, all of these operators:
     *
     *                   <, <=, ==, > and >= 
     *
     *          all work on strings.  They are not 'built-in' to C++, but
     *          the class string has "overloaded" these operators (they 
     *          result in an appropriate function call).
     *
     *          (In a subsequent exercise, we will do this kind of 
     *          overloading ourselves!)
     *                                     
     *        Examples with lists of strings:
     *
     *          ["egg", "goat"] < ["egg", "globe", "apple"]
     *
     *          ["zebra", "fun"] < ["zebra", "funny"]
     *
     *        [Yes, the components of these lists are THEMSELVES compared
     *        lexically, but the string class is doing those comparisons)
     *
     */
  int compare_with(const List<T> &other) const
  {
    Node *p = this->front;
    Node *pOther = other.front;
    // if(this->numNodes == other.numNodes) { //need to cehck who is longer a different way
      while (p != nullptr && pOther != nullptr) { //while both lists have not reached an end
        if (p->data == pOther->data) { //if list a = list b nodes, try the next one
          p = p->next;
          pOther = pOther->next;
        }
        else if (p->data > pOther->data) { //if list a is before list b
          return 1;
        }
        else if (p->data < pOther->data) {  //if list b is before list a
          return -1;
        }
      }
      //this will run after one of the lists reaches their end. then, it's just a matter of which one has more
      if (this->numNodes < other.numNodes) {
        return -1;
      }
      else if (this->numNodes > other.numNodes) {
        return 1;
      }

      return 0;
  }

  /*
     * TODO
     *
     * function:  suffix_maxes
     *
     * desc:  constructs a new list of the same length as the calling object
     *        with the value stored at position i of the new list is the MAXIMUM
     *        value in the suffix (or tail) of the calling list starting from
     *        position i.
     *
     *        This new list is returned and the calling list is unchanged.
     *
     *        Example:
     *
     *          Given List:  [6, -18, 12, 4, 1, 7, 2, 5  4]
     *                                    ^^^^^^^^^^^^^^^^
     *
     *          New list:    [12, 12, 12, 7, 7, 7, 5, 5, 4]
     *                                    ^
     *
     *              (as a sub-example, the marked entry in the new list
     *              (marked with '^') is the max of the marked suffix in the
     *              given list (marked with a bunch of '^'s).
     *
     * REQUIREMENTS:
     *
     *        Total Runtime:   O(n)
     *        Calling list is unchanged.
     *
     */
  void suffixMax(Node *p, Node *backEnd) const {
    int nextNode = 0;
  
    if (p == backEnd) {
      return;
    }
    else {
      suffixMax(p->next, backEnd); 
      nextNode = p->next->data;
      if (p->data < nextNode) {
        p->data = nextNode;
      }
    }
    return;
  }

  List<T> *suffix_maxes() const
  {
    List<T> *newList = this->clone();
    suffixMax(newList->front, newList->back);
    return newList;
  }

  int returnNumNodes() {
    return numNodes;
  }

  /**
   * func:  checksum
   * desc:  Performs and XOR of all node pointers and returns result as
   *        an unsigned int.
   * 
   * NOTES: YOU MAY NOT TOUCH OR MODIFY THIS FUNCTION!!
   */
  unsigned long int checksum()
  {
    unsigned long int s = 0;
    Node *p = front;

    while (p != nullptr)
    {
      s = s ^ ((unsigned long int)p);
      p = p->next;
    }
    return s;
  }

};

#endif