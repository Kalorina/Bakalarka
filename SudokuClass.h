#include "BoxClass.h"

class Sudoku{
private:
  vector<Box> box; //[1-9]

public:
  Sudoku() {}
  Sudoku(vector<Box> b) {box = b;}

  void setSudoku(vector<Box> b) {box = b;}
  vector<Box> getSudoku() {return box;}

  void printSudoku(){
    for (size_t i = 0; i < 9; i++) {
      cout << "-";
    }
    cout << endl;
    for (size_t i = 0; i < 9; i++) {
      for (size_t j = 0; j < 3; j++) {
        cout << "||";
        box[i].printRow(j);
        if (i % 3 == 2) {
          cout << "||" << endl;
        }
        if(i % 3 == 2 || i == 0){
          cout << endl;
          for (size_t k = 0; k < 9; k++) {
            cout << "-";
          }
          cout << endl;
        }
      }
    }
  }

  void printRow(int n){
    for (size_t i = 0; i < 3; i++) {
      if (n > (-1) && n<3) {
        box[i].printRow(n % 3);
      }
      if (n>2 && n<6) {
        box[i+3].printRow(n % 3);
      }
      if (n>5 && n<9) {
        box[i+6].printRow(n % 3);
      }
    }
  }

  void printColumn(int n){
    for (size_t i = 0; i < 3; i++) {
      if (n > (-1) && n<3) {
        box[i].printColumn(n % 3);
      }
      if (n>2 && n<6) {
        box[i*3+1].printColumn(n % 3);
      }
      if (n>5 && n<9) {
        box[i*3+2].printColumn(n % 3);
      }
    }
  }

  void generateSudoku(){

  }

};
