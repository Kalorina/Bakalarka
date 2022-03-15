#include "Sudoku.h"

using namespace std;

int genRandNum(int max){
  return rand()%max;
}

int main(int argc, char const *argv[]) {

srand(time(NULL)); //for generating random number

  vector<int> a = {2,0,0,1,0,0,0,6,0}; //zapis po riadkoch
  vector<int> b = {0,8,5,0,2,0,0,9,0};
  vector<int> c = {0,0,0,0,7,0,1,0,2};
  vector<int> d = {0,0,0,0,0,1,0,0,3};
  vector<int> e = {0,0,0,9,0,5,0,0,0};
  vector<int> f = {9,0,0,2,0,0,0,0,0};
  vector<int> g = {8,0,6,0,9,0,0,0,0};
  vector<int> h = {0,1,0,0,6,0,8,3,0};
  vector<int> i = {0,9,0,0,0,3,0,0,7};

  vector<vector<int>> values;

  values.push_back(a);
  values.push_back(b);
  values.push_back(c);
  values.push_back(d);
  values.push_back(e);
  values.push_back(f);
  values.push_back(g);
  values.push_back(h);
  values.push_back(i);

  Grid grid(values);
  grid.printGrid();

  /*for (size_t i = 0; i < 9; i++) {
    cout << "i: " << i << endl;
    for (size_t j = 0; j < 9; j++) {
      cout << "values[i][j]: " << values[i][j] << endl;
    }
  }*/

}
