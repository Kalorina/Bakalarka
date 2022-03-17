#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Grid{
private:
  vector<vector<int>> grid;

public:
  Grid();
  Grid(vector<vector<int>> g) {grid=g;}

  void setGrid(vector<vector<int>> g) {grid=g;}

  void printGrid(){
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

  void printSVG(){

    fstream file;
    file.open("sudokuPrint.svg", ios::out | ios::trunc );
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

    cout << endl << "wrting svg file done." << endl;

    file.close();
  }

};
