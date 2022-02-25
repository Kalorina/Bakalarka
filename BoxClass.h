#include "CellClass.h"

class Box {
private:
  vector<Cell> cell; //stvorec [1-9]
  int id;

public:
  Box() {id = 0;}
  Box(vector<Cell> b, int Id)  {cell = b; id = Id;}

  void setBox(vector<Cell> c) { cell = c;}
  void setBox(Box x) { cell = x.getBox(); id = x.getIdBox();}
  void setID(int Id) {id = Id;}

  vector<Cell> getBox() {return cell;}
  Cell getCellFromBox(int n) {return cell[n];}
  int getIdBox() {return id;}

  void printBox() {
    cout << "ID: " << id << endl;
    for (size_t i = 0; i < cell.size(); i++) {
      cell[i].printCell();
    }
  }
  void printRow(int n){
    cout << "|";
    for (int i = 0; i < 3; i++) {
      cout << cell[i+3*n].getValue() << "|";
    }
  }
  void printColumn(int n){

    for (int i = 0; i < 3; i++) {
      cout << cell[3*i+n].getValue() << endl;
    }
  }
  void printBoxByRow(){

    for (int i = 0; i < 3; i++) {
      printRow(i);
    }
    cout << endl;
  }

};
