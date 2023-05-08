#ifndef STATE_H
#define STATE_H

#include <vector>

class State
{
    private:
        std::vector<int> board;
        int n; // represents the size of the board
        int blank; // represents the position of the empty tile
    public:
        std::vector<int> moves; // holds the moves
        State(int);
        State(const State&);
        ~State();
        bool move(int, State&);
        void printState();
        bool check();
        int getMoves();
        void solveUniform();
};


#endif