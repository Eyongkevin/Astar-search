#ifndef UTIL_HEADER_H
#define UTIL_HEADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include<unistd.h>


using namespace std;

class Util{
    public:
    static vector<State> ParseLine(string line);
    static vector<vector<State>> ReadBoardFile(string path); 
    static bool CheckValidCell(int x, int y,vector<vector<State>>& grid );
    static bool const Compare(vector<int> node1, vector<int> node2);
    static void CellSort(vector<vector<int>> *v);
    static string CellString(State cell);
    static void PrintBoard(const vector<vector<State>> board);
    static void PrintFinalBoard(const vector<vector<State>> grid, vector<vector<int>> finalPathIndices, int init[2], int goal[2]);
    
};


vector<State> Util::ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> Util::ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}


// TODO: Write the CheckValidCell function
bool Util::CheckValidCell(int x, int y,vector<vector<State>>& grid ){
  if(((x >= 0 && x < grid.size()) && (y >= 0 && y < grid[0].size())) && (grid[x][y] == State::kEmpty || grid[x][y] == State::kFinish)){
    return true;
  }
  return false;

}
// TODO: Write the Compare function here
bool const Util::Compare(vector<int> node1, vector<int> node2){
    int f1 = node1[2] + node1[3];  //f1 = g1 + h1
    int f2 = node2[2] + node2[3];  //f2 = g2 + h2
    return f1 > f2;
}

// Sort the two-dimentional vector of ints in descending order
void Util::CellSort(vector<vector<int>> *v){
    sort(v->begin(), v->end(), Compare);
}

string Util::CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    case State::kFinish: return "🏁   ";
    default: return "0   "; 
  }
}


void Util::PrintBoard(const vector<vector<State>> board) {
  system("clear");
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

void Util::PrintFinalBoard(vector<vector<State>> grid, vector<vector<int>> finalPathIndices, int init[2], int goal[2]){
  //system("clear");
  cout<<"\n\nPrinting the final path\n---------------\n\n"<<endl;
  usleep(1000000);
  for(vector<int> idx: finalPathIndices){
        grid[idx[0]][idx[1]] = State::kPath;
        grid[init[0]][init[1]] = State::kStart;
        grid[goal[0]][goal[1]] = State::kFinish;
        Util::PrintBoard(grid);
        usleep(1000000);
      }
      
}


#endif