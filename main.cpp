#include <iostream>
#include "State.h"
#include <vector>
#include <queue>

int main()
{
    State curr(3);
    // std::cout << curr.check() << std::endl;
    // curr.printState();
    curr.move(3, curr);
    // curr.move(3, curr);
    curr.move(0, curr);
    curr.move(1, curr);
    curr.move(2, curr);
    curr.solveUniform();
}