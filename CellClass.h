#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

class Cell{
private:
  int row; //riadok [1-3]
  int column; //stlpec [1-3]
  int value; //cislo [1-9]

public:
  Cell() {row = 0; column = 0; value = 0;}
  Cell(int r, int c, int v) {row = r; column = c; value = v;}

  void setRow(int r) {row = r;}
  void setColumn(int c) {column = c;}
  void setValue(int v) {value = v;}
  void setCell(int r, int c, int v) {row = r; column = c; value = v;}
  void setCell(Cell x) {
    row = x.getRow();
    column = x.getColum();
    value = x.getValue();
  }

  int getRow() {return row;}
  int getColum() {return column;}
  int getValue() {return value;}

  void printCell() {
      cout << "Row: " << row << " , Column: " << column << " , Value: " << value << endl;
  }
};
