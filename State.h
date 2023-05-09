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
        State(int, std::vector<int>);
        ~State();
        void createBoard(std::vector<int>&);
        bool move(int, State&);
        void printState();
        bool check();
        const int getMoves();
        void setMisplaced();
        const int getMisplaced();
        void setEuclidean();
        const double getEuclidean();
        void solveUniform();
        void solveMisplaced();
        void solveEuclidean();
        void printSolution(std::vector<int>&);

};


#endif