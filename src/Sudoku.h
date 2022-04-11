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
	void updateGrid(int position, int candidate);
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
 	vector<int> checkForSingleCandidatesAndUpdateGrid();
 	void findAllNakedPairs();
 	void findAllHiddenPairs();

 	void print_map();
 	void printSVG_candidates(string name);

};
