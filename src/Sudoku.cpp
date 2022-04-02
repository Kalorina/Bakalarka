/*
 * Sudoku.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: karoli
 */

#include "Sudoku.h"

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

void Grid::printSVG(){
	fstream file;
	file.open("sudokuOriginal.svg", ios::out | ios::trunc );
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

	cout << endl << "wrting sudoku .svg file done." << endl;

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
    //b=0-8, prisom 0->lavyhorny a 8->pravydolny a po riadkoch
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

bool Grid::checkIfInside(vector<int> vector, int value) {
    for (size_t i = 0; i < vector.size(); i++) {
    	if (vector[i] == value) {
    		return true;
    	}
    }
    return false;
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
}

void Grid::print_map() {
	cout << "KEY\tELEMENT\n";
	for (auto itr = candidates.begin(); itr != candidates.end(); ++itr) {
		cout << itr->first << "\t";
		for (auto it = itr->second.begin(); it != itr->second.end(); it++){
			cout << *it << " ";
		}
		cout << endl;
	}
}

void Grid::printSVG_candidates() {

 	fstream file;
 	file.open("sudokuAllCandidates.svg", ios::out | ios::trunc );
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
 				auto it = search->second.begin();
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
