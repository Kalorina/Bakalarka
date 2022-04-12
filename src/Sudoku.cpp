/*
 * Sudoku.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: karoli
 */

#include "Sudoku.h"

void Grid::updateGrid(int position, int candidate){ //pri 3 zakladnych pravidlach
	for (size_t i = 0; i < 9; i++) {
	    for (size_t j = 0; j < 9; j++) {
			int p = i*9+j;
			if(p == position){
				grid[i][j] = candidate;
				candidates.clear();
			}
		}
	}
}

void Grid::printGrid(){
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
	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
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
	file.open("original_" + name + ".svg", ios::out | ios::trunc );
	if( !file ) {
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	file << "<svg version=\"1.1\"" << endl;
	file << "     baseProfile=\"full\"" << endl;
	file << "     width=\"500\" height=\"500\">" << endl;
	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
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
			if(grid[i][j] != 0){
				int x = 50*j + 16;
				int y = 50*i + 35;
				file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold\" font-size=\"30px\">" << grid[i][j] << "</text>" << endl;
			}
		}
	}

	file << "</svg>" << endl;

	cout << endl << "wrting " + name + " grid sudoku .svg file done." << endl;

	file.close();
}

vector<int> Grid::getColumn(int k){
	vector<int> column;
	for (size_t i = 0; i < grid.size(); i++) {
		column.push_back(grid[i][k]);
	}
	return column;
}

vector<int> Grid::getBox(int k, int l){
	vector<int> box;
    //b=0-8, pricom 0->lavyhorny a 8->pravydolny a po riadkoch
	int b = (k/3)*3 + l/3;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if ((i/3)*3 + j/3 == b) {
				box.push_back(grid[i][j]);
				//cout << "i: " << i << " j: " << j << endl;
			}
			//box.push_back(grid[i+(b/3)*3][j+(b%3)*3]); //pozor toto je mozno optimalnejsie, ale treba ist cez 0-3 cyklus, nie 0-9 oba.
			//cout << "i: " << i+(b/3)*3 << " j: " << j+(b%3)*3 << endl;
		}
	}
	return box;
}

map<int, vector<int>> Grid::getRowCandidates(int k){
	map<int, vector<int>> row;
	int key;
	for(size_t i = 0; i < 9; i++){
		key = i + (9 * k);
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
    //b=0-8, pricom 0->lavyhorny a 8->pravydolny a po riadkoch
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

int Grid::checkIfInsideCandidates(map<int, vector<int>> m, vector<int> vector, int key) {
	int k = -1;
	for (auto itr = m.begin(); itr != m.end(); ++itr) {
		if (itr->first != key && vector == itr->second){
			k = itr->first;
			return k;
		}
	}
	return k;
}

void Grid::findAllCandidates() {
	cout << "Finding all candicates" << endl;
	vector<int> c; //kandidati pre konkretne policko 0-80
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			for (size_t k = 1; k < 10; k++){
				if(grid[i][j] == 0){
					if (!checkIfInside(getRow(i), k)) {
						//cout << "Row: " << i << " Value: " << j << endl;
						if (!checkIfInside(getColumn(j), k)) {
							//cout << "Column: " << j << " Value: " << j << endl;
							if (!checkIfInside(getBox(i,j), k)) {
								//cout << "Box: " << j << " Value: " << j << endl;
								c.push_back(k);
							}
						}
					}
				}
			}
			candidates.insert({i*9+j, c});
			c.clear();
		}
	}
	cout << "Found all candicates" << endl;
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
    			itr->second.push_back(1); //1=row
    			nakedPairs.insert({key,itr->second});
    			nakedPairs.insert({matchKey, itr->second});
    		}
    		if (checkIfInsideCandidates(getColumnCandidates(kColumn), itr->second, itr->first) != -1) {
    			cout<< "found match in column " + to_string(kColumn) << endl;
    			int matchKey = checkIfInsideCandidates(getColumnCandidates(kColumn), itr->second, itr->first);
    			itr->second.push_back(2); //2=column
    			nakedPairs.insert({key,itr->second});
    			nakedPairs.insert({matchKey, itr->second});
    		}
    		if (checkIfInsideCandidates(getBoxCandidates(kBox), itr->second, itr->first) != -1) {
    			cout<< "found match in box " + to_string(kBox) << endl;
    			int matchKey = checkIfInsideCandidates(getBoxCandidates(kBox), itr->second, itr->first);
    			itr->second.push_back(3); //3=box
    			nakedPairs.insert({key,itr->second});
    			nakedPairs.insert({matchKey, itr->second});
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

void Grid::printSVG_candidates(string name) {

 	fstream file;
 	file.open("AllCandidates" + name + ".svg", ios::out | ios::trunc );
 	if( !file ) {
 		cerr << "Error: file could not be opened" << endl;
 		exit(1);
 	}

 	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
 	file << "<svg version=\"1.1\"" << endl;
 	file << "     baseProfile=\"full\"" << endl;
 	file << "     width=\"500\" height=\"500\">" << endl;
 	file << "  <polyline points=\"0,0 450,0 450,450 0,450 0,0\" style=\"fill:none;stroke:black;stroke-width:5\" />" << endl;
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

 	for (size_t i = 0; i < grid.size(); i++) {
 		for (size_t j = 0; j < grid[i].size(); j++) {
 			if(grid[i][j] == 0){
 				int key = i*9+j;
 				auto search = candidates.find(key); //konkretny element z mapy
 				int size = search->second.size(); //velkost vektora = pocet kadnidatov pre policko
 				auto it= search->second.begin();
 				int k;
 				for (it = search->second.begin(), k = 0; it != search->second.end() && k < size; it++, k++){ //iteraia na posuvanie suradnic medzi elementami konkretnych vektorov
 					k = int(k);
 					int x = 50*j + 8 + 12*k - 36*(k/3);
 					int y = 50*i + 25 + 15*(k/3);
 					file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold; fill:blue\" font-size=\"15px\">" << *it << "</text>" << endl;
 				}
 			}
 			else{
 				int x = 50*j + 16;
 				int y = 50*i + 35;
 				file << "<text x=\"" << x << "\" y=\"" << y << "\" style=\"font-wight:bold\" font-size=\"30px\">" << grid[i][j] << "</text>" << endl;
 			}
 		}
 	}

 	file << "</svg>" << endl;

 	cout << endl << "wrting candidates .svg file done." << endl;
 	file.close();
}
