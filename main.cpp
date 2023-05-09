#include <iostream>
#include "State.h"
#include <vector>
#include <queue>
#include <iostream> 

int main()
{
    int option = 0; 
    int dim = 0; 
    int curr = 0; 
    std::vector<int>board; 
    std::cout << "Welcome to our puzzle! Please enter 1 for a hard-coded puzzle, or 2 to enter your own values." << std::endl; 
    std::cin >> option; 
    if (option == 1){
        State curr(3);
        // std::cout << curr.check() << std::endl;
        // curr.printState();
        curr.move(3, curr);
        // curr.move(3, curr);
        curr.move(0, curr);
        curr.move(1, curr);
        curr.move(2, curr);
        std::cout << "Please enter which way you would like to solve the puzzle (1: euclidean, 2: misplaced, 3: uniform):" << std::endl; 
        std::cin >> option; 
        if (option == 1){
            curr.solveEuclidean(); 
        }
        else if (option == 2){
            curr.solveMisplaced();
        } else {
            curr.solveUniform(); 
        }
    }
    if (option == 2){

        std::cout << "Please enter the dimensions of your puzzle (min: 2)." << std::endl; 
        std::cin >> dim; 
        board.reserve(dim*dim); 
        for (int i = 0; i < dim * dim; ++i)
            {
                std::cout << "Please enter a number (-1 for an empty tile): " << std::endl; 
                std::cin >> curr;                 
                board.push_back(curr); 
            }

        State bingbong(dim, board); 
        std::cout << "Please enter which way you would like to solve the puzzle (1: euclidean, 2: misplaced, 3: uniform):" << std::endl; 
        std::cin >> option; 
        if (option == 1){
            bingbong.solveEuclidean(); 
        }
        else if (option == 2){
            bingbong.solveMisplaced();
        } else {
            bingbong.solveUniform(); 
        }
     }
// mystery testing option
    if (option == 3){
        std::vector<int>vec = {8, 7, 1, 6, -1, 2, 5, 4, 3}; 
        State pur(3,vec);

        pur.solveUniform(); 
        // pur.solveEuclidean(); 
        // pur.solveMisplaced();  
    }

     return 0; 


}