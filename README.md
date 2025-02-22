# Project-2-
Description: In this project, you will implement a generalized list data structure using an array. A
generalized list can be used to represent a tree data structure. Consider the following tree and the
corresponding generalized list.


You will implement the following classes along with the methods mentioned each of the classes – You can
add other helper methods as you deem useful:
template <class DT>
class GLRow; //class prototype
template <class DT>
ostream& operator <<(ostream& s, GLRow<DT>& oneGLRow);
class GLRow {
friend ostream& operator<< <DT>(ostream& s, GLRow<DT>& oneGLRow);
Protected:
DT* _Info;
int _Next;
int _Down;
Public:
GLRow ();
GLRow (DT& newInfo);
GLRow (GLRow<DT>& anotherOne);
GLRow<DT>& operator= (GLRow<DT>& anotherOne); //Make sure you do
//a deep copy
int getNext();
int getDown();
DT& getInfo();
int setNext(int n);
int setDown(int d);
int setInfo (DT& x);
~GLRow(); //destructor
};
template <class DT>
class ArrayGLL; //class prototype
template <class DT>
ostream& operator <<(ostream& s, ArrayGLL<DT>& oneGLL);
class ArrayGLL {
friend ostream& operator<< <DT>(ostream& s, ArrayGLL<DT>& OneGLL);
Protected:
GLRow<DT>* myGLL;
int maxSize; //Maximum size of the array of GLRows
int firstElement;
int firstFree;
Public:
ArrayGLL ();
ArrayGLL (int size);
ArrayGLL (ArrayGLL<DT>& anotherOne);
ArrayGLL<DT>& operator= (ArrayGLL<DT>& anotherOne);
void display (); //display in parenthesis format 10% BONUS
int find (DT& key); //return the index position where you find
//the element key; -1 if not found; use recursive search
void findDisplayPath (DT& Key); // as you travel through the tree
//print the values of nodes encountered. If the element is
//you will print the all the values
int noFree (); //return the number of free locations; you need
//to follow the _Next and get the free locations
int size (); //return the number of elements stored
int parentPos(DT& Key); // provide the location of the parent of
//the element Key in the array 10% BONUS
GLRow<DT>& operator [] (int pos); //return the GLRow that is in
//in the position pos in the array
int getFirstFree();
int getFirstElement();
void setFirstFree (int pos);
void setFirstElement (int pos);
~ArrayGLL (); //destructor
};
Your main program will have the following structure (changes may be required).
#include <iostream>
using namespace std;
int main() {
ArrayGLL<int> firstGLL(20);
int noElements, firstFree, firstElement;
int value, next, down, parentPos;
int pos = -1;
int keyValue;
// Read the number of elements
cout << "Enter number of elements: ";
cin >> noElements >> firstFree >> firstElement;
// Input validation and initialization of GLRows
for (int i = 0; i < noElements; i++) {
cin >> value >> next >> down;
// Dynamically create a new GLRow<int> for each entry
GLRow<int> newRow(value);
newRow.setNext(next);
newRow.setDown(down);
firstGLL[i] = newRow; // Ensure deep copy is handled correctly
}
// Setting up the structure
firstGLL.setFirstFree(firstFree);
firstGLL.setFirstElement(firstElement);
cout << "\n=== First GLL Structure ===\n";
firstGLL.display();
// Testing copy constructor
ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);
if (!secondGLL) {
cerr << "Error: Memory allocation failed for secondGLL." << endl;
return 1;
}
(*secondGLL)[1].setInfo(600);
(*secondGLL)[2].setInfo(700);
cout << "\n=== Second GLL (After Modifications) ===\n";
(*secondGLL).display();
// Testing find function
keyValue = 700;
pos = (*secondGLL).find(keyValue);
if (pos != -1) {
cout << "Element " << keyValue << " found at position: " << pos << endl;
cout << "Element details: " << (*secondGLL)[pos] << endl;
(*secondGLL).findDisplayPath(keyValue);
} else {
cout << "Element " << keyValue << " not found." << endl;
}
// Testing parentPos function
parentPos = (*secondGLL).parentPos(keyValue);
if (parentPos != -1) {
cout << "Parent of " << keyValue << " is at position: " << parentPos << endl;
cout << "Parent details: " << (*secondGLL)[parentPos] << endl;
} else {
cout << "Parent of " << keyValue << " not found." << endl;
}
// Testing size and free locations
cout << "\nSize of secondGLL: " << (*secondGLL).size() << endl;
cout << "Number of free locations: " << (*secondGLL).noFree() << endl;
// Test getFirstElement and getFirstFree
cout << "\nFirst element position: " << firstGLL.getFirstElement() << endl;
cout << "First free position: " << firstGLL.getFirstFree() << endl;
// Test setFirstElement and setFirstFree
firstGLL.setFirstElement(2);
firstGLL.setFirstFree(5);
cout << "Updated first element position: " << firstGLL.getFirstElement() << endl;
cout << "Updated first free position: " << firstGLL.getFirstFree() << endl;
// Test GLRow class methods
cout << "\n=== Testing GLRow Methods ===\n";
GLRow<int> testRow(50); // Creating a GLRow object
cout << "Initial Row: " << testRow << endl;
// Set and Get methods
testRow.setNext(8);
testRow.setDown(4);
testRow.setInfo(75);
cout << "Updated Row: " << testRow << endl;
cout << "Next Pointer: " << testRow.getNext() << endl;
cout << "Down Pointer: " << testRow.getDown() << endl;
cout << "Info: " << testRow.getInfo() << endl;
// Test copy constructor
GLRow<int> copiedRow(testRow);
cout << "Copied Row: " << copiedRow << endl;
// Test assignment operator
GLRow<int> assignedRow(0);
assignedRow = copiedRow;
cout << "Assigned Row: " << assignedRow << endl;
// Ensure different memory locations
if (&testRow != &copiedRow && &copiedRow != &assignedRow) {
cout << "Deep copy successful: Objects have separate memory allocations." << endl;
} else {
cout << "Error: Deep copy failed!" << endl;
}
// Proper memory cleanup
delete secondGLL;
secondGLL = nullptr;
cout << "\n=== All Tests Completed Successfully! ===\n";
return 0;
}
Sample Input
14 2 8
999 12 -1
75 9 -1
90 -1 4
30 13 -1
80 1 6
85 -1 -1
55 7 -1
45 -1 -1
999 0 -1
15 -1 10
35 5 11
25 3 -1
999 -1 -1
10 -1 -1
Redirected Input: Redirected input provides you a way to send a file to the standard input of a program
without typing it using the keyboard. To use redirected input in Visual Studio environment, follow these
steps: After you have opened or created a new project, on the menu go to project, project properties, expand
configuration properties until you see Debugging, on the right you will see a set of options, and in the
command arguments type “< input filename”. The < sign is for redirected input and the input filename is
the name of the input file (including the path if not in the working directory). A simple program that reads a
matrix can be found below.
#include <iostream>
using namespace std;
int main () {
int r,c,cv,nsv;
int val;
cin >> r >> c >> cv >> nsv;
for (int i=0; i < r; i++) {
for (int j=0; j < c; j++) {
cin >> value;
cout << value << “ “;
}
endl;
}
return 0;
}
Constraints
1. In this project, the only header you will use is #include <iostream> and using namespace std.
2. None of the projects is a group project. Consulting with other members of this class our
seeking coding solutions from other sources including the web on programming projects is
strictly not allowed and plagiarism charges will be imposed on students who do not follow this.
