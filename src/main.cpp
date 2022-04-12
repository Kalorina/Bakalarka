#include "Sudoku.h"

using namespace std;


void printVector(vector<int> v){
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << ", ";
	}
	cout << "]" << endl;
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

  	  string name = "unsolved";
  	  Grid grid(values);
  	  //grid.printGrid();
  	  //grid.printEmptyGridSVG();
  	  //grid.printGridSVG(name);

  	  grid.findAllCandidates();
  	  //grid.printSVG_candidates(name);
  	  //grid.print_map();

  	  //zakladne tri pravidla
  	  vector<int> k;
  	  int itr = 1;
  	  do {
  		  k = grid.checkForSingleCandidatesAndUpdateGrid();
  		  if(k.empty()){
  			  break;
  		  }
  		  cout << "position: " << k.front() << " candidate: " << k.back() << endl;
  		  grid.updateGrid(k.front(), k.back());
  		  grid.findAllCandidates();
  		  //grid.printGrid();
  		  string n = name + to_string(itr);
  		  //grid.printGridSVG(n);
  		  //grid.printSVG_candidates(n);
  		  itr++;
  	  }
  	  while (!k.empty());

  	  //grid.printGrid();

  	  //naked pairs
  	  grid.findAllNakedPairs();
  	  grid.print_mapNakedPairs();


  	  //Solved Example

  	  vector<int> a1 = {2,7,4,1,5,9,3,6,8}; //zapis po riadkoch
  	  vector<int> b1 = {1,8,5,3,2,6,7,9,4};
  	  vector<int> c1 = {3,6,9,4,7,8,1,5,2};
  	  vector<int> d1 = {7,5,8,6,4,1,9,2,3};
  	  vector<int> e1 = {6,2,3,9,8,5,4,7,1};
  	  vector<int> f1 = {9,4,1,2,3,7,5,8,6};
  	  vector<int> g1 = {8,3,6,7,9,4,2,1,5};
  	  vector<int> h1 = {4,1,7,5,6,2,8,3,9};
  	  vector<int> i1 = {5,9,2,8,1,3,6,4,7};

  	  vector<vector<int>> values1;

  	  values1.push_back(a1);
  	  values1.push_back(b1);
  	  values1.push_back(c1);
  	  values1.push_back(d1);
  	  values1.push_back(e1);
  	  values1.push_back(f1);
  	  values1.push_back(g1);
  	  values1.push_back(h1);
  	  values1.push_back(i1);

  	  string name1 = "solved";
  	  Grid grid1(values1);
  	  //grid1.printGridSVG(name1);
}
