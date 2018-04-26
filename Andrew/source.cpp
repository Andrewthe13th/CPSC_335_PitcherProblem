#include <iomanip>
#include <iostream>
#include "assert.h"

using namespace std;

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
  return (a > b)? a: b;
}

void FloydAlg(int matrix[][9])
{
  for(int k = 0; k < 9; k++)
  {
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        // do not update shortest path to itself
        if(i != j){
          matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
        }
      }
    }
  }
}


// MAIN PROGRAM
int main(){

  // dummy code
  // PitcherGroup a(8,8,0);
  // a.printPitcherGroup();

  // Demo matrix
  



  // end of program
  return 0;
}
