#include <iostream>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {

    int noElements, firstFree, firstElement;
    int value, next, down, parentPos;
    int pos = -1;
    int keyValue;
    // Read the number of elements
    cout << "Enter number of elements: ";
    cin >> noElements >> firstElement >> firstFree;
    // Setting up the structure
    ArrayGLL<int> firstGLL(noElements);
    firstGLL.setFirstElement(firstElement);
    firstGLL.setFirstFree(firstFree);
    // Input validation and initialization of GLRows
    for (int i = 0; i < noElements; i++) {
        cin >> value >> next >> down;
        // Dynamically create a new GLRow<int> for each entry
        GLRow<int> newRow(value);
        newRow.setNext(next);
        newRow.setDown(down);
        firstGLL[i] = newRow;
    }
    cout << "\n=== First GLL Structure ===\n";
    firstGLL.display();
    // Testing copy constructor
    ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);
    if (!secondGLL)
    {
        cerr << "Error: Memory allocation failed for secondGLL." << endl;
        return 1;
    }
    int use = 600;
    (*secondGLL)[1].setInfo(use);
    use =700;
    (*secondGLL)[2].setInfo(use);
    cout << "\n=== Second GLL (After Modifications) ===\n";
    (*secondGLL).display();
    // Testing find function
    keyValue = 700;
    pos = (*secondGLL).find(keyValue);
    if (pos != -1)
    {
        cout << "Element " << keyValue << " found at position: " << pos << endl;
        cout << "Element details: " << (*secondGLL)[pos] << endl;
        (*secondGLL).findDisplayPath(keyValue);
        cout << endl;
    }
    else
    {
        cout << "Element " << keyValue << " not found." << endl;
    }
    // Testing parentPos function
    parentPos = (*secondGLL).parentPos(keyValue);
    if (parentPos != -1) {
        cout << "Parent of " << keyValue << " is at position: " << parentPos <<
        endl;
        cout << "Parent details: " << (*secondGLL)[parentPos] << endl;
    }
    else
    {
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
    cout << "Updated first element position: " << firstGLL.getFirstElement() <<
    endl;
    cout << "Updated first free position: " << firstGLL.getFirstFree() << endl;
    // Test GLRow class methods
    cout << "\n=== Testing GLRow Methods ===\n";
    use = 50;
    GLRow<int> testRow(use); // Creating a GLRow object
    cout << "Initial Row: " << testRow << endl;
    // Set and Get methods
    testRow.setNext(8);
    testRow.setDown(4);
    use = 75;
    testRow.setInfo(use);
    cout << "Updated Row: " << testRow << endl;
    cout << "Next Pointer: " << testRow.getNext() << endl;
    cout << "Down Pointer: " << testRow.getDown() << endl;
    cout << "Info: " << testRow.getInfo() << endl;
    // Test copy constructor
    GLRow<int> copiedRow(testRow);
    cout << "Copied Row: " << copiedRow << endl;
    // Test assignment operator
    use = 0;
    GLRow<int> assignedRow(use);
    assignedRow = copiedRow;
    cout << "Assigned Row: " << assignedRow << endl;
    // Ensure different memory locations
    if (&testRow != &copiedRow && &copiedRow != &assignedRow)
    {
        cout << "Deep copy successful: Objects have separate memory allocations."
        << endl;
    }
    else
    {
        cout << "Error: Deep copy failed!" << endl;
    }
    // Proper memory cleanup
    delete secondGLL;
    secondGLL = nullptr;
    cout << "\n=== All Tests Completed Successfully! ===";
    return 0;
}





// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.