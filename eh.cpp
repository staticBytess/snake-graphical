
//void printWall(int& row, int& col, const int position, const int goal);
//void printCeiling();
//void initArray();
//void placeBlocks(const int position, const int goal, vector<int>& blocks);
//
//void findPath(const int position, const int goal);
//void randomMove(int& cursor, int& row, int& col,vector<int>& path, const int dimension);
//void resetPath(vector<int>& blocks, const char input = '0');
//void startGame();
//void resetMap(const int position, int& goal,const char input = '0');
//void gameLoop();
// 
//char getMarker(const int cellNum, const int goal);
//
//int const dimension = 10;
//int const blockCount = dimension * dimension / 2+ dimension;
//int const pathCount = dimension * dimension;
//int const width = 5;
//int const height = 3;
//
//int const center = dimension * (dimension / 2) + dimension / 2;
//
//int mapGrid[dimension][dimension];
//vector<int> blockGrid;
//vector<int> pathGrid;
//vector<int> playerWasHere;
//
//int main() {
//    startGame();
//}
//
//void startGame() {
//    srand(time(NULL));
//    initArray();
//    gameLoop();
//}
//
//
//void resetMap(const int position, int& goal, const char input) {
//    resetPath(blockGrid, input);
//    placeGoal(position, goal);
//    findPath(position, goal);
//    //placeBlocks(position, goal, blockGrid);
//}
//
//
//void gameLoop() {
//    int row;
//    int col;
//    int goal;
//    int level = 1;
//    
//    int position = center;
//    int currPos = position; //used to keep track of previous positon
//    char input = 'y';
//
//    resetMap(position, goal);
//
//    while (input != 'p') {
//        row = 0;
//        col = 0;
//        
//
//        for (int i = 0; i < pathGrid.size() - 1; i++) {
//            cout << pathGrid[i] << "  ";
//        }
//        
//      
//        cout << "\nLevel: " << level << endl;
//
//            
//
//        printGrid(row, col, position, goal);
//
//        currPos = position;
//        
//        
//
//        while (currPos == position && input != 'p' && input != 'r') { //only continue when position is refreshed
//            movePlayer(row, col, input, position, dimension, playerWasHere);
//
//        }
//
//        
//
//        if (playerWon(position, goal)) {
//            playerWasHere.insert(playerWasHere.begin(), position);
//            resetMap(position, goal);
//            level++;
//            
//        }
//        else if (input == 'r') {
//            resetMap(position, goal, input);
//            level = 1;
//        }
//        else {
//            playerWasHere.insert(playerWasHere.begin(), position);
//            cout << "\nplayer size:" << playerWasHere.size() << "\n";
//
//            if (playerWasHere.size() > level) {
//                playerWasHere.pop_back();
//            }
//        }
//
//        input = '0';
//        system("CLS");
//    }
//}
//
//char getMarker(const int cellNum, const int goal) {
//    if (hasBlock(cellNum, blockGrid)) {
//        return '/';
//    }
//    else if (cellNum == goal) {
//        return '&';
//    }
//    /*else if (alreadyVisited(cellNum, pathGrid) && cellNum != pathGrid.front() && cellNum != pathGrid.back()) {
//        return '.';
//    }*/
//    else {
//        return ' ';
//    }
//}
//
//void printWall(int& row, int& col, const int position, const int goal) {
//    int cellNum = mapGrid[row][col];
//    char cellMarker;
//
//    for (int cellRow = 0; cellRow < height; cellRow++) {
//        cout << "\n|";
//
//        for (int rowWidth = 0; rowWidth < dimension; rowWidth++) { //ensures enough columns are printed per row
//
//            cellMarker = getMarker(cellNum, goal);
//
//            for (int cellCol = 0; cellCol < width; cellCol++)
//            {
//
//                if (cellCol == 0 && cellRow == 0) {
//                    cout << cellNum;
//                    if (cellNum > 9) { //if cell number is double digit
//                        cellCol += 2; //removes two spaces from the width so the walls are aligned
//                    }
//                    else {
//                        cellCol += 1; //removes two spaces from the width so the walls are aligned
//                    }
//                }
//                if ((cellNum == position || alreadyVisited(cellNum, playerWasHere)) && cellRow == height / 2 && cellCol == width / 2) {
//                    cout << "*";
//                }
//                else {
//                    cout << cellMarker;
//                }
//            }
//
//            cout << "|";
//            col++;
//            if (col > dimension - 1) {
//                col = 0;
//            }
//            cellNum = mapGrid[row][col];
//        }
//
//    }
//
//}
//
//void printCeiling() {
//    cout << endl << "+";
//    for (int i = 0; i < dimension; i++) {
//        for (int j = 0; j < width; j++) {
//            cout << "-";
//        }
//
//        cout << "+";
//    }
//
//}
//
//void printGrid(int& row, int& col, const int position, const int goal) {
//    for (int i = 0; i < dimension; i++) {
//
//        printCeiling();
//        printWall(row, col, position, goal);
//        row++;
//
//    }
//    printCeiling();
//}
//
//void initArray() {
//    int cellNumber = 0;
//    for (int i = 0; i < dimension; i++) {
//        for (int j = 0; j < dimension; j++) {
//            mapGrid[i][j] = cellNumber++;
//        }
//
//    }
//
//}
//
//
//
//void placeBlocks(const int position, const int goal, vector<int>& blocks) {
//    int max = dimension * dimension;
//    int min = 0;
//    int randNum;
//
//    for (int i = 0; i < blockCount; i++) {
//
//        randNum = rand() % (max - min + 1) + min;
//        while (randNum == position || randNum == goal || alreadyVisited(randNum, pathGrid)) {
//            randNum = rand() % (max - min + 1) + min;
//        }
//        blocks.push_back(randNum);
//    }
//
//}
//
//
//
//
//
//
//
//void findPath(const int position, const int goal) {
//    int cursor = goal;
//    int counter = 0;
//    int cursorRow = cursor / dimension;
//    int cursorCol = cursor % dimension;
//    int posRow = position / dimension;
//    int posCol = position % dimension;
//    int max = 10;
//    int min = 0;
//    int modify;
//    int signal = 1;
//    
//
//
//
//    while (cursor != position && counter < dimension * dimension / 2 && signal == 1) {
//
//        if (pathGrid.empty()) {
//            pathGrid.push_back(cursor);
//        }
//
//        if (goalReached(cursor, position, dimension)) {
//            signal = 0;
//        }
//
//        modify = rand() % (max - min + 1) + min;
//
//        //modifier
//        if (modify > 6) {
//            randomMove(cursor, cursorRow, cursorCol, pathGrid,dimension);
//        }
//
//        else if (cursorRow < posRow && !alreadyVisited(cursor + dimension, pathGrid)) {
//            cursor += dimension;
//            cursorRow += 1;
//        }
//        else if (cursorCol < posCol && !alreadyVisited(cursor + 1, pathGrid)) {
//            cursor += 1;
//            cursorCol += 1;
//        }
//        else if (cursorRow > posRow && !alreadyVisited(cursor - dimension, pathGrid)) {
//       
//            cursor -= dimension;
//            cursorRow -= 1;
//        }
//        else if (cursorCol > posCol && !alreadyVisited(cursor - 1, pathGrid)) {
//        
//            cursor -= 1;
//            cursorCol -= 1;
//        }
//
//        if (!pathGrid.empty() && pathGrid.back() != cursor) {
//
//            if (!pathGrid.empty() && !alreadyVisited(cursor, pathGrid))
//                pathGrid.push_back(cursor);
//        }
//        counter++;
//    }
//}
//
//
//
//void resetPath(vector<int>& blocks, const char input) {
//    vector<int> temp;
//    pathGrid = temp;
//    blocks = temp;
//    if (input == 'r') {
//        playerWasHere = temp;
//    }
//    
//}
//
//
//
//
//void randomMove(int& cursor, int& row, int& col, vector<int>& path, const int dimension) {
//    int max = 3;
//    int min = 0;
//    int modify = rand() % (max - min + 1) + min;
//
//    if (modify == 0) { //moves up unless at edge or down
//        if (validMove(cursor, cursor - dimension, pathGrid, dimension)) {
//            cursor -= dimension;
//            row -= 1;
//        }
//        else if (validMove(cursor, cursor + dimension, pathGrid, dimension)) {
//            cursor += dimension;
//            row += 1;
//        }
//    }
//
//    else if (modify == 1) { //moves down or up
//        if (validMove(cursor, cursor + dimension, pathGrid, dimension)) {
//            cursor += dimension;
//            row += 1;
//        }
//        else if (validMove(cursor, cursor - dimension, pathGrid, dimension)) {
//            cursor -= dimension;
//            row -= 1;
//        }
//    }
//    else if (modify == 2) { //moves left unless at edge, then moves right
//        if (validMove(cursor, cursor - 1, pathGrid, dimension)) {
//            cursor -= 1;
//            col -= 1;
//        }
//        else if (validMove(cursor, cursor + 1, pathGrid, dimension)) {
//            cursor += 1;
//            col += 1;
//        }
//    }
//    else if (modify == 3) {
//        if (validMove(cursor, cursor + 1, pathGrid, dimension)) {
//            cursor += 1;
//            col += 1;
//        }
//        else if (validMove(cursor, cursor - 1, pathGrid, dimension)) {
//            cursor -= 1;
//            col -= 1;
//        }
//    }
//}
