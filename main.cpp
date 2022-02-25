#include "SudokuClass.h"

using namespace std;

int genRandNum(int max){
  return rand()%max;
}

vector<Cell> fillCellsVector(vector<Cell> cells){

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int v = genRandNum(9);
      Cell c(i, j, v);
      cells.push_back(c);
    }
  }
  return cells;
}

void printCells(vector<Cell> cells){
  for (size_t i = 0; i < cells.size(); i++) {
    cells[i].printCell();
  }
}

Box fillBox(vector<Cell> cells){
  Box box;
  box.setBox(cells);
  box.setID(1);
  return box;
}

vector<Box> fillBoxes(){

  vector<Cell> box;
  vector<Box> boxes;
  for (size_t i = 0; i < 9; i++) {
    box = fillCellsVector(box);
    Box b; b.setBox(box);
    boxes.push_back(b);
  }
  return boxes;
}

void printBoxes(vector<Box> boxes){
  for (size_t i = 0; i < boxes.size(); i++) {
    cout << i << endl;
    boxes[i].printBoxByRow();
    cout << endl;
  }
}

void printSVG( Sudoku puzzle, string path=""){
  string fileName = path + "svgHead.txt";
  ifstream file1(fileName.c_str());
  stringstream svgHead;
  svgHead << file1.rdbuf();

  ofstream outFile("sudokuPuzzle.svg");
  outFile << svgHead.rdbuf();

  int grid[9][9];

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      Box b = puzzle.getBoxFromSudoku(j);
      Cell c = b.getCellFromBox(j);
      grid[i][j] = c.getValue();
    }
  }

  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(grid[i][j]!=0)
      {
        int x = 50*j + 16;
        int y = 50*i + 35;

        stringstream text;
        text<<"<text x=\""<<x<<"\" y=\""<<y<<"\" style=\"font-weight:bold\" font-size=\"30px\">"<<grid[i][j]<<"</text>\n";

        outFile << text.rdbuf();
      }
    }
  }

  outFile << "<text x=\"50\" y=\"500\" style=\"font-weight:bold\" font-size=\"15px\">Difficulty Level (0 being easiest): "                  <<5<<"</text>\n";
  outFile << "</svg>";

}

int main(int argc, char const *argv[]) {

srand(time(NULL)); //for generating random number

/*
  vector<Cell> cells;
  //Box box1;

  //cells = fillCellsVector(cells);
  //printCells(cells);
  //box1 = fillBox(cells);
  //box1.printBoxByRow();
*/

  vector<Box> boxes;

  boxes = fillBoxes();
  //printBoxes(boxes);

  Sudoku puzzle;
  puzzle.setSudoku(boxes);
  puzzle.printSudoku();

  string rem = "sudokuGen";
  string path = argv[0];
  path = path.substr(0,path.size() - rem.size());
  printSVG(puzzle, path);
  cout<<"The above sudoku puzzle has been stored in puzzles.svg in current folder\n";

}
