
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>

using std::vector;
using namespace std;

class GridWorld {

  private:
   /*----------------------------Data members for grid object----------------------------*/
    int gridRows;
    int gridCols;
    int totalPop;

    /*----------------------------Person struct for use in vector/DLL----------------------------*/
    struct Person{
      int pID;
      int pRow;
      int pCol;
      bool isAlive;
      Person *toDistrictList = nullptr;
      Person *next = nullptr;
      Person *previous = nullptr;       

    //Person constructor
      Person(int row, int col, int ID) {
        this->pRow = row;
        this->pCol = col;
        this->pID = ID;
      }   

      void setAlive() {
        this->isAlive = true;
      }
      void setDead() {
        this->isAlive = false;
        this->pRow = -1;
        this->pCol = -1;
      }

      void updateDistrict(int row, int col) {
        this->pRow = row;
        this->pCol = col;
      }

    };  
    /*----------------------------Double Linked List Template To Use----------------------------*/
    class doubleLinkedList {
      private:
        int numPeople = 0;
        Person *front = nullptr;
        Person *back = nullptr;

      public:
        //add to the end of the list
        void push_back(Person * &newP) {                
          if (front == nullptr && back == nullptr) {    //empty list
            front = newP;
            back = newP;
            numPeople++;
          }
          else {                                        //nonempty list
            newP->previous = back;
            this->back->next = newP;
            this->back = newP;
            numPeople++;
          }
        }

      //remove from the list
      void pop_out(Person * &leavingP) {               
        if (front == back && back == nullptr) {           //empty list
          return;
        }
        else if (front == back && back != nullptr) {    //one item list
          this->front = nullptr;
          this->back = nullptr;
          numPeople--;
          return;
        }
        else if (front == leavingP) { //if the person leaving is the front
          this->front = leavingP->next;
          leavingP->next = nullptr;
          numPeople--;
          return;
        }
        else {                                           //2+ item list
          Person *temp = leavingP->previous;
          leavingP->previous->next = leavingP->next;
          leavingP->next->previous = temp; 
          leavingP->next = nullptr;
          numPeople--;
        }
      }

      //return the end of the list node
      Person *endOfList() { 
        return this->back;
      }    

      Person *frontOfList() {
        return this->front;
      }

      void printList() {
        cout << "People in this district: ";
        Person *temp = front;
        while (temp != nullptr) {
          cout << temp->pID << " ";
          temp = temp->next;
        }
        cout << endl;
      }

      int districtPop() {
        return numPeople;
      } 

      void isListEmpty() {
        if (this->back == nullptr) {
        cout << "this list is empty\n";
        return;
        }
        cout << "this list is not empty\n";
      }

      void incPeople() {
        numPeople++;
        return;
      }

      void decPeople() {
        numPeople--;
        return;
      }
    };
    /*----------------------------Data members for grid object----------------------------*/
    doubleLinkedList **theGrid;

  public:
    /*----------------------------Vector for all the people birthed----------------------------*/
    vector<Person> personVector;
    /*----------------------------Double Linked List for the graveyard----------------------------*/
    doubleLinkedList *graveyard = new doubleLinkedList;   

    /*----------------------------Constructor for the Grid----------------------------*/  
    GridWorld(unsigned nrows, unsigned ncols)   {    
      this->gridRows = nrows;
      this->gridCols = ncols;

      //this generates a district DLL for each piece of the grid
      theGrid = new doubleLinkedList*[nrows];
      for (int i=0; i < ncols; i++) {
        theGrid[i] = new doubleLinkedList[ncols];
      }
    }
    /*----------------------------Destructor for the Grid----------------------------*/ 
    ~GridWorld(){
    }
    /*--------------------------------Class functions--------------------------------*/ 
    void printVector() {
      cout << "Here is everyone that is alive...\n";
      for (int i=0; i < personVector.size(); i++) {
        if (personVector[i].isAlive) {
          // cout << personVector[i].pID << endl;
          personInfo(personVector[i]);
        }
      }
      cout << "Here is everyone that is dead...\n";
      for (int i=0; i < personVector.size(); i++) {
        if (personVector[i].isAlive != true) {
          // cout << personVector[i].pID << endl;
          personInfo(personVector[i]);
        }
      }      
    }

    void printGraveyard() {
     graveyard->printList(); 
    }    

    void printDistrict(int row, int col) {
      theGrid[row][col].printList();
    }    

