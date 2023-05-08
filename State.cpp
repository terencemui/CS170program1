#include "State.h"
#include <iostream>
#include <vector>
#include <queue>

State::State(int n)
{
    this->n = n;
    board.reserve(n);
    for (int i = 0; i < n * n - 1; ++i)
    {
        board.push_back(i + 1);
    }
    board.push_back(-1);
    blank = n * n - 1;
}

State::State(const State &rhs)
{
    this->board = rhs.board;
    this->n = rhs.n;
    this->blank = rhs.blank;
    this->moves = rhs.moves;
}

State::~State()
{
}

bool State::move(int direction, State &newState)
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
            newState.blank -= n;
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
            newState.blank++;
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
            newState.blank += n;
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
            newState.blank--;
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
            // if (board[i * n + j] != -1)
            {
                std::cout << board[i * n + j] << " ";
            }
            // else
            // {
            //     std::cout << "* ";
            // }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool State::check()
{
    for (unsigned int i = 0; i < board.size(); ++i)
    {
        if (i != blank)
        {
            if (board.at(i) != i + 1)
            {
                return false;
            }
        }
    }
    return true;
}

int State::getMoves()
{
    return moves.size();
}

bool operator<(const State &s1, const State &s2)
{
    return s1.moves.size() < s2.moves.size();
}

void State::solveUniform()
{
    std::queue<State> pq;
    pq.push(*this);
    int count = 0;

    while (!pq.empty())
    {
        std::cout << "count: " << count++ << std::endl;
        State curr = pq.front();
        pq.pop();

        if (curr.check())
        {
            // done
            std::cout << "solution found " << std::endl;
            return;
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                State newState = State(curr);
                if (curr.move(i, newState))
                {
                    pq.push(newState);
                }
            }
        }
    }
}