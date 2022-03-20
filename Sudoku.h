#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Grid{
private:
  vector<vector<int>> grid;

public:
  Grid();
  Grid(vector<vector<int>> g) {grid=g;}

  void setGrid(vector<vector<int>> g) {grid=g;}
  vector<vector<int>> getGrid() { return grid; }
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
  vector<int> getRow(int k) {return grid[k];}
  vector<int> getColumn(int k){
    vector<int> column;
    for (size_t i = 0; i < grid.size(); i++) {
      column.push_back(grid[i][k]);
    }
    return column;
  }
  vector<int> getBox(int k, int l){
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
  bool checkIfInside(vector<int> vector, int value){
    for (size_t i = 0; i < vector.size(); i++) {
      if (vector[i] == value) {
        return true;
      }
    }
    return false;
  }
  int getValue(int i, int j){return grid[i][j];}

  map<int, vector<int>> addCandidateToMap(map<int, vector<int>> mp, int position, int value){
    //int key;
    vector<int> candidates;

    //ak je uplne prazdna, vlozim 1. key-value element
    if (mp.empty() == true){
      candidates.push_back(value);
      mp.insert({position, candidates});
      return mp;
    }

    candidates = mp.at(position);

    //ak nieje uplne prazdna, ale taky key-value element este nieje
    if(candidates.empty()){
      candidates.push_back(value);
      mp.insert({position, candidates});
      return mp;
    }
    //ak key-value element existuje, updatne ho
    if (!candidates.empty()){
      candidates.push_back(value);
      mp[position] = candidates;
      return mp;
    }
    return mp;
  }

};
