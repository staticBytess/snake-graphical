#include "gameLogic.h"
#include "detectEdge.h"
#include <vector>
#include <conio.h>

using namespace std;

using namespace std;

void movePlayer(int& row, int& col, char& input, int& position, const int dimension, const vector<int> blocks) {
    input = _getch();
    int userRow = position / dimension;
    int userCol = position % dimension;
    switch (input) {

    case 'w': //up
        if (userRow != 0 && !hasBlock(position - dimension, blocks)) {
            position -= dimension;
        }

        break;
    case 's': //down
        if (userRow != dimension - 1 && !hasBlock(position + dimension, blocks)) {
            position += dimension;
        }
        break;
    case 'a': //left
        if (userCol != 0 && !hasBlock(position - 1, blocks)) {
            position -= 1;
        }
        break;
    case 'd': //right
        if (userCol != dimension - 1 && !hasBlock(position + 1, blocks)) {
            position += 1;
        }
        break;
    }

}

bool hasBlock(const int cellNum, const vector<int> blocks) {
    for (int i = 0; i < blocks.size(); i++) {
        if (cellNum == blocks[i]) {
            return true;
        }
    }
    return false;
}

bool playerWon(const int position, const int goal) {
    if (position == goal) {
        return true;
    }
    return false;
}

bool moveRow(const int cellNum, const int direction, const int position, const int dimension) {
    int cellRow = position / dimension;
    int cellCol = position % dimension;

    if (cellCol == 0 || cellCol == dimension - 1) {

        if (direction == 1 && cellRow != dimension - 1)
            return true;
        else if (direction == 0 && cellRow != 0)
            return false;
    }

    return false;

}

bool moveCol(const int cellNum, const int direction, const int position, const int dimension) {
    int cellCol = position % dimension;

    if (cellCol == dimension - 1 && direction == 0 || cellCol == 0 && direction == 1) {
        return true;
    }

    return false;
}
bool alreadyVisited(const int cellNum, const vector<int> path) {
    for (int i = 0; i < path.size(); i++) {
        if (!path.empty() && cellNum == path[i]) {
            return true;
        }
    }
    return false;
}

bool goalReached(const int cursor, const int goal, const int dimension) {
    return (cursor == goal - 1 || cursor == goal + 1 || cursor == goal + dimension || cursor == goal - dimension);
}

bool validMove(const int curCell, const int nextCell, const int dimension, const vector<int> path) {

    int curCol = curCell % dimension;

    if (alreadyVisited(nextCell, path)) {
                return false;
        }

    if (nextCell == curCell + 1 && atRightEdge(curCol, dimension)) {
        return false;
    }
    else if (nextCell == curCell - 1 && atLeftEdge(curCol)) {
        return false;
    }
    else if (nextCell < 0) {
        return false;
    }
    else if (nextCell >= dimension * dimension) {
        return false;

    }

    return true;
}
//bool validMove(const int curCell, const int nextCell, const vector<int> path, const int dimension) {
//    if (!alreadyVisited(nextCell, path)) {
//        return false;
//    }
//
//    int curCol = curCell % dimension;
//
//    if (nextCell == curCell + 1 && atRightEdge(curCol, dimension)) {
//        return false;
//    }
//    else if (nextCell == curCell - 1 && atLeftEdge(curCol)) {
//        return false;
//    }
//    else if (nextCell < 0) {
//        return false;
//    }
//    else if (nextCell >= dimension * dimension) {
//        return false;
//
//    }
//
//    return true;
//}