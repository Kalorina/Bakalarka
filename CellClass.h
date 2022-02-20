#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include <functional>
#include <numeric>

using namespace std;

class Cell{
private:
  int row; //riadok [1-3]
  int column; //stlpec [1-3]
  int value; //cislo [1-9]
  int id; //stvorec [1-9]

public:
  Cell() {row = 0; column = 0; id = 0; value = 0;}
  Cell(int r, int c, int v, int Id) {row = r; column = c; value = v; id = Id;}

  void setRow(int r) {row = r;}
  void setColumn(int c) {column = c;}
  void setValue(int v) {value = v;}
  void setCell(int r, int c, int v) {row = r; column = c; value = v;}
  void setCell(Cell x) {
    row = x.getRow();
    column = x.getColum();
    value = x.getValue();
    id = x.getId();
  }

  int getRow() {return row;}
  int getColum() {return column;}
  int getValue() {return value;}

  void setId(int Id) {id = Id;}
  int getId() {return id;}

  void printCell() {
    for (int i = 0; i < 81; i++) {
      cout << "Row: " << row << " , Column: " << " , Value: " << value << " , ID:" << id << endl;
    }
  }
};
