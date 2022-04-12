#include "Sudoku.h"
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

using namespace std;


void printVector(vector<int> v){
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << ", ";
	}
	cout << "]" << endl;
}

vector<vector<int>> loadSudokuFromFile(string filename) {

	ifstream myFile(filename);

	if(!myFile.is_open()) throw runtime_error("Could not open file");

    vector<vector<int>> grid;

    string line, colname;
    int val;
    vector<int>	row;

    while(getline(myFile, line)) {
    	stringstream ss(line);
		row.clear();
    	while(ss >> val){
    		row.push_back(val);
    		if(ss.peek() == ',') ss.ignore();
    	}
    	grid.push_back(row);
    }

    myFile.close();

    return grid;
}

int main(int argc, char const *argv[]) {

	  // ***************Unsolved Example*****************************

	  string name = "unsolved";
  	  vector<vector<int>> values = loadSudokuFromFile("example.cvs");
  	  Grid grid(values);
  	  //grid.printGrid();
  	  grid.printEmptyGridSVG();
  	  grid.printGridSVG(name);

 	  grid.rowRuleAllRows();
	  grid.printSVG_candidates(name+"_rowRule");
	  grid.columnRuleAllColumns();
 	  grid.printSVG_candidates(name+"_columnRUle");
  	  grid.boxRuleAllBoxes();
  	  grid.printSVG_candidates(name+"_boxRule");
  	  //grid.print_map();



  	  //***********************Algo***************************
/* 	  vector<int> k;
  	  int itr = 1;
  	  do {
  		  k = grid.checkForSingleCandidatesAndUpdateGrid();
  		  if(k.empty()){
  			  //naked pair algo
  		  	  grid.findAllNakedPairs();
  		  	  grid.updateCandidatesByPair();
  		  	  string n = name + to_string(itr) + "nakedPair";
  		  	  grid.printGridSVG(n);
  		  	  grid.printSVG_candidates(n);
  		  	  k = grid.checkForSingleCandidatesAndUpdateGrid();
  		  	  itr++;
  		  	  continue;
  		  }
  		  //single candidates algo
  		  cout << "position: " << k.front() << " candidate: " << k.back() << endl;
  		  grid.updateGrid(k.front(), k.back());
  		  grid.findAllCandidates();
  		  //grid.printGrid();
  		  string n = name + to_string(itr) + "singleCandidate";
  		  grid.printGridSVG(n);
  		  grid.printSVG_candidates(n);
  		  itr++;
  	  }
  	  while (!k.empty());

  	  //grid.printGrid();

  	  //naked pairs practice

  	  //grid.print_mapCandidates();
  	  //grid.findAllNakedPairs();
  	 // grid.updateCandidatesByPair();
  	  //grid.print_mapNakedPairs();
  	  //grid.print_mapCandidates();
  	  //string n = name + "skuska";
  	  //grid.printSVG_candidates(n);
*/
  	  //*****************Solved Example**********************

  	  string name1 = "solved";
  	  vector<vector<int>> values1 = loadSudokuFromFile("solved_example.csv");
  	  Grid grid1(values1);
  	  grid1.printGridSVG(name1);

  	  cout << "done" << endl;
}
