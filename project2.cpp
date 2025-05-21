#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
class GLRow {
public:
    GLRow(T info = T()); // Constructor
    ~GLRow(); // Destructor

    void setInfo(T info);
    T getInfo() const;

    void setNext(int next);
    int getNext() const;

    void setDown(int down);
    int getDown() const;

    friend ostream& operator<<(ostream& os, const GLRow& row) {
        os << row.info << " " << row.next << " " << row.down;
        return os;
    }

private:
    T info;
    int next;
    int down;
};

template <typename T>
GLRow<T>::GLRow(T info) : info(info), next(-1), down(-1) {}

template <typename T>
GLRow<T>::~GLRow() {}

template <typename T>
void GLRow<T>::setInfo(T info) {
    this->info = info;
}

template <typename T>
T GLRow<T>::getInfo() const {
    return info;
}

template <typename T>
void GLRow<T>::setNext(int next) {
    this->next = next;
}

template <typename T>
int GLRow<T>::getNext() const {
    return next;
}

template <typename T>
void GLRow<T>::setDown(int down) {
    this->down = down;
}

template <typename T>
int GLRow<T>::getDown() const {
    return down;
}

template <typename T>
class ArrayGLL {
public:
    ArrayGLL(int size);
    ArrayGLL(const ArrayGLL& other);
    ~ArrayGLL();

    ArrayGLL& operator=(const ArrayGLL& other);

    GLRow<T>& operator[](int index);
    const GLRow<T>& operator[](int index) const;

    void setFirstElement(int firstElement);
    int getFirstElement() const;

    void setFirstFree(int firstFree);
    int getFirstFree() const;

    void display() const;
    int find(T key) const;
    void findDisplayPath(T key) const;
    int parentPos(T key) const;
    int size() const;
    int noFree() const;

    void traverse(int index, vector<int>& elements) const;

    void displayRecursive(int index) const;

private:
    GLRow<T>* rows;
    int size_;
    int firstElement;
    int firstFree;

    void copyFrom(const ArrayGLL& other);
};

template <typename T>
ArrayGLL<T>::ArrayGLL(int size) : size_(size), firstElement(-1), firstFree(0) {
    rows = new GLRow<T>[size_];
}

template <typename T>
ArrayGLL<T>::ArrayGLL(const ArrayGLL& other) {
    copyFrom(other);
}

template <typename T>
ArrayGLL<T>& ArrayGLL<T>::operator=(const ArrayGLL& other) {
    if (this != &other) {
        delete[] rows;
        copyFrom(other);
    }
    return *this;
}

template <typename T>
ArrayGLL<T>::~ArrayGLL() {
    delete[] rows;
}

template <typename T>
void ArrayGLL<T>::copyFrom(const ArrayGLL& other) {
    size_ = other.size_;
    firstElement = other.firstElement;
    firstFree = other.firstFree;
    rows = new GLRow<T>[size_];
    for (int i = 0; i < size_; ++i) {
        rows[i] = other.rows[i];
    }
}

template <typename T>
GLRow<T>& ArrayGLL<T>::operator[](int index) {
    return rows[index];
}

template <typename T>
const GLRow<T>& ArrayGLL<T>::operator[](int index) const {
    return rows[index];
}

template <typename T>
void ArrayGLL<T>::setFirstElement(int firstElement) {
    this->firstElement = firstElement;
}

template <typename T>
int ArrayGLL<T>::getFirstElement() const {
    return firstElement;
}

template <typename T>
void ArrayGLL<T>::setFirstFree(int firstFree) {
    this->firstFree = firstFree;
}

template <typename T>
int ArrayGLL<T>::getFirstFree() const {
    return firstFree;
}

template <typename T>
void ArrayGLL<T>::display() const {
    displayRecursive(firstElement);
}

template <typename T>
void ArrayGLL<T>::displayRecursive(int index) const {
    if (index == -1) return;
    cout << rows[index].getInfo();
    if (rows[index].getDown() != -1) {
        cout << "(";
        displayRecursive(rows[index].getDown());
        cout << ")";
    }
    if (rows[index].getNext() != -1) {
        cout << " ";
        displayRecursive(rows[index].getNext());
    }
}

template <typename T>
void ArrayGLL<T>::traverse(int index, vector<int>& elements) const {
    if (index == -1) return;
    elements.push_back(rows[index].getInfo());
    if (rows[index].getDown() != -1) {
        traverse(rows[index].getDown(), elements);
    }
    if (rows[index].getNext() != -1) {
        traverse(rows[index].getNext(), elements);
    }
}

