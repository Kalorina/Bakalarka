/*
 * Sudoku.cpp
 *
 *  Created on: Jan 10, 2022
 *      Author: Karolina Vallova
 */

#include "Sudoku.h"

Grid::Grid(vector<vector<int>> g) {
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9+j;
			gridMap[key] = g[i][j];
			vector<int> v; // = {1, 2, 3, 4, 5, 6, 7, 8, 9};
			candidates[key] = v;
			nakedPairs[key] = v;
		}
	}
}

void Grid::setUpGrid(vector<vector<int>> s) {
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9+j;
			gridMap[key] = s[i][j];
			vector<int> v;
			candidates[key] = v;
			nakedPairs[key] = v;
		}
	}
}

void Grid::setUpFromFile(string filename) {

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

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9+j;
			gridMap[key] = grid[i][j];
			vector<int> v;
			candidates[key] = v;
			nakedPairs[key] = v;
		}
	}
}

void Grid::updateGrid(int position, int candidate){ //pre 3 zakladne pravidla
	gridMap[position] = candidate;
}

void Grid::printGrid(){
    for (size_t i = 0; i < 9; i++) {
    	for (size_t j = 0; j < 9; j++) {
    		int key = i*9+j;
    		if(gridMap[key] == 0)
    			cout<<".";
    		else
    			cout<<gridMap[key];
    		cout<<"|";
    	}
    	cout<<endl;
    }
}

vector<int> Grid::getColumn(int position) {
	vector<int> column_values;
	int column = position % 9;
	for (size_t i = 0; i < 9; i++) {
		int key = i*9+column;
		column_values.push_back(gridMap[key]);
	}
	return column_values;
}

vector<int> Grid::getRow(int position) {
	vector<int> row_values;
	int row = position / 9;
	for (size_t j = 0; j < 9; j++) {
		int key = row*9+j;
		row_values.push_back(gridMap[key]);
	}
	return row_values;
}

vector<int> Grid::getBox(int position) {
	vector<int> box;
    //b=0-8, pricom 0->lavyhorny a 8->pravydolny a po riadkoch
	int b = (position/3)%3 + 3*((position/9)/3);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int key = i*9+j;
			int current_b = (key/3)%3 + 3*((key/9)/3);
			if (current_b == b) {
				box.push_back(gridMap[key]);
			}
		}
	}
	return box;
}

map<int, vector<int>> Grid::getRowCandidates(int k){
	map<int, vector<int>> row;
	for(size_t i = 0; i < 9; i++){
		int key = i + (9 * k);
		auto search = candidates.find(key); //konkretny element=policko z mapy
		row.insert({key, search->second});
	}
	return row;
}

map<int, vector<int>> Grid::getColumnCandidates(int k){
	map<int, vector<int>> column;
	int key;
	for(size_t i = 0; i < 9; i++){
		key = (i * 9) + k;
		auto search = candidates.find(key); //konkretny element=policko z mapy
		column.insert({key, search->second});
	}
	return column;
}

map<int, vector<int>> Grid::getBoxCandidates(int k){
	map<int, vector<int>> box;
	int key;
	for (size_t i = 0; i < 3; i++) {
		for(size_t j = 0; j < 3; j++){
			key = i + (3 * k) + (j * 9) + ((k / 3) * 18);
			auto search = candidates.find(key);
			box.insert({key, search->second});
		}
	}
	return box;
}

bool Grid::checkIfInside(vector<int> vector, int value) {
    for (size_t i = 0; i < vector.size(); i++) {
    	if (vector[i] == value) {
    		return true;
    	}
    }
    return false;
}

bool Grid::checkIfInsideOnce(vector<int> vector, int value) {
	int count = 0;
    for (size_t i = 0; i < vector.size(); i++) {
    	if (vector[i] == value) {
    		count++;
    	}
    }

    if (count == 1){return true;}
    else {return false;}
}

int Grid::checkIfInsideCandidates(map<int, vector<int>> m, vector<int> vector, int key) {
	int k = -1;
	for (auto itr = m.begin(); itr != m.end(); ++itr) {
		if (itr->first != key && vector == itr->second){
			k = itr->first;
			return k; //vrati match key
		}
	}
	return k;
}

