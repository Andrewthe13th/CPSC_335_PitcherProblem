#include "assert.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// the size of the testing matrix, change if necessay
const int SIZE = 4;

class Pitcher {
public:
  Pitcher() {
    contents = 0;
    capacity = 0;
  };
  Pitcher(int Contents, int Capacity) {
    contents = Contents;
    capacity = Capacity;
  }
  void printPitcher() { cout << contents; };
  void printCapacity() { cout << capacity; };
  bool hasRoom() { return (contents != capacity); }
  int space() { return (capacity - contents); }
  int getContents() const { return contents; }

private:
  int contents;
  int capacity;
};

class PitcherGroup {
public:
  PitcherGroup() {
    pitcherGroup[0] = Pitcher(0, 16);
    pitcherGroup[1] = Pitcher(0, 9);
    pitcherGroup[2] = Pitcher(0, 7);
  };
  PitcherGroup(int a, int b, int c) {
    pitcherGroup[0] = Pitcher(a, 16);
    pitcherGroup[1] = Pitcher(b, 9);
    pitcherGroup[2] = Pitcher(c, 7);
  };
  void printPitcherGroup() {
    for (auto &x : pitcherGroup) {
      x.printPitcher();
      cout << " ";
    }
    cout << endl;
  };
  bool operator==(const PitcherGroup &rhs) {
    return ((this->pitcherGroup[0].getContents() ==
             rhs.pitcherGroup[0].getContents()) &&
            (this->pitcherGroup[1].getContents() ==
             rhs.pitcherGroup[1].getContents()) &&
            (this->pitcherGroup[2].getContents() ==
             rhs.pitcherGroup[2].getContents()));
  }
  Pitcher pitcherGroup[3];
};

int min(int a, int b) {
  if (a != 0 && b != 0)
    return (a < b) ? a : b;
  else {
    if (a == 0 && b == 0)
      return 0;
    else
      return (a != 0) ? a : b;
  }
}

