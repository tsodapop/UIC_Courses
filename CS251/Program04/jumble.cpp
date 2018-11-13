#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {

unordered_map <string, vector<string> > dictionary; //generation of dict map
ifstream file;                                  //the file to open
string dictStr;
string keyStr;
string inputStr;
int numWords = 0;
int numClasses = 0;
int longestLen = 0;
string longestLenKey;

 if(argc != 2) {        //if you don't input a file, throw error message
    cout << "Incorrect way to use this program...\n";
    cout << "For proper use, run as follows: ./freq <filename>\n";
    return 1;
  }

file.open(argv[1], ios::in);

//if the file can be used, notify. else, notify they need to use new file.
if(!file.is_open()) {
    cout << "The file could not be opened...please try with a different file.\n";
    return 1;
}
else {
    cout << endl << "Reading file: " << argv[1] << "...complete!" << endl;
}

//inserting all the words into the map via key/value pairings
while (file >> dictStr) { //while there is still something to be read from the file
    numWords++;         //incr for the number of words in dictionary
    keyStr = dictStr;     //set key to dictionary value and then sort it
    sort(keyStr.begin(), keyStr.end());

    if (dictionary[keyStr].size() == 0) {   //incr for the number of distinct keys
        numClasses++;
    }

    dictionary[keyStr].push_back(dictStr); //push into the dictionary

    if (dictionary[keyStr].size() > longestLen) { //update the longest length key 
        longestLen = dictionary[keyStr].size();
        longestLenKey = keyStr;
    }
}

cout << "\nEnter a string of characters.\n";
cout << "I'll let you know if I can find any anagrams in my dictionary!\n";
cout << "Alternatively, use control-d to terminate the program.\n\n";

//intake user input and return on string
while (cin >> inputStr) {
    sort(inputStr.begin(), inputStr.end());
    if (dictionary[inputStr].size() == 0) { //if there is nothing in the dictionary
        cout << "There are no words available with this string of characters.\n\n";
    }

    else {  //it is in the dictionary, so return the anagrams
        cout << "The following anagrams I can find in my dictionary are...\n\n";
        for (int i=0; i < dictionary[inputStr].size(); i++ ){
            cout << dictionary[inputStr][i] << endl;
        }
    }
}

//the user wants to end the program. send a final report of the dictionary
cout << "\nBefore you go, here is a report for this dictionary!\n\n";
cout << "--------------------REPORT:--------------------\n\n";
cout << "num words: " << numWords << endl;
cout << "num classes: " << numClasses << endl;
cout << "size-of-largest-class: " << longestLen << endl;
cout << "largest-class key: " << longestLenKey << endl;
cout << "members of largest-class: \n\n";

for (int i =0; i < dictionary[longestLenKey].size(); i++) {
    cout << dictionary[longestLenKey][i] << endl;
}
cout << "-----------------END OF REPORT:-----------------\n\n";

cout << endl;
    return 0;
}