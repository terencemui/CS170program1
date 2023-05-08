#ifndef STATE_H
#define STATE_H

#include <vector>
#include <queue>

class State
{
    private:
        std::vector<int> board;
        int n; // represents the size of the board
        int blank; // represents the position of the empty tile
        std::vector<int> moves; // holds the moves
        int misplaced = 0;
        double euclidean = 0;
    public:
        State(int);
        State(const State&);
        ~State();
        bool move(int, State&);
        void printState();
        bool check();
        const int getMoves();
        void setMisplaced();
        const int getMisplaced();
        void setEuclidean();
        const double getEuclidean();
        void solveUniform(std::vector<int>&);
        void solveMisplaced(std::vector<int>&);
        void solveEuclidean(std::vector<int>&);
};


#endif