void printMatrix(int matrix[][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      cout << setw(2) << matrix[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
}

struct Node {
  PitcherGroup data;
  Node *c1, *c2, *c3, *c4, *c5, *c6;
};

Node *newnode(int a, int b, int c) {
  Node *node = new Node;
  node->data = PitcherGroup(a, b, c);
  Node *c1, *c2, *c3, *c4, *c5, *c6 = 0;
  return (node);
}

class Tree {
public:
  Node *root;
  vector<PitcherGroup> v;
  Tree() {
    root = newnode(16, 0, 0);
    v.push_back(root->data);
  }
  Node *createTree(Node *n) {
    cout << "pointer :";
    cout << n;
    cout << " is found here" << endl;
    ;

    // If last round didn't add anything new than quit
    if (n == NULL) {
      return NULL;
    } else {
      bool newPitcherCombinations = false;
      int new7pitcher = 0;
      int new9pitcher = 0;
      int new16pitcher = 0;
      // Check if the 16 pitcher is not empty
      if (n->data.pitcherGroup[0].getContents() != 0) {

        // check if the 9 pitcher has rooom
        if (n->data.pitcherGroup[1].hasRoom()) {

          // If 16pitcher has more water than the 9 pitcher has space
          if (n->data.pitcherGroup[1].space() <
              n->data.pitcherGroup[0].getContents()) {
            // how much the 16 pitcher will have after the move
            new16pitcher = n->data.pitcherGroup[0].getContents() -
                           n->data.pitcherGroup[1].space();
            // fill up 9
            new9pitcher = 9;
          } else {
            // pitcher 9 is partially filled
            new9pitcher = n->data.pitcherGroup[1].getContents() +
                          (n->data.pitcherGroup[0].getContents());
            new16pitcher = 0;
          }
          // create new node from edge 16->9
          cout << "c1 start:" << n->c1 << endl;
          n->c1 = newnode(new16pitcher, new9pitcher,
                          n->data.pitcherGroup[2].getContents());
          cout << "c1 finish:" << n->c1 << endl;
        }
        // check if ptcher 7 has room
        if (n->data.pitcherGroup[2].hasRoom()) {

          // If 16pitcher has more water than the 7 pitcher has space
          if (n->data.pitcherGroup[2].space() <
              n->data.pitcherGroup[0].getContents()) {
            // how much the 16 pitcher will have after the move
            new16pitcher = n->data.pitcherGroup[0].getContents() -
                           n->data.pitcherGroup[2].space();
            // fill up 7
            new7pitcher = 7;
          } else {
            // pitcher 7 is partially filled
            new7pitcher = n->data.pitcherGroup[2].getContents() +
                          n->data.pitcherGroup[0].getContents();
            new16pitcher = 0;
          }
          // create new node from edge 16->7
          cout << "c2 start:" << n->c2 << endl;
          n->c2 = newnode(new16pitcher, n->data.pitcherGroup[1].getContents(),
                          new7pitcher);
          cout << "c2 finish:" << n->c2 << endl;
        }
      }

      // Check if the 9 pitcher is empty
      if (n->data.pitcherGroup[1].getContents() != 0) {
        // check if the 16 pitcher has rooom
        if (n->data.pitcherGroup[0].hasRoom()) {

          // If 9 pitcher has more water than the 16 pitcher has space
          if (n->data.pitcherGroup[0].space() <
              n->data.pitcherGroup[1].getContents()) {
            // how much the 9 pitcher will have after the move
            new9pitcher = n->data.pitcherGroup[1].getContents() -
                          n->data.pitcherGroup[0].space();
            // fill up 16
            new16pitcher = 16;
          } else {
            // pitcher 16 is partially filled
            new16pitcher = n->data.pitcherGroup[1].getContents() +
                           n->data.pitcherGroup[0].getContents();
            new9pitcher = 0;
          }
          // create new node from edge 9->16
          cout << "c3 start:" << n->c3 << endl;

          n->c3 = newnode(new16pitcher, new9pitcher,
                          n->data.pitcherGroup[2].getContents());
        }
        cout << "c3 finish:" << n->c3 << endl;

        // check if ptcher 7 has room
        if (n->data.pitcherGroup[2].hasRoom()) {

          // If pitcher 9 has more water than the 7 pitcher has space
          if (n->data.pitcherGroup[2].space() <
              n->data.pitcherGroup[1].getContents()) {
            // how much the 9 pitcher will have after the move
            new9pitcher = n->data.pitcherGroup[1].getContents() -
                          n->data.pitcherGroup[2].space();
            // fill up 7
            new7pitcher = 7;

          } else {
            // pitcher 7 is partially filled
            new7pitcher = n->data.pitcherGroup[2].getContents() +
                          n->data.pitcherGroup[1].getContents();
            new9pitcher = 0;
          }
          // create new node from edge 9->7
          cout << "c4 start:" << n->c4 << endl;

          n->c4 = newnode(n->data.pitcherGroup[0].getContents(), new9pitcher,
                          new7pitcher);
          cout << "c4 finish:" << n->c4 << endl;
        }
      }

      // Check if the 7 pitcher is empty
      if (n->data.pitcherGroup[2].getContents() != 0) {
        // check if the 16 pitcher has rooom
        if (n->data.pitcherGroup[0].hasRoom()) {

          // If 7 pitcher has more water than the 16 pitcher has space
          if (n->data.pitcherGroup[0].space() <
              n->data.pitcherGroup[2].getContents()) {
            // how much the 7 pitcher will have after the mov
            new7pitcher = n->data.pitcherGroup[2].getContents() -
                          n->data.pitcherGroup[0].space();
            // fill up 16
            new16pitcher = 16;

          } else {
            // pitcher 16 is partially filled
            new16pitcher = n->data.pitcherGroup[2].getContents() +
                           n->data.pitcherGroup[0].getContents();
            new7pitcher = 0;
          }
          // create new node from edge 7->16
          cout << "c5 start:" << n->c5 << endl;

          n->c5 = newnode(new16pitcher, n->data.pitcherGroup[1].getContents(),
                          new7pitcher);
          cout << "c5 finish:" << n->c5 << endl;
        }
        // check if ptcher 9 has room
        if (n->data.pitcherGroup[2].hasRoom()) {

          // If pitcher 7 has more water than the 9 pitcher has space
          if (n->data.pitcherGroup[1].space() <
              n->data.pitcherGroup[2].getContents()) {
            // how much the 7 pitcher will have after the move
            new7pitcher = n->data.pitcherGroup[2].getContents() -
                          n->data.pitcherGroup[1].space();
            // fill up 9
            new9pitcher = 9;
          } else {
            // pitcher 7 is partially filled
            new7pitcher = n->data.pitcherGroup[2].getContents() +
                          n->data.pitcherGroup[1].getContents();
            new7pitcher = 0;
          }
          // create new node from edge 7->9
          cout << "c6 start:" << n->c6 << endl;

          n->c6 = newnode(n->data.pitcherGroup[0].getContents(), new9pitcher,
                          new7pitcher);
          cout << "c6 finish:" << n->c6 << endl;
        }
      }

      cout << "c1 is:" << n->c1 << endl;
      cout << "c2 is:" << n->c2 << endl;
      cout << "c3 is:" << n->c3 << endl;
      cout << "c4 is:" << n->c4 << endl;
      cout << "c5 is:" << n->c5 << endl;
      cout << "c6 is:" << n->c6 << endl;
      // bool to check if there were any new pitcher combinations
      // checks all new pitcher combos just made
      cout << "1" << endl;
      if (n->c1 != NULL) {
        if (std::find(v.begin(), v.end(), n->c1->data) != v.end()) {
        } else { // If a new pitcher combo was found throw it in the vector
          v.push_back(n->c1->data);
          newPitcherCombinations = true;
        }
      }
      cout << "2" << endl;
      if (n->c2 != NULL) {
        if (std::find(v.begin(), v.end(), n->c2->data) != v.end()) {
        } else {
          // If a new pitcher combo was found throw it in the vector
          v.push_back(n->c2->data);
          newPitcherCombinations = true;
        }
      }
      cout << "3" << endl;
      if (n->c3 != NULL) {
        if (std::find(v.begin(), v.end(), n->c3->data) != v.end()) {
        } else {
          // If a new pitcher combo was found throw it in the vector
          v.push_back(n->c3->data);
          newPitcherCombinations = true;
        }
      }
      cout << "4" << endl;
      if (n->c4 != NULL) {
        if (std::find(v.begin(), v.end(), n->c4->data) != v.end()) {

        } else {
          // If a new pitcher combo was found throw it in the vector
          v.push_back(n->c4->data);
          newPitcherCombinations = true;
        }
      }
      cout << "5" << endl;
      if (n->c5 != NULL) {
        if (std::find(v.begin(), v.end(), n->c5->data) != v.end()) {

        } else {
          // If a new pitcher combo was found throw it in the vector
          v.push_back(n->c5->data);
          newPitcherCombinations = true;
        }
      }
      cout << "6" << endl;
      if (n->c6 != NULL) {
        if (std::find(v.begin(), v.end(), n->c6->data) != v.end()) {

        } else {
          // If a new pitcher combo was found throw it in the vector
          v.push_back(n->c6->data);
          newPitcherCombinations = true;
        }
      }

      // If just one new pitcher combo was found, take tree down a level
      if (newPitcherCombinations) {
        createTree(n->c1);
        cout << "test1" << endl;
        createTree(n->c2);
        cout << "test2" << endl;
        createTree(n->c3);
        cout << "test3" << endl;
        createTree(n->c4);
        cout << "test4" << endl;
        createTree(n->c5);
        cout << "test5" << endl;
        createTree(n->c6);
        cout << "finished one loop ##################" << endl;
      } else {
        cout << "There was nothing new added" << endl;
        return NULL;
      }
    }
  }
};

void FloydAlg(int matrix[][SIZE]) {
  cout << "inital Matrix: \n";
  printMatrix(matrix);
  for (int k = 0; k < SIZE; k++) {
    // looks at the row second
    for (int i = 0; i < SIZE; i++) {
      // looks at the column first
      for (int j = 0; j < SIZE; j++) {
        // do not update shortest path to itself
        if (i != j) {
          // check for additions with 0, not valid as they are infinity
          if (matrix[i][k] != 0 && matrix[k][j] != 0)
            matrix[i][j] = min(matrix[i][j], (matrix[i][k] + matrix[k][j]));
        }
      }
    }
    cout << "Floyd Round #" << k + 1 << endl;
    printMatrix(matrix);
  }
}

bool matrixComparision(const int a[][SIZE], const int b[][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (a[i][j] != b[i][j]) {
        cout << a[i][j] << " != " << b[i][j] << endl;
        return false;
      }
    }
  }
  return true;
}

// MAIN PROGRAM
int main() {
  Tree start;
  // dummy code
  // PitcherGroup a(8,8,0);
  // a.printPitcherGroup();
  Node *test = start.createTree(start.root);

  // Demo matrix
  int demoMatrix[SIZE][SIZE] = {
      {0, 0, 3, 0}, {2, 0, 0, 0}, {0, 7, 0, 1}, {6, 0, 0, 0}};
  FloydAlg(demoMatrix);

  int matrixSolution[SIZE][SIZE] = {
      {0, 10, 3, 4}, {2, 0, 5, 6}, {7, 7, 0, 1}, {6, 16, 9, 0}};
  if (matrixComparision(demoMatrix, matrixSolution))
    cout << "Matrix is correct!!!\n";
  else
    cout << "NOT A MATCH!!!!!\n";
  // end of program
  return 0;
}
