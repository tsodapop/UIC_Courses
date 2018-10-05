#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>

// using namespace std;

template <typename T>
class List
{
  private:    

    // struct for singly-linked list nodes
    struct Node
    {
      T      data;
      Node   *next;

      Node( const T & d = T{}, Node * n = nullptr)
        : data{ d },  next{ n } { }

    };


  public:
    // constructors
    List( ) { 
      init( );
    }

    ~List( ) {
      clear( );
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
    void clear(){
      Node * p = front;
      Node *pnext;

      while(p != nullptr) {
        pnext = p->next;
        delete p;
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
    int length( ) const {
      return n;
    }


  public:

    // Return true if the list is empty, false otherwise.
    bool is_empty( ) const {
      return front == nullptr;
    }


    void print() const {
      Node *p = front;

      std::cout << "[ "; 
      while(p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
      }
      std::cout << "]\n";
    }

    void push_front(const T & data) {
      front = new Node(data, front);

      if(back == nullptr)
        back = front;
      n++;
    }

    bool pop_front(T &val) {
      Node *tmp;

      if(front==nullptr)
        return false;
      val = front->data;

      tmp = front;
      front = front->next;
      delete tmp;
      if(front==nullptr)
        back = nullptr;
      n--;
      return true;
    }

    void push_back(const T & val) {
      Node *tmp = new Node(val, nullptr);
      int dummy;

      if(front == nullptr) {
        front = back = tmp;
      }
      else {
        back->next = tmp;
        back = tmp;
      }
      n++;
    }

    bool remove_first(const T &x) {
      Node *p, *tmp;
      T dummy;

      if(front==nullptr) return false;
      if(front->data == x) {
        pop_front(dummy);
        return true;
      }
      p = front;
      while(p->next != nullptr) {
        if(x == p->next->data) {
          tmp = p->next;
          p->next = tmp->next;
          if(tmp == back)
            back = p;
          delete tmp;
          n--;
          return true;
        }
        p = p->next;
      }
      return false;
    }

    int slow_remove_all(const T &x) {
      int ndel=0;

      while(remove_first(x))
        ndel++;
      return ndel;
    }

    bool is_sorted() const {
      Node *p = front;

      while(p!=nullptr && p->next != nullptr) {
        if(p->data > p->next->data)
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
    int count(const T &x) const {
      return _count(front, x); 
    }

  private:
    static int _count(const Node *p, const T &x) {
      if(p==nullptr) return 0;
      return (p->data == x) + _count(p->next,x);
    }
  public:


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
    bool pop_back(T &data) {
      if(front == nullptr)
        return false;
      if(front==back)
        return pop_front(data);

      Node *newback = front;
      while(newback->next != back)
        newback = newback->next;

      data = back->data;
      delete back;
      back = newback;
      back->next = nullptr;
      n--;
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
    bool equal_to(const List<T> &other) const {
      Node *p1, *p2;

      p1 = front;
      p2 = other.front;

      while(p1 != nullptr && p2 != nullptr) {
        if(p1->data != p2->data) return false;
        p1 = p1->next;
        p2 = p2->next;
      }
      // if we get here, everthing matched so far.  We just
      //   need to figure out if we have "exhausted" both lists
      //   or if one is a prefex of the other.
      //
      // NOTE:  at least one of p1, p2 must be null after loop.
      //   this if-statement checks if they are BOTH null.
      //   (or equivalently if the two lists are of the
      //   same length).
      if(p1==p2)
        return true;
      else  // one must be a prefix of the other
        return false;  

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
    void print_rev() const {
      std::cout << " [ ";
      _p_rev(front);
      std::cout << " ] " << std::endl;
    }

  private: 
    static void _p_rev(Node *p) {
      if(p == nullptr)
        return;
      _p_rev(p->next);
      std::cout << p->data << " ";
    }

  public:


    /* TODO
     *  For full credit, you cannot allocate any new memory!
     *
     *  description:  self-evident 
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
    void reverse() {
      Node *p;  // "previous"
      Node *c;  // "current"
      Node *nxt;  // "next"
      Node *tmp;

      if(n < 2) return;

      // at least 2 nodes

      p = front;
      c = p->next;

      p->next = nullptr;  // new last element

      while(c != nullptr) {
        nxt = c->next;
        c->next = p;  // Key line here!
        p = c;
        c = nxt;
      }

      tmp = front;
      front = back;
      back = tmp;
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
    int fast_remove_all(const T &x) {
      // return slow_remove_all(x);
      Node *p, *nxt, *nxt_nxt;
      int cnt;

      cnt = 0;
      p = front;

      // get rid of all x's at front (if any)
      while(p != nullptr && p->data == x) {
        cnt++;
        nxt = p->next;
        delete p;
        p = nxt;
      }

      // NOW:  p == nullptr or p->val != x
      front = p;
      while(p->next != nullptr) {

        if(p->next->data == x) {
          cnt++;
          nxt_nxt = p->next->next;
          delete p->next;
          p->next = nxt_nxt;
          // NOTE that we don't advance p in this case
        }
        else {
          p = p->next;
        }
      }
      back = p;
      n -= cnt;
      return cnt;
    }

    /** TODO
     * function:  insert_sorted
     *
     * description:  assumes given list is already in sorted order from
     *     smallest to largest and inserts x into the appropriate position
     * 	   retaining sorted-ness.
     * Note 1:  duplicates are allowed.
     *
     * Note 2:  if given list not sorted, behavior is undefined/implementation
     * 		dependent.  We blame the caller.
     * 		So... you don't need to check ahead of time if it is sorted.
     *
     *
     * REQUIREMENTS:
     *
     *   O(n) runtime
     */
    void insert_sorted(const T &x) {
      Node *px, *p;

      p = front;
      if(p == nullptr || x <= p->data) 
        push_front( x);
      else {
        // walk p til x belongs right after p
        while(p->next != nullptr && p->next->data < x) {
          p = p->next;
        }
        px = new Node(x, p->next);

        p->next = px;
        if(px->next == nullptr)
          back = px;
        n++;
      }

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
    void merge_with(List<T> &other){
Node *m;

  m = merge_rec(this->front, other.front);

  this->front = m;

  if(other.back != nullptr && other.back->next == nullptr)
  this->back = other.back;
  // else: original back of a also back of merged list

  this->n += other.n;
  other.n = 0;
  other.front = nullptr;
  other.back = nullptr;
	
}
private:

static Node * merge_rec(Node *a, Node *b) {

  if(a==nullptr)
    return b;
  if(b==nullptr)
    return a;

  if(a->data< b->data) {
    a->next = merge_rec(a->next, b);
    return a;
  }
  else {
    b->next = merge_rec(a, b->next);
    return b;
  }
}

public:

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
    List<T> * clone() const {
      List<T> *cpy = new List<T>();
      Node *p, *last;

      p  = front;

      if(p==nullptr) return cpy;

      cpy->front = new Node(p->data, nullptr);
      last = cpy->front;
      p = p->next;
      while(p != nullptr) {
        last->next = new Node(p->data, nullptr);
        last = last->next;
        p = p->next;
      }
      cpy->back = last;
      cpy->n = n;
      return cpy;
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
    List<T> * prefix(unsigned int k) {
      List<T> *lhs; // stores the prefix to return
      Node *p;
      int i;

      lhs = new List<T>();

      if(k == 0)
        return lhs;

      if(k >= n) {
        *lhs = *this;
        this->front = nullptr;
        this->back = nullptr;
        this->n = 0;
      }
      else {  // 1 <= k < n)
        lhs->front = this->front;
        p = this->front;
        i = 1;
        while(i < k) {
          p = p->next;
          i++;
        }
        // now p points to the kth node:
        //    - last node in prefix
        //    - successor is first node in suffix
        lhs->back = p;
        this->front = p->next;
        this->n -= k;
        lhs->n = k;
        p->next = nullptr;
      }
      return lhs;
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
    List<T> * filter_leqREC(const T & cutoff) {
      List<T> *leq = new List<T>();

      leq->front = filter_leq_rec(&(front), cutoff);

      leq->set_size();
      this->set_size();
      leq->set_back();
      this->set_back();

      return leq;
    }

    List<T> * filter_leq(const T & cutoff) {
      List<T> *leq = new List<T>();
      Node *p = front;

      this->front = nullptr;
      this->back= nullptr;
      this->n = 0;

      while(p != nullptr) {
        Node *nxt = p->next;  // save tail
        if(p->data <= cutoff) 
          leq->pback_node(p);
        else
          this->pback_node(p);
        p = nxt;
      }
      return leq;
    }



  private:

  // pushback operation where node already exists!
  //   local/private helper (outside world doesn't know about
  //   Nodes)
  void pback_node(Node *p) {
    n++;
    p->next = nullptr;
    if(front==nullptr) {
      front = p;
      back = p;
    }
    else {
      back->next = p;
      back = p;
    }
  }

    static Node * filter_leq_rec(Node **pp, T cutoff){
      Node *leq, *tail,*p;

      p = *pp;
      if(p == nullptr) 
        return nullptr;

      tail = p->next;
      leq = filter_leq_rec(&tail, cutoff);
      if(p->data <= cutoff) {
        p->next = leq;
        *pp = tail;
        return p;
      }
      else {
        (*pp)->next = tail;
        return leq;
      }
    }

  public:

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
     *     sanity:  this operation makes sense when a and b
     *		are distinct lists.  For example, we don't
     *		want/allow the caller to do something like
     *		this:
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
    void concat(List<T> &other) {

      if(this == &other) {
        std::cerr << "warning:  List::concat():  calling object same as parameter";
        std::cerr << "\n          list unchanged\n";
        return;
      }
      // std::cout << "List::concat(): no error...\n";

      if(other.front == nullptr) return;

      if(front == nullptr){
        front = other.front;
        back = other.back;
        n = other.n;
        other.init();
        return;
      }
      back->next = other.front;
      back = other.back;
      n += other.n;

      other.init();  
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
    int compare_with(const List<T> &other) const {

      return _cmp(front, other.front);

    }

  private:
    static int _cmp(Node *a, Node *b) {
      if(a==b) return 0;  // works if they are both null or if they
      //   are really the same lists in memory.

      // we know that a != b if we get here
      //    -- e.g., we cannot have both a and be equal to nullptr
      if(a==nullptr)
        return -1;
      if(b==nullptr)
        return 1;

        // if we get here, both are non-null
      if(a->data < b->data) return -1;
      if(b->data < a->data) return 1;
      // else they must match at this position
      return _cmp(a->next, b->next);
    }

  public:

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
    List<T> * suffix_maxes() const{
      List<T> *sm = new List<T>();

      sm->front = _suffix_maxes(front, sm->back);
      sm->n = n;
      return sm;
    }

  private:

    static Node * _suffix_maxes(Node *p, Node *&b) {
      Node *tail;

      if(p==nullptr) {
        b = nullptr;
        return nullptr;
      }
      if(p->next == nullptr) {
        b = new Node(p->data, nullptr);
        return b;
      }
      tail = _suffix_maxes(p->next, b);

      return  new Node(p->data > tail->data ? p->data : tail->data, tail);
    }



  private:
    Node *front;
    Node *back;
    int  n;

    void init( ) {
      front = nullptr;
      back = nullptr;
      n = 0;
    }
    void set_back() {
      Node *p;

      p = front;

      while(p != nullptr && p->next != nullptr) {
        p = p->next;
      }
      back = p;
    }

    void set_size() {
      Node *p;

      n = 0;
      p = front;
      while(p != nullptr) {
        n++;
        p = p->next;
      }
    }
};

#endif
