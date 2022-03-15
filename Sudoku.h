#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Grid{
private:
  vector<vector<int>> grid;

public:

  Grid(vector<vector<int>> g) {grid=g;}

  void setGrid(vector<vector<int>> g) {grid=g;}

  void printGrid(){

    for (size_t i = 0; i < 9; i++) {
      for (size_t j = 0; j < 9; j++) {
        if(grid[i][j] == 0)
    cout<<".";
        else
    cout<<grid[i][j];
        cout<<"|";
      }
      cout<<endl;
    }

  }

};