    void personInfo(Person thePerson) { //give info about a specific person
      cout << "The ID is: " << thePerson.pID << endl;
      cout << "The row is: " << thePerson.pRow << endl;
      cout << "The col is: " << thePerson.pCol << endl;
      if (thePerson.isAlive) {
        cout << "Alive\n\n";
      }
      else {
        cout << "Dead.\n\n";
      }
      if (thePerson.toDistrictList == nullptr ) {
        cout << "The person is not linked to a district.\n";
      }
    }       
    /*--------------------------------Prog02 functions--------------------------------*/ 
    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     * return:  indicates success/failure
     */   
    bool birth(int row, int col, int &id){
      //Use an ID from the graveyard if possible
      if (graveyard->endOfList() != nullptr && row < gridRows && col << gridCols) {
        graveyard->frontOfList()->setAlive();
        graveyard->frontOfList()->updateDistrict(row,col);

        int reviveID = graveyard->frontOfList()->pID;

        Person *newPerson = graveyard->frontOfList(); 
        theGrid[row][col].push_back(newPerson);   //add to the district DLL
        graveyard->pop_out(newPerson);            //remove from grave DLL

        personVector[reviveID].setAlive();
        personVector[reviveID].updateDistrict(row,col);   //update person vector
        totalPop++;
        return true;
      }

      //Create new ID if it is within the bounds of the grid
      if (row < gridRows && col << gridCols) {
        Person *newPerson = new Person(row, col, personVector.size());
        newPerson->setAlive();

        // add them to the correct district
        theGrid[row][col].push_back(newPerson);

        //connect the new person pointer to the district node
        newPerson->toDistrictList = theGrid[row][col].endOfList();

        //add the new person to the person vector
        personVector.push_back(*newPerson);

        totalPop++;
        return true;
      }
      return false;
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     * return:  indicates success/failure
     */
    bool death(int personID){
      if (personVector.empty()) {         //if the vector is empty, no one is alive
        return false;
      }
      if (personID > personVector.size() || personID < 0) { //if invalid input for id
        return false;
      }

      if (personVector[personID].isAlive) {
        int tempRow = personVector[personID].pRow;
        int tempCol = personVector[personID].pCol;

        //set the vector and pointer to dead
        personVector[personID].setDead();
        personVector[personID].toDistrictList->setDead();

        //push the person to the graveyard
        graveyard->push_back(personVector[personID].toDistrictList); 

        //remove the person from the list
        theGrid[tempRow][tempCol].pop_out(personVector[personID].toDistrictList);
        totalPop--;
        return true;
      }      
      return false;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{
      if (personVector.empty()) {         //if the vector is empty, no one is alive
        return false;
      }
      if (id > personVector.size() || id < 0) { //if invalid input for id
        return false;
      }
      if (personVector[id].isAlive) {         //if they're alive, update row and col
        cout << "District: " << personVector[id].pRow << " " << personVector[id].pCol << endl; //testing
        row = personVector[id].pRow;
        col = personVector[id].pCol;
        return true;
      }
      return false;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){
      if (id < personVector.size()) {
        if (personVector[id].isAlive && targetRow < gridRows && targetCol < gridCols) {
          int tempRow = personVector[id].pRow;
          int tempCol = personVector[id].pCol;

          //don't do anything if moving the end person of a list to the same list
          if (theGrid[targetRow][targetCol].endOfList()->pID == id) { 
            return false;
          }

          //move out of curr district
          theGrid[tempRow][tempCol].pop_out(personVector[id].toDistrictList);
          
          //move to new district
          theGrid[targetRow][targetCol].push_back(personVector[id].toDistrictList); 

          personVector[id].toDistrictList->updateDistrict(targetRow,targetCol); //update node
          personVector[id].updateDistrict(targetRow,targetCol); //update vector      
          return true;
        }
      }
      return false;
    }
   
/*------------------------------------------------------------------------------------------------*/ 
    std::vector<int> * members(int row, int col)const{
      vector<int> *districtList = new vector<int>;

      if (row < gridRows && col < gridCols) {
        Person *temp = theGrid[row][col].frontOfList();
        for (int z=0; z < theGrid[row][col].districtPop(); z++) {
          districtList->push_back(temp->pID); 
          temp = temp->next;
        }
      }
      return districtList;
    }

   void printMembersVector(vector<int> *members) {
      vector<int> temp = *members;
      cout << "Members of this district are: ";
      for (int i =0; i < members->size(); i++) {
        cout << temp[i] << " ";
      }
      cout << endl;
    } 
    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return totalPop;
    }    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      if (row > gridRows || col > gridCols) {
        return 0;
      }
      return theGrid[row][col].districtPop(); 
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return gridRows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return gridCols;
    }



};

#endif
