#include "State.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <string>
#include <set>

State::State(int n)
{
    this->n = n;
    board.reserve(n*n);
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
    this->misplaced = rhs.misplaced;
    this->euclidean = rhs.euclidean;
}

State::~State()
{
}

void State::createBoard(std::vector<int> &board)
{
    this->board = board;
    for (unsigned int i = 0; i < board.size(); ++i)
    {
        if (board.at(i) == -1)
        {
            blank = i;
        }
    }
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
            if (board[i * n + j] != -1)
            {
                std::cout << board[i * n + j] << "\t";
            }
            else
            {
                std::cout << "*\t";
            }
        }
        std::cout << std::endl;
    }
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

const int State::getMoves()
{
    return moves.size();
}

void State::setMisplaced()
{
    int count = 0;
    for (unsigned int i = 0; i < board.size(); ++i)
    {
        if (board[i] != -1 && board[i] != (i + 1))
        {
            count++;
        }
    }
    misplaced = count;
}

const int State::getMisplaced()
{
    return misplaced;
}

void State::setEuclidean()
{
    double count = 0;
    int deltaX = 0;
    int deltaY = 0;
    for (unsigned int i = 0; i < board.size(); ++i)
    {
        if (board[i] != -1)
        {
            deltaX = (i % n) - ((board[i] - 1) % n);
            deltaY = (i / n) - ((board[i] - 1) / n);
            count += sqrt(deltaX * deltaX + deltaY * deltaY);
        }
    }
    euclidean = count;
}

const double State::getEuclidean()
{
    return euclidean;
}

struct Uniform
{
    const bool operator()(State &s1, State &s2)
    {
        return (s1.getMoves() > s2.getMoves());
    }
};

struct Misplaced
{
    const bool operator()(State &s1, State &s2)
    {
        return (s1.getMoves() + s1.getMisplaced() > s2.getMoves() + s2.getMisplaced());
    }
};

struct Euclidean
{
    const bool operator()(State &s1, State &s2)
    {
        return (s1.getMoves() + s1.getEuclidean() > s2.getMoves() + s2.getEuclidean());
    }
};

void State::solveUniform()
{
    std::priority_queue<State, std::vector<State>, Uniform> pq;
    pq.push(*this);
    int count = 0;
    int max = 1;

    std::set<std::vector<int>> visited;

    std::cout << "Expanding state: \n";
    this->printState();

    while (!pq.empty())
    {
        if (pq.size() > max)
        {
            max = pq.size();
        }
        State curr = pq.top();
        pq.pop();

        if (curr.check())
        {
            std::cout << "Solution found \n\nThe solution is: \n";
            printSolution(curr.moves);
            std::cout << "\nThe maximum number of nodes in a queue at any one time: " << max << std::endl;
            std::cout << "The depth of the goal node was " << curr.moves.size() << std::endl;
            return;
        }
        else if (!visited.contains(curr.board)) // if it hasn't been visited
        {
            visited.insert(board);
            std::cout << "The next state to expand in the uniform cost search is: \n";
            curr.printState();
            std::cout << "Expanding this node \n\n";
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

void State::solveMisplaced()
{
    std::priority_queue<State, std::vector<State>, Misplaced> pq;
    this->setMisplaced();
    this->moves = {};
    pq.push(*this);
    int count = 0;
    int max = 1;

    std::set<std::vector<int>> visited;

    std::cout << "Expanding state: \n";
    this->printState();

    while (!pq.empty())
    {
        if (pq.size() > max)
        {
            max = pq.size();
        }
        State curr = pq.top();
        pq.pop();

        if (curr.check())
        {
            std::cout << "Solution found \n\nThe solution is: \n";
            printSolution(curr.moves);
            std::cout << "\nThe maximum number of nodes in a queue at any one time: " << max << std::endl;
            std::cout << "The depth of the goal node was " << curr.moves.size() << std::endl;
            return;
        }
        else if (!visited.contains(curr.board)) // if it hasn't been visited
        {
            std::cout << "The best state to expand next with g(n) = " << curr.getMoves() << " and h(n) = " << curr.getMisplaced() << " is: \n";
            curr.printState();
            std::cout << "Expanding this node \n\n";
            for (int i = 0; i < 4; ++i)
            {
                State newState = State(curr);
                if (curr.move(i, newState))
                {
                    newState.setMisplaced();
                    pq.push(newState);
                }
            }
        }
    }
}

void State::solveEuclidean()
{
    std::priority_queue<State, std::vector<State>, Euclidean> pq;

    this->setEuclidean();
    pq.push(*this);
    int count = 0;
    int max = 1;

    std::set<std::vector<int>> visited;

    std::cout << "Expanding state: " << std::endl;
    this->printState();

    while (!pq.empty())
    {
        if (pq.size() > max)
        {
            max = pq.size();
        }
        State curr = pq.top();
        pq.pop();

        if (curr.check())
        {
            std::cout << "Solution found \n\nThe solution is: \n";
            printSolution(curr.moves);
            std::cout << "\nThe maximum number of nodes in a queue at any one time: " << max << std::endl;
            std::cout << "The depth of the goal node was " << curr.moves.size() << std::endl;
            return;
        }
        else if (!visited.contains(curr.board)) // if it hasn't been visited
        {
            std::cout << "The best state to expand next with g(n) = " << curr.getMoves() << " and h(n) = " << curr.getEuclidean() << std::endl;
            curr.printState();
            std::cout << "Expanding this node" << std::endl;
            for (int i = 0; i < 4; ++i)
            {
                State newState = State(curr);
                if (curr.move(i, newState))
                {
                    newState.setEuclidean();
                    pq.push(newState);
                }
            }
        }
    }
}

void State::printSolution(std::vector<int> &sol)
{
    std::string moves = "NESW";
    for (unsigned int i = 0; i < sol.size(); ++i)
    {
        std::cout << moves[sol[i]] << " ";
    }
}