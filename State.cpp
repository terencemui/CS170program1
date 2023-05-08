#include "State.h"
#include <iostream>

State::State(int n)
{
    this->n = n;
    board.reserve(n);
    for (int i = 0; i < n*n - 1; ++i)
    {
        board[i] = i + 1;
    }
    board[n*n - 1] = -1;
    blank = n*n - 1;
}

State::~State()
{
}

bool State::move(int direction, State newState)
{
    // 0, 1, 2, 3 -> N, E, S, W

    if (direction == 0) // N
    {
        if (blank < n)
        {
            return false;
        }
        else
        {
            newState.moves.push_back(direction);
            newState.board.at(blank) = newState.board.at(blank - n);
            newState.board.at(blank - n) = -1;
            return true;
        }
    }
    else if (direction == 1)
    {
        if (blank % n == (n - 1))
        {
            return false;
        }
        else
        {
            newState.moves.push_back(direction);
            newState.board.at(blank) = newState.board.at(blank + 1);
            newState.board.at(blank + 1) = -1;
            return true;
        }
    }
    else if (direction == 2)
    {
        if (blank >= (n * n - n))
        {
            return false;
        }
        else
        {
            newState.moves.push_back(direction);
            newState.board.at(blank) = newState.board.at(blank + n);
            newState.board.at(blank + n) = -1;
            return true;
        }
    }
    else if (direction == 3)
    {
        if (blank % n == 0)
        {
            return false;
        }
        else
        {
            newState.moves.push_back(direction);
            newState.board.at(blank) = newState.board.at(blank - 1);
            newState.board.at(blank - 1) = -1;
            return true;
        }
    }
    else
    {
        std::cout << "Invalid direction " << std::endl;
        return false;
    }
}

void State::printState()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (board[i * n + j] != -1)
            {
                std::cout << board[i * n + j] << " ";
            }
            else
            {
                std::cout << "* ";
            }
        }
        std::cout << std::endl;
    }
}