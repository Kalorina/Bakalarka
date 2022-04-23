/*
 * Sudoku.h
 *
 *  Created on: Jan 10, 2022
 *      Author: Karolina Vallova
 */

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

using namespace std;

class Grid{
private:
	map<int, int> gridMap;
	map<int, vector<int>> candidates; //iteracia cez "1-81" policok po riadkoch, vsetci kandidati
	map<int, vector<int>> nakedPairs; //dvojice ktore sa najdu v grid, opat pozicia 0-80 po riadkoch

public:
	Grid() {};
	Grid(vector<vector<int>> g);

	void setUpGrid(vector<vector<int>> s);
	void setUpFromFile(string filename);
	void updateGrid(int position, int candidate);
	void printGrid();
	void printEmptyGridSVG();
	void printGridSVG(string name);
	vector<int> getRow(int k);
	vector<int> getColumn(int k);
	vector<int> getBox(int k);

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
 	void findAllHiddenPairs(); // nieje dokoncene

 	void print_map();
 	void print_mapCandidates();
 	void print_mapNakedPairs();
 	void printSVG_candidates(string name);
};
