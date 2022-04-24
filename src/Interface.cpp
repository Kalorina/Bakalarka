/*
 * Interface.cpp
 *
 *  Created on: Apr 23, 2022
 *      Author: karoli
 */

#include "Interface.h"


Game::Game(string filename){

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

	sudoku = Grid(grid);
	hint = -1;

}

void Game::runGame() {
	cout << "Game started" << endl;

	cout << "Enter a filename for sudoku: ";
	string filename;
	cin >> filename;

	sudoku.setUpFromFile(filename);

	string name;
	cout << "Name of your game: ";
	cin >> name;

	cout << "Yours grid:" << endl;
	sudoku.printGrid();
	sudoku.printGridSVG(name);

	do{
		cout << "Yours options:" << endl;
		cout << "1. Add a number to grid." << endl;
		cout << "2. Show candidates for all rows." << endl;
		cout << "3. Show candidates for all column." << endl;
		cout << "4. Show candidates for all 3x3 box." << endl;
		cout << "5. Show all candidates." << endl;
		cout << "6. End game." << endl;

		cout << "Enter number of your choice: ";
		cin >> hint;
		if (hint <= 0 || hint > 6){
			cout << "wrong number, please enter again: " << endl;
			cin >> hint;
		}

		if(hint == 1) {
			cout << "Enter number to add to your grid (1-9): ";
			int number;
			cin >> number;
			if (number < 1 || number > 9){
				cout << "wrong number, please enter again: " << endl;
				cin >> number;
			}

			cout << "Enter row number(1-9): ";
			int row;
			cin >> row;
			if (row < 1 || row > 9){
				cout << "wrong number for row, please enter again: " << endl;
				cin >> row;
			}

			cout << "Enter column number(1-9): ";
			int column;
			cin >> column;
			if (column < 1 || column > 9){
				cout << "wrong number for column, please enter again: " << endl;
				cin >> column;
			}
			int key = (column-1) + 9*(row-1);
			sudoku.updateGrid(key, number);
			cout << endl;
			sudoku.printGrid();
			sudoku.printGridSVG(name);
			cout << "Your Game " + name + " was updated with new number in the grid" << endl;
		}
		if(hint == 2) {
			sudoku.rowRuleAllRows();
			sudoku.printSVG_candidates(name);
			cout << "Your Game " + name + " was updated with candidates for all rows" << endl;
		}
		if(hint == 3) {
			sudoku.columnRuleAllColumns();
			sudoku.printSVG_candidates(name);
			cout << "Your Game " + name + " was updated with candidates for all columns" << endl;
		}
		if(hint == 4) {
			sudoku.boxRuleAllBoxes();
			sudoku.printSVG_candidates(name);
			cout << "Your Game " + name + " was updated with candidates for all 3x3 boxes" << endl;
		}
		if(hint == 5) {
			sudoku.findAllCandidates();
			sudoku.printSVG_candidates(name);
			cout << "Your Game " + name + " was updated with all candidates" << endl;
		}
		if(hint == 6) {
			sudoku.printGridSVG(name);
			cout << "Your Game " + name + " ended" << endl;
			break;
		}
		if(sudoku.checkIfSolved()){
			cout << "Your Game " + name + " is solved" << endl;
			sudoku.printGrid();
			sudoku.printGridSVG(name);
			break;
		}
	}
	while(!sudoku.checkIfSolved());


	cout << "Game ended" << endl;
}
