#ifndef ASTAR_HEADER_H
#define ASTAR_HEADER_H
#include<vector>

using namespace std;

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};


class Astar{

    public:
        int Heuristic(int x1, int y1, int x2, int y2);
        void AddToOpen(int x, int y, int g, int h, vector<vector<int>>& openNodes, vector<vector<State>>& grid);
        void ExpandNeighbors(vector<int>& node,  int goal[2], vector<vector<int>>& open, vector<vector<State>>& grid);
        vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]);
        void ConstructFinalPath(int init[2], int goal[2], vector<vector<State>> grid);
        void printVisitedIndices();
        vector<vector<int>> getFinalVisitedIndices();
        

    private:
        // directional deltas 2D array used to find visited path
        const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        vector<vector<int>> VisitedIndices{};
        vector<vector<int>> finalPathIndices{};
        // Directional delta vector used to find final path from start to target.
        vector<vector<int>> delta2 = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        

};
#endif

