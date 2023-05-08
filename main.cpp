#include <iostream>
#include "State.h"
#include <vector>
#include <queue>

int main()
{
    State curr(4);
    std::vector<int> solution;
    // std::cout << curr.check() << std::endl;
    curr.printState();
    curr.move(3, curr);
    curr.move(0, curr);
    curr.move(1, curr);
    curr.move(2, curr);
    // curr.move(3, curr);
    curr.printState();
    curr.setEuclidean();
    std::cout << curr.getEuclidean() << std::endl;
    // State newState(curr);
    // curr.move(3, newState);
    // newState.printState();
    // curr.solveEuclidean(solution);
}