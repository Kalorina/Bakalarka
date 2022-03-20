#include "Sudoku.h"

using namespace std;

void print_map(map<int, vector<int>> mp){
  cout << "KEY\tELEMENT\n";
  for (auto itr = mp.begin(); itr != mp.end(); ++itr) {
    cout << itr->first << "\t";
    for (auto it = itr->second.begin(); it != itr->second.end(); it++){
      cout << *it << " ";
    }
    cout << endl;
  }
}
void printVector(vector<int> v){
  cout << "[";
  for (size_t i = 0; i < v.size(); i++) {
    cout << v[i] << ", ";
  }
  cout << "]" << endl;
}

map<int, vector<int>> findAllCandidates(Grid sudoku){ //3 main rules
  cout << "Finding all candicates" << endl;
  map<int, vector<int>> mp;
  vector<int> candidates;
  for (size_t i = 0; i < sudoku.getGrid().size(); i++) {
    for (size_t j = 0; j < sudoku.getGrid()[i].size(); j++) {
      for (size_t k = 1; k < 10; k++){
        if(sudoku.getGrid()[i][j] == 0){
          if (!sudoku.checkIfInside(sudoku.getRow(i), k)) {
           //cout << "Row: " << i << " Value: " << j << endl;
           if (!sudoku.checkIfInside(sudoku.getColumn(j), k)) {
             //cout << "Column: " << j << " Value: " << j << endl;
             if (!sudoku.checkIfInside(sudoku.getBox(i,j), k)) {
                //cout << "Box: " << j << " Value: " << j << endl;
                candidates.push_back(k);
              }
            }
          }
        }
      }
      mp.insert({i*9+j, candidates});
      candidates.clear();
    }
  }
  return mp;
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
  //grid.printGrid();
  //grid.printSVG();

  map<int, vector<int>> candidates; //iteracia cez "1-81" policok po riadkoch
  candidates = findAllCandidates(grid);
  print_map(candidates);
}
