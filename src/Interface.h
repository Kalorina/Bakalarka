/*
 * Interface.h
 *
 *  Created on: Apr 23, 2022
 *      Author: karoli
 */
#include "Sudoku.h"

using namespace std;

class Game{
private:
	Grid sudoku;
	int hint;
public:
	Game() {hint = -1, sudoku = Grid();}
	Game(string filename);

	void runGame();
};

