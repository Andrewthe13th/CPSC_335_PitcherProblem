#include <iomanip>
#include <iostream>
#include "assert.h"

using namespace std;

// the size of the testing matrix, change if necessay
const int SIZE = 4;

class Pitcher{
public:
  Pitcher() {contents = 0; capacity = 0;};
  Pitcher(int Contents, int Capacity){
    contents = Contents; capacity = Capacity;
  }
  void printPitcher(){cout << contents;};
  void printCapacity(){ cout << capacity;};
private:
  int contents;
  int capacity;
};

class PitcherGroup{
public:
  PitcherGroup(){ pitcherGroup[0] = Pitcher(0,16); pitcherGroup[1] = Pitcher(0,9); pitcherGroup[2] = Pitcher(0,7);};
  PitcherGroup(int a, int b, int c){pitcherGroup[0] = Pitcher(a,16); pitcherGroup[1] = Pitcher(b,9); pitcherGroup[2] = Pitcher(c,7);};
  void printPitcherGroup(){ for(auto &x : pitcherGroup){ x.printPitcher(); cout << " ";} cout << endl; };
private:
  Pitcher pitcherGroup[3];
};

int min(int a, int b)
{
  if(a != 0 && b != 0)
    return (a < b)? a: b;
  else
  {
    if(a == 0 && b == 0)
      return 0;
    else
      return (a != 0)? a: b;
  }

}

void printMatrix(int matrix[][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      cout << setw(2) << matrix[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
}

void FloydAlg(int matrix[][SIZE])
{
  cout << "inital Matrix: \n";
  printMatrix(matrix);
  for(int k = 0; k < SIZE; k++)
  {
    // looks at the row second
    for(int i = 0; i < SIZE; i++)
    {
      // looks at the column first
      for(int j = 0; j < SIZE; j++)
      {
        // do not update shortest path to itself
        if(i != j){
          // check for additions with 0, not valid as they are infinity
          if(matrix[i][k] != 0 && matrix[k][j] != 0)
            matrix[i][j] = min(matrix[i][j], (matrix[i][k]+matrix[k][j]) );
        }
      }
    }
    cout << "Floyd Round #" << k+1 << endl;
    printMatrix(matrix);
  }
}

bool matrixComparision(const int a[][SIZE], const int b[][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      if(a[i][j] != b[i][j])
      {
        cout << a[i][j] <<  " != " <<  b[i][j] << endl;
        return false;
      }
    }
  }
  return true;
}

// MAIN PROGRAM
int main(){

  // dummy code
  // PitcherGroup a(8,8,0);
  // a.printPitcherGroup();

  // Demo matrix
  int demoMatrix[SIZE][SIZE] = { {0,0,3,0},{2,0,0,0},{0,7,0,1},{6,0,0,0} };
  FloydAlg(demoMatrix);

  int matrixSolution[SIZE][SIZE] = { {0,10,3,4},{2,0,5,6},{7,7,0,1},{6,16,9,0} };
  if(matrixComparision(demoMatrix,matrixSolution))
    cout << "Matrix is correct!!!\n";
  else
    cout << "NOT A MATCH!!!!!\n";


  // end of program
  return 0;
}
