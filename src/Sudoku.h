#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Grid{
private:
	vector<vector<int>> grid; //[9][9] po riadkoch
	map<int, vector<int>> candidates; //iteracia cez "1-81" policok po riadkoch, vsetci kandidati

public:
	Grid();
	Grid(vector<vector<int>> g) {grid=g;}

	void setGrid(vector<vector<int>> g) {grid=g;}
	vector<vector<int>> getGrid() { return grid; }
	void printGrid();
	void printEmptyGridSVG();
	void printGridSVG(string name);
	vector<int> getRow(int k) {return grid[k];}
	vector<int> getColumn(int k);
	vector<int> getBox(int k, int l);
 	bool checkIfInside(vector<int> vector, int value);
 	int getValue(int i, int j){return grid[i][j];}

 	void findAllCandidates();

/*  void findAllNakedPairs();{
    cout << "Finding all naked pairs" << endl;
    vector<int> c; //kandidati pre konkretne policko 0-80
    for (auto itr = candidates.begin(); itr != candidates.end(); ++itr) {
      cout << itr->first << "\t";
      int size = itr->second.size();
      if (size == 2){

      }



      }
      cout << endl;
    }

  }*/

 	void print_map();
 	void printSVG_candidates();

};
