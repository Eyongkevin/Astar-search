#include "Astar.h"
#include "Util.h"

using namespace std;



// TODO: Write the Heuristic function here.
int Astar::Heuristic(int x1, int y1, int x2, int y2){
    // Manhattan distance between two line is the absolut 
    // differences between points in the line.
    return abs(x2-x1) + abs(y2-y1);
}

// TODO: Write the AddToOpen function here
void Astar::AddToOpen(int x, int y, int g, int h, vector<vector<int>>& openNodes, vector<vector<State>>& grid){
    vector<int> node = {x, y, g, h};
    openNodes.push_back(node);
    grid[x][y] = State::kClosed;
}

// TODO: Write the ExpandNeighbors function
void Astar::ExpandNeighbors(vector<int>& node,  int goal[2], vector<vector<int>>& open, vector<vector<State>>& grid){
  // Get current node's data
  // Loop through current node's potential neighbors
    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed
    // Increment g value, compute h value, and add neighbor to open list.
  // end loop

    int x = node[0];
    int y = node[1];
    int g = node[2];

    // Find size(number of rows) for a 2D array
    int delta_size = sizeof(delta)/sizeof(delta[0]);

    for(int i=0; i < delta_size; i++){
      int x1 = x + delta[i][0];
      int y1 = y + delta[i][1];

      if(Util::CheckValidCell(x1, y1,grid)){
        int g1 = g + 1;
        int h = Heuristic(x1, y1, goal[0], goal[1]);
        AddToOpen(x1, y1, g1, h, open, grid);
      }
    }


}

// TODO: Write the Search function stub here.
vector<vector<State>> Astar::Search(vector<vector<State>> grid, int init[2], int goal[2]){
     
     vector<vector<int>> open{};
     int x = init[0];
     int y = init[1];
     int g = 0;
     int h = Astar::Heuristic(x, y, goal[0], goal[1]);
     AddToOpen(x, y, g, h, open, grid);

    // TODO: Sort the open list using CellSort, and get the current node.
    // TODO: Get the x and y values from the current node,
    // and set grid[x][y] to kPath.

    // TODO: Check if you've reached the goal. If so, return grid.
    // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
    // ExpandNeighbors
    // TODO: End while loop
    
    // We've run out of new nodes to explore and haven't found a path.
     while(!open.empty()){
         Util::CellSort(&open);

         auto currentNode = open.back();
         open.pop_back();
         x = currentNode[0];
         y = currentNode[1];
         grid[x][y] = State::kPath;
         grid[init[0]][init[1]] = State::kStart;
         grid[goal[0]][goal[1]] = State::kFinish;

         vector<int> visitedIndex = {x, y};
         VisitedIndices.push_back(visitedIndex);

         if(x == goal[0] && y == goal[1]){
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            

            return grid;
         } 
         Util::PrintBoard(grid);
         ExpandNeighbors(currentNode, goal, open, grid);
         usleep(1000000);

     }

     cout<<"No path found!"<<endl;
     return vector<vector<State>>{};
}

// TODO: construct the final path for the shortest path from destination to target.
void Astar::ConstructFinalPath(int init[2], int goal[2], vector<vector<State>> grid)
{
    // Initially consider first item of VisitedIndices(starter) to be beginning of final path
    finalPathIndices.push_back(VisitedIndices[0]);
    int count = 0;
    // Loop through the vector of indices
    for(; count+1 < VisitedIndices.size(); count++){
      // Find the difference between two adjecent points. The difference should be part of the delta2.
      vector<int> holdIdx = {VisitedIndices[count+1][0] - VisitedIndices[count][0], VisitedIndices[count+1][1] - VisitedIndices[count][1]};

      if(find(delta2.begin(), delta2.end(), holdIdx) != delta2.end()){
        // If the difference vector exist 
        finalPathIndices.push_back(VisitedIndices[count+1]);
      }else{
        // if the difference vector doesn't exist
      int backCount = count;
      while(backCount > 0){
          // compare present point to previous points for a match
          holdIdx = {VisitedIndices[backCount-1][0] - VisitedIndices[count + 1][0], VisitedIndices[backCount-1][1] - VisitedIndices[count+1][1]};
          

          // If a match is found, find its index, then move all elements from that index(inclusive) to a temporary vector
          // Then add the present value that was used for matching.
          // if {1,3,5,7,9,4} and '4' is the present and matches with '7',
          // we get '7' index which is '3', then we add {1,3,5,7} to a temporary vector, then add 4 as {1,3,5,7,4}.
          if(find(delta2.begin(), delta2.end(), holdIdx) != delta2.end()){
              vector<vector<int>>::iterator it = find(finalPathIndices.begin(), finalPathIndices.end(), VisitedIndices[backCount-1]);
              if(it != finalPathIndices.end()){
                  vector<vector<int>> tem_visitedIdx{};
                  int index = distance(finalPathIndices.begin(), it)+1;
                  for(vector<int> vec: finalPathIndices){
                      if(index <= 0){
                          finalPathIndices = tem_visitedIdx;
                          break;
                      } 
                      tem_visitedIdx.push_back(vec);
                      index--;
                  }

                  }
              break;
          }
              backCount--;
          }       
          // add the present
          finalPathIndices.push_back(VisitedIndices[count+1]);
      }

      }
    
}

void Astar::printVisitedIndices()
{
  for(auto i: VisitedIndices){
    cout<<"{ ";
    for(int j: i){
      cout<<j<<", ";
    }
    cout<<"}"<<endl;

  }

}
vector<vector<int>> Astar::getFinalVisitedIndices(){
  return finalPathIndices;
}
