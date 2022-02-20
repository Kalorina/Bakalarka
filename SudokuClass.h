#include "BoxClass.h"

class Sudoku{
private:
  vector<Box> box; //[1-9]

public:
  Sudoku() {}
  Sudoku(vector<Box> b) {box = b;}

  void setSudoku(vector<Box> b) {box = b;}

  vector<Box> getSudoku() {return box;}


};