template <typename T>
int ArrayGLL<T>::find(T key) const {
    for (int i = 0; i < size_; ++i) {
        if (rows[i].getInfo() == key) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void ArrayGLL<T>::findDisplayPath(T key) const {
    int pos = find(key);
    if (pos != -1) {
        cout << "Path to " << key << ": ";
        while (pos != -1) {
            cout << pos << " -> ";
            pos = rows[pos].getNext();
        }
        cout << "end" << endl;
    }
}

template <typename T>
int ArrayGLL<T>::parentPos(T key) const {
    int pos = find(key);
    if (pos == -1) return -1;
    for (int i = 0; i < size_; ++i) {
        if (rows[i].getDown() == pos || rows[i].getNext() == pos) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int ArrayGLL<T>::size() const {
    int count = 0;
    for (int i = 0; i < size_; ++i) {
        if (rows[i].getInfo() != 999) count++;
    }
    return count;
}

template <typename T>
int ArrayGLL<T>::noFree() const {
    int count = 0;
    for (int i = 0; i < size_; ++i) {
        if (rows[i].getInfo() == 999) count++;
    }
    return count;
}

template class ArrayGLL<int>;

int main() {
    int noElements, firstFree, firstElement;
    int value, next, down, parentPos;
    int pos = -1;
    int keyValue;

    cout << "Enter number of elements: ";
    cin >> noElements >> firstElement >> firstFree;

    ArrayGLL<int> firstGLL(noElements);
    firstGLL.setFirstElement(firstElement);
    firstGLL.setFirstFree(firstFree);

    for (int i = 0; i < noElements; i++) {
        cin >> value >> next >> down;
        GLRow<int> newRow(value);
        newRow.setNext(next);
        newRow.setDown(down);
        firstGLL[i] = newRow;
    }

    cout << "\n=== First GLL Structure ===\n";
    cout << "(";
    firstGLL.display();
    cout << ")" << endl;

    ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);
    if (!secondGLL) {
        cerr << "Error: Memory allocation failed for secondGLL." << endl;
        return 1;
    }

    int use = 600;
    (*secondGLL)[1].setInfo(use);
    use = 700;
    (*secondGLL)[2].setInfo(use);

    cout << "\n=== Second GLL (After Modifications) ===\n";
    cout << "(";
    (*secondGLL).display();
    cout << ")" << endl;

    keyValue = 700;
    pos = (*secondGLL).find(keyValue);
    if (pos != -1) {
        cout << "Element " << keyValue << " found at position: " << pos << endl;
        cout << "Element details: " << (*secondGLL)[pos] << endl;

        vector<int> extractedElements;
        (*secondGLL).traverse((*secondGLL).getFirstElement(), extractedElements);

        cout << "Extracted elements: ";
        for (int num : extractedElements) {
            cout << num << " ";
        }
        cout << endl;

    } else {
        cout << "Element " << keyValue << " not found." << endl;
    }

    parentPos = (*secondGLL).parentPos(keyValue);
    if (parentPos != -1) {
        cout << "Parent of " << keyValue << " is at position: " << parentPos << endl;
        cout << "Parent details: " << (*secondGLL)[parentPos] << endl;
    } else {
        cout << "Parent of " << keyValue << " not found." << endl;
    }

    cout << "\nSize of secondGLL: " << (*secondGLL).size() << endl;
    cout << "Number of free locations: " << (*secondGLL).noFree() << endl;

    cout << "\nFirst element position: " << firstGLL.getFirstElement() << endl;
    cout << "First free position: " << firstGLL.getFirstFree() << endl;

    firstGLL.setFirstElement(2);
    firstGLL.setFirstFree(5);
    cout << "Updated first element position: " << firstGLL.getFirstElement() << endl;
    cout << "Updated first free position: " << firstGLL.getFirstFree() << endl;

    cout << "\n=== Testing GLRow Methods ===\n";
    use = 50;
    GLRow<int> testRow(use);
    cout << "Initial Row: " << testRow << endl;

    testRow.setNext(8);
    testRow.setDown(4);
    use = 75;
    testRow.setInfo(use);
    cout << "Updated Row: " << testRow << endl;
    cout << "Next Pointer: " << testRow.getNext() << endl;
    cout << "Down Pointer: " << testRow.getDown() << endl;
    cout << "Info: " << testRow.getInfo() << endl;

    GLRow<int> copiedRow(testRow);
    cout << "Copied Row: " << copiedRow << endl;

    use = 0;
    GLRow<int> assignedRow(use);
    assignedRow = copiedRow;
    cout << "Assigned Row: " << assignedRow << endl;

    if (&testRow != &copiedRow && &copiedRow != &assignedRow) {
        cout << "Deep copy successful: Objects have separate memory allocations." << endl;
    } else {
        cout << "Error: Deep copy failed!" << endl;
    }

    delete secondGLL;
    secondGLL = nullptr;

    cout << "\n=== All Tests Completed Successfully! ===";
    return 0;
}