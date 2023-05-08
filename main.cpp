#include <iostream>
#include "State.h"

int main()
{
    State curr(3);
    // std::cout << curr.check() << std::endl;
    curr.printState();
    curr.move(3, curr);
    curr.printState();
    // State newState(curr);
    // curr.move(3, newState);
    // newState.printState();
    curr.solveUniform();
}