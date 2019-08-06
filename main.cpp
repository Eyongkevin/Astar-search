#include<vector>
#include "Astar.cpp"

int main() {
  // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
  auto board = Util::ReadBoardFile("board");
  // TODO: Call Search with "board", "init", and "goal". Store the results in the variable "solution".
  int init[2]{0,0};
  int goal[2]{4,8};
  Astar astar;
  vector<vector<State>> solution = astar.Search(board, init, goal);
  astar.ConstructFinalPath(init, goal, board);
  Util::PrintFinalBoard(board, astar.getFinalVisitedIndices(), init, goal);

}