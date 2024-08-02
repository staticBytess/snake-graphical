#pragma once
#include <vector>

void movePlayer(int& row, int& col, char& input, int& position, const int dimension, const std::vector<int> blocks);
bool hasBlock(const int cellNum, const std::vector<int> blocks);
bool playerWon(const int position, const int goal);
bool moveRow(const int cellNum, const int direction, const int position, const int dimension);
bool moveCol(const int cellNum, const int direction, const int position, const int dimension);
bool alreadyVisited(const int cellNum, const std::vector<int> path);
bool goalReached(const int cursor, const int goal, const int dimension);
bool validMove(const int curCell, const int nextCell, const int dimension, const std::vector<int> path);
//bool validMove(const int curCell, const int nextCell, const std::vector<int> path, const int dimension);