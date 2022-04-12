#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

using namespace std;

class Grid{
private:
	//vector<vector<int>> grid;//[9][9] po riadkoch
	map<int, int> gridMap;
	map<int, vector<int>> candidates; //iteracia cez "1-81" policok po riadkoch, vsetci kandidati
	map<int, vector<int>> nakedPairs; //dvojice ktore sa najdu v grid, opat pozicia 0-80 po riadkoch

public:
	Grid();
	Grid(vector<vector<int>> g);

//	void setGrid(vector<vector<int>> g) {grid=g;}
	void updateGrid(int position, int candidate);
//	vector<vector<int>> getGrid() { return grid; }
	void printGrid();
	void printEmptyGridSVG();
	void printGridSVG(string name);
	vector<int> getRow(int k);
	vector<int> getColumn(int k);
	vector<int> getBox(int k);
// 	int getValue(int i, int j){return grid[i][j];}

 	map<int, vector<int>> getRowCandidates(int k);
 	map<int, vector<int>> getColumnCandidates(int k);
 	map<int, vector<int>> getBoxCandidates(int k);

 	bool checkIfInside(vector<int> vector, int value);
 	int checkIfInsideCandidates(map<int, vector<int>> m, vector<int> vector, int key);

 	void findAllCandidates();
 	void rowRuleAllRows();
 	void columnRuleAllColumns();
 	void boxRuleAllBoxes();
 	vector<int> checkForSingleCandidatesAndUpdateGrid();
 	void findAllNakedPairs();
 	void updateCandidatesByPair();
 	void findAllHiddenPairs();

 	void print_mapCandidates();
 	void print_mapNakedPairs();
 	void printSVG_candidates(string name);
};
