#ifndef STATE_H
#define STATE_H

#include <vector>

class State
{
    private:
        std::vector<int> board;
        int n; // represents the size of the board
        int blank; // represents the position of the empty tile
        std::vector<int> moves; // holds the moves
    public:
        State(int);
        ~State();
        bool move(int, State);
        void printState();
};



#endif