bool Grid::checkIfInsideNakedPairs(int position, int candidate) {

	for (auto itr = nakedPairs.begin(); itr != nakedPairs.end(); ++itr) {
		if (itr->first == position){
			if(checkIfInside(itr->second, candidate)){
				return true;
			}
		}
	}
	return false;
}

bool Grid::checkIfSolved() {
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9+j;
			if (gridMap[key] == 0) {
				return false;
			}
		}
	}
	if(checkIfSolvedCorrectly()){
		return true;
	}
	else return false;
}

bool Grid::checkIfSolvedCorrectly() {

	int count = 0;
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9 +j;
			for (size_t k = 1; k < 10; k++){
				if (checkIfInsideOnce(getRow(key), k)) {
					if (checkIfInsideOnce(getColumn(key), k)) {
						if (checkIfInsideOnce(getBox(key), k)) {
							count++;
						}
					}
				}
			}
		}
	}
	if (count == 729) return true;
	else return false;
}

void Grid::findAllCandidates() {
	cout << "Finding all candicates" << endl;
	//
	//candidates.clear();
	vector<int> c; //kandidati pre konkretne policko 0-80
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9 +j;
			for (size_t k = 1; k < 10; k++){
				if(gridMap[key]== 0){
					if (!checkIfInside(getRow(key), k)) {
						if (!checkIfInside(getColumn(key), k)) {
							if (!checkIfInside(getBox(key), k)) {
								c.push_back(k);
							}
						}
					}
				}
			}
			candidates[key] = c;
			c.clear();
		}
	}
	cout << "Found all candicates" << endl;

}

void Grid::addCandidate(int position, int candidate){
	vector<int> c;
	c = candidates[position];
	if(!checkIfInside(c, candidate)){
		c.push_back(candidate);
	}
	candidates[position] = c;
}

void Grid::removeCandidate(int position, int candidate){
	vector<int> cold, cnew;
	cold = candidates[position];
	if(cold.size() != 0){
		for(size_t i = 0; i < cold.size(); i++){
			if(cold[i] != candidate){
				cnew.push_back(cold[i]);
			}
		}
	}
	candidates[position] = cnew;
}

void Grid::rowRuleAllRows() {
	cout << "Finding all candicates for all rows" << endl;

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9 +j;
			vector<int> c, cRemove; //kandidati pre konkretne policko 0-80
			for (size_t k = 1; k < 10; k++){
				if(gridMap[key] == 0){
					if (!checkIfInside(getRow(key), k)) {
						c.push_back(k);
					}
					else{
						cRemove.push_back(k);
					}
				}
			}
			candidates[key] = c;
			candidatesToRemove[key] = cRemove;
		}
	}
}

void Grid::columnRuleAllColumns() {
	cout << "Finding all candicates for all columns" << endl;
	//candidates.clear();
	vector<int> c; //kandidati pre konkretne policko 0-80
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9 +j;
			vector<int> c; //kandidati pre konkretne policko 0-80
			for (size_t k = 1; k < 10; k++){
				if(gridMap[key] == 0){
					if (!checkIfInside(getColumn(key), k)) {
						c.push_back(k);
					}
				}
			}
			candidates[key] = c;
		}
	}
}

void Grid::boxRuleAllBoxes() {
	cout << "Finding all candicates for all boxes" << endl;
	//candidates.clear();
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9 +j;
			vector<int> c; //kandidati pre konkretne policko 0-80
			for (size_t k = 1; k < 10; k++){
				if(gridMap[key] == 0){
					if (!checkIfInside(getBox(key), k)) {
						c.push_back(k);
					}
				}
			}
			candidates[key] = c;
		}
	}
}

vector<int> Grid::checkForSingleCandidatesAndUpdateGrid(){
	vector<int> k;
	for (auto itr = candidates.begin(); itr != candidates.end(); ++itr) {
		int position = itr->first;
		int size = itr->second.size();
		if (size == 1){
	   		cout<< "Found one single candidate." << endl;
	   		auto c = itr->second.begin();
	   		k.push_back(position);
	   		k.push_back(int(*c));
	   	}
    }
	return k;
}

void Grid::findAllNakedPairs(){
    cout << "Finding all naked pairs" << endl;

    for (auto itr = candidates.begin(); itr != candidates.end(); ++itr) {
    	int size = itr->second.size();
    	if (size == 2){
    		int key = itr->first;
    		int kRow = key/9;
    		int kColumn = key%9;
    		int kBox = (key/3)%3 + 3*((key/9)/3);
    		//cout << "key: " << key << " kRow: " << kRow << " kColumn: " << kColumn << " kBox: " << kBox << endl;
    		if (checkIfInsideCandidates(getRowCandidates(kRow), itr->second, itr->first) != -1) {
    			cout<< "found match in row " + to_string(kRow) << endl;
    			int matchKey = checkIfInsideCandidates(getRowCandidates(kRow), itr->second, itr->first);
    			//itr->second.push_back(1); //1=row
    			nakedPairs[key] = itr->second;
    			nakedPairs[matchKey] = itr->second;
    		}
    		if (checkIfInsideCandidates(getColumnCandidates(kColumn), itr->second, itr->first) != -1) {
    			cout<< "found match in column " + to_string(kColumn) << endl;
    			int matchKey = checkIfInsideCandidates(getColumnCandidates(kColumn), itr->second, itr->first);
    			//itr->second.push_back(2); //2=column
    			nakedPairs[key] = itr->second;
    			nakedPairs[matchKey] = itr->second;
    		}
    		if (checkIfInsideCandidates(getBoxCandidates(kBox), itr->second, itr->first) != -1) {
    			cout<< "found match in box " + to_string(kBox) << endl;
    			int matchKey = checkIfInsideCandidates(getBoxCandidates(kBox), itr->second, itr->first);
    			//itr->second.push_back(3); //3=box
    			nakedPairs[key] = itr->second;
    			nakedPairs[matchKey] = itr->second;
    		}
    	}
    }
    if(nakedPairs.empty()){
    	cout << "Found none naked pair" << endl;
    }
}

void Grid::updateCandidatesByPair(){
	vector<int> pair;

	for (auto itr = nakedPairs.begin(); itr != nakedPairs.end(); ++itr) {
		int one = itr->second[0];
		int two = itr->second[1];
		int shape = itr->second[2];
		pair.push_back(one);
		pair.push_back(two);
		int key = itr->first;
		if(shape == 1){
				map<int, vector<int>> m;
				int k = key/9;
				m = getRowCandidates(k);
				for(auto it = m.begin(); it != m.end(); it++){
					if(!it->second.empty() && key != it->first){
						for(size_t i = 0; i < it->second.size(); i++){
							if(one == it->second.at(i) || two == it->second.at(i)){
								it->second.erase(it->second.begin()+i); //zostanu ostatni kandidati okrem naked pair
								auto search = candidates.find(it->first);
								candidates.erase(it->first);
								candidates.insert({search->first,it->second});
							}
						}
					}
					break;
				}
				candidates.erase(itr->first);
				candidates.insert({itr->first,pair});
				pair.clear();
			}
		if(shape == 2){
				map<int, vector<int>> m;
				int k = key%9;
				m = getColumnCandidates(k);
				for(auto it = m.begin(); it != m.end(); it++){
					if(!it->second.empty() && key != it->first){
						for(size_t i = 0; i < it->second.size(); i++){
							if(one == it->second.at(i) || two == it->second.at(i)){
								it->second.erase(it->second.begin()+i); //zostanu ostatni kandidati okrem naked pair
								auto search = candidates.find(it->first);
								candidates.erase(it->first);
								candidates.insert({search->first,it->second});
							}
						}
					}
					break;
				}
				candidates.erase(itr->first);
				candidates.insert({itr->first,pair});
				pair.clear();
			}
		if(shape == 3){
			map<int, vector<int>> m;
			int k = (key/3)%3 + 3*((key/9)/3);
			m = getBoxCandidates(k);
			for(auto it = m.begin(); it != m.end(); it++){
				if(!it->second.empty() && key != it->first){
					for(size_t i = 0; i < it->second.size(); i++){
						if(one == it->second.at(i) || two == it->second.at(i)){
							it->second.erase(it->second.begin()+i); //zostanu ostatni kandidati okrem naked pair
							auto search = candidates.find(it->first);
							candidates.erase(it->first);
							candidates.insert({search->first,it->second});
						}
					}
				}
				break;
			}
			candidates.erase(itr->first);
			candidates.insert({itr->first,pair});
			pair.clear();
		}
	}
}

void Grid::findAllHiddenPairs(){
	cout << "Finding all hidden pairs" << endl;

	map<int, vector<int>> k;

	for(auto itr = candidates.begin(); itr != candidates.end(); itr++){
		cout << itr->first << "\t";
		int size = itr->second.size();
		if (size == 2){
			cout<< "found one of sixe 2" << endl;
		}
	}
}

void Grid::print_map() {
	cout << "KEY\tELEMENT\n";
	for (auto itr = gridMap.begin(); itr != gridMap.end(); ++itr) {
		cout << itr->first << "\t" << itr->second << endl;
	}
}

void Grid::print_mapCandidates() {
	cout << "KEY\tELEMENT\n";
	for (auto itr = candidates.begin(); itr != candidates.end(); ++itr) {
		cout << itr->first << "\t";
		for (auto it = itr->second.begin(); it != itr->second.end(); it++){
			cout << *it << " ";
		}
		cout << endl;
	}
}

void Grid::print_mapNakedPairs() {
	cout << "KEY\tELEMENT\n";
	for (auto itr = nakedPairs.begin(); itr != nakedPairs.end(); ++itr) {
		cout << itr->first << "\t";
		for (auto it = itr->second.begin(); it != itr->second.end(); it++){
			cout << *it << " ";
		}
		cout << endl;
	}
}

void Grid::printEmptyGridSVG(){
	fstream file;
	file.open("emptyGrid.svg", ios::out | ios::trunc );
	if( !file ) {
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	file << "<svg version=\"1.1\"" << endl;
	file << "     baseProfile=\"full\"" << endl;
	file << "     width=\"500\" height=\"500\">" << endl;
	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:white;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"0,50 450,50\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,100 450,100\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,150 450,150\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"0,200 450,200\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,250 450,250\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,300 450,300\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"0,350 450,350\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,400 450,400\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"50,0 50,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"100,0 100,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"150,0 150,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"200,0 200,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"250,0 250,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"300,0 300,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"350,0 350,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"400,0 400,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;

	file << "</svg>" << endl;

	cout << endl << "wrting empty grid sudoku.svg file done." << endl;

	file.close();
}

void Grid::printGridSVG(string name){
	fstream file;
	file.open(name + ".svg", ios::out | ios::trunc );
	if( !file ) {
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	file << "<svg version=\"1.1\"" << endl;
	file << "     baseProfile=\"full\"" << endl;
	file << "     width=\"500\" height=\"500\">" << endl;
	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:white;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"0,50 450,50\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,100 450,100\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,150 450,150\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"0,200 450,200\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,250 450,250\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,300 450,300\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"0,350 450,350\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"0,400 450,400\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"50,0 50,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"100,0 100,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"150,0 150,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"200,0 200,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"250,0 250,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"300,0 300,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
	file << "  <polyline points=\"350,0 350,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
	file << "  <polyline points=\"400,0 400,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int key = i*9+j;
			if(gridMap[key] != 0){
				int x = 50*j + 16;
				int y = 50*i + 35;
				file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold\" font-size=\"30px\">" << gridMap[key] << "</text>" << endl;
			}
		}
	}

	file << "</svg>" << endl;

	cout << endl << "wrting " + name + " grid sudoku .svg file done." << endl;

	file.close();
}

void Grid::printSVG_candidates(string name) {

 	fstream file;
 	file.open(name + ".svg", ios::out | ios::trunc );
 	if( !file ) {
 		cerr << "Error: file could not be opened" << endl;
 		exit(1);
 	}

 	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
 	file << "<svg version=\"1.1\"" << endl;
 	file << "     baseProfile=\"full\"" << endl;
 	file << "     width=\"500\" height=\"500\">" << endl;
	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:white;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"0,50 450,50\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,100 450,100\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,150 450,150\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"0,200 450,200\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,250 450,250\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,300 450,300\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"0,350 450,350\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,400 450,400\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"50,0 50,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"100,0 100,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"150,0 150,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"200,0 200,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"250,0 250,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"300,0 300,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"350,0 350,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"400,0 400,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;

 	for (size_t i = 0; i < 9; i++) {
 		for (size_t j = 0; j < 9; j++) {
 			int key = i*9+j;
 			if(gridMap[key] == 0){
 				auto search = candidates.find(key); //konkretny element z mapy
 				int size = search->second.size(); //velkost vektora = pocet kadnidatov pre policko
 				auto it= search->second.begin();
 				int k;
 				for (it = search->second.begin(), k = 0; it != search->second.end() && k < size; it++, k++){ //iteraia na posuvanie suradnic medzi elementami konkretnych vektorov
 					k = int(k);
 					int x = 50*j + 8 + 12*k - 36*(k/3);
 					int y = 50*i + 20 + 13*(k/3);
 					file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold; fill:black\" font-size=\"15px\">" << *it << "</text>" << endl;
 				}
 			}
 			else{
 				int x = 50*j + 16;
 				int y = 50*i + 35;
 				file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold\" font-size=\"30px\">" << gridMap[key] << "</text>" << endl;
 			}
 		}
 	}

 	file << "</svg>" << endl;

 	cout << endl << "wrting candidates to .svg file done." << endl;
 	file.close();
}

void Grid::printSVG_nakedPairs(string name) {

 	fstream file;
 	file.open(name + ".svg", ios::out | ios::trunc );
 	if( !file ) {
 		cerr << "Error: file could not be opened" << endl;
 		exit(1);
 	}

 	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
 	file << "<svg version=\"1.1\"" << endl;
 	file << "     baseProfile=\"full\"" << endl;
 	file << "     width=\"500\" height=\"500\">" << endl;
	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:white;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"0,50 450,50\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,100 450,100\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,150 450,150\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"0,200 450,200\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,250 450,250\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,300 450,300\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"0,350 450,350\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"0,400 450,400\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"50,0 50,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"100,0 100,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"150,0 150,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"200,0 200,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"250,0 250,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"300,0 300,450\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
 	file << "  <polyline points=\"350,0 350,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;
 	file << "  <polyline points=\"400,0 400,450\" style=\"fill:none;stroke:black;stroke-width:1\" />" << endl;

 	for (size_t i = 0; i < 9; i++) {
 		for (size_t j = 0; j < 9; j++) {
 			int key = i*9+j;
 			if(gridMap[key] == 0){
 				auto search = candidates.find(key); //konkretny element z mapy
 				int size = search->second.size(); //velkost vektora = pocet kadnidatov pre policko
 				auto it= search->second.begin();
 				int k;
 				for (it = search->second.begin(), k = 0; it != search->second.end() && k < size; it++, k++){ //iteraia na posuvanie suradnic medzi elementami konkretnych vektorov
 					if (checkIfInsideNakedPairs(key, *it)){
 	 					k = int(k);
 	 					int x = 50*j + 8 + 12*k - 36*(k/3);
 	 					int y = 50*i + 20 + 13*(k/3);
 	 					file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold; fill:royalblue\" font-size=\"15px\">" << *it << "</text>" << endl;
 	 					continue;
 					}
 					k = int(k);
 					int x = 50*j + 8 + 12*k - 36*(k/3);
 					int y = 50*i + 20 + 13*(k/3);
 					file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold; fill:black\" font-size=\"15px\">" << *it << "</text>" << endl;
 				}
 			}
 			else{
 				int x = 50*j + 16;
 				int y = 50*i + 35;
 				file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold\" font-size=\"30px\">" << gridMap[key] << "</text>" << endl;
 			}
 		}
 	}

 	file << "</svg>" << endl;

 	cout << endl << "wrting candidates to .svg file done." << endl;
 	file.close();
}

void Grid::saveToFile(string filename) {

 	fstream file;

 	file.open(filename + ".csv", ios::out | ios::trunc );
 	if( !file ) {
 		cerr << "Error: file could not be opened" << endl;
 		exit(1);
 	}

 	for (size_t i = 0; i < 9; i++) {
 		for (size_t j = 0; j < 9; j++) {
 			int key = i*9+j;
 			file << gridMap[key] << ",";
 		}
 		file << endl;
 	}
 	cout << endl << "saving grid to .csv file done." << endl;
 	file.close();
}
