#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "detectEdge.h"
#include "gameLogic.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

void placeuser(int& user);
void printGrid(const int user, const float cellSize, sf::RenderWindow& window, sf::Font& font);
void movePlayer(vector<int>& mapGrid, int& user, sf::RenderWindow& window, sf::Event& event, bool& refresh);
void initVector(vector<int>& mapGrid);
void placeGoal(const int position, int& goal);



int const dimension = 9;
int const vecSize = dimension * dimension;
int const center = dimension * (dimension / 2) + dimension / 2;
vector<int> mapGrid; // set size to dim*dim, and set each index equal to 0

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Game");

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return -1;
    }

    // Size of each cell (assuming a square window)
    float cellSize = window.getSize().x / dimension;
    srand(time(NULL));
    int user = center;
    bool refresh;
    initVector(mapGrid);

    while (window.isOpen()) {
        sf::Event event;
        refresh = false;

        //checks events from user
        movePlayer(mapGrid, user, window, event, refresh);

        window.clear();

        printGrid(user, cellSize, window, font);

        //refreshes the user's position
        if (refresh) {
            user = center;
        }

        
        

        window.display();
    }

    return 0;
}

void placeuser(int& user) {
    int max = dimension * dimension-1;
    int min = 0;
    int randNum;


    randNum = rand() % (max - min + 1) + min;

    while (randNum == 0) {
        randNum = rand() % (max - min + 1) + min;
        
    }

    user = randNum;
}

void printGrid(const int user, const float cellSize, sf::RenderWindow& window, sf::Font& font) {
    // Draw the grid
    string cellNum;
    for (int row = 0; row < dimension; ++row) {
        for (int col = 0; col < dimension; ++col) {

            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(col * cellSize, row * cellSize);

            // Set cell color based on its value in mapGrid
            if (mapGrid[row * dimension + col] == user) {
                cell.setFillColor(sf::Color::Red);  // User cell
            }
            else {
                cell.setFillColor(sf::Color(88, 181, 80));  // Empty cell
                
            }

            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(2);

            window.draw(cell);
            cellNum = to_string(mapGrid[row * dimension + col]);
            // Create a text object to display the number
            sf::Text cellText;
            cellText.setString(cellNum);
            cellText.setFont(font);
            cellText.setString(std::to_string(mapGrid[row * dimension + col]));
            cellText.setCharacterSize(static_cast<unsigned int>(cellSize / 2)); // Adjust character size
            cellText.setFillColor(sf::Color::Black);

            // Center the text in the cell
            sf::FloatRect textRect = cellText.getLocalBounds();
            cellText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            cellText.setPosition(col * cellSize + cellSize / 2.0f, row * cellSize + cellSize / 2.0f);

            window.draw(cellText);
        }
    }
}


void movePlayer(vector<int>& mapGrid, int& user, sf::RenderWindow& window, sf::Event& event, bool& refresh) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                refresh = true;
            }
            else if (event.key.scancode == sf::Keyboard::Scan::W && validMove(user, user - dimension, dimension)) {
                user -= dimension;
            }
            else if (event.key.scancode == sf::Keyboard::Scan::S && validMove(user, user + dimension, dimension)) {
                user += dimension;
            }
            else if (event.key.scancode == sf::Keyboard::Scan::D && validMove(user, user + 1, dimension)) {
                user += 1;
            }
            else if (event.key.scancode == sf::Keyboard::Scan::A && validMove(user, user - 1, dimension)) {
                user -= 1;
            }
        }
    }
}

void initVector(vector<int>& mapGrid) {
    for (int i = 0; i < vecSize; i++) {
        mapGrid.push_back(i);
    }
}

void placeGoal(const int position, int& goal) {
    int max = dimension * dimension-1;
    int min = 0;
    int randNum;
    
    
    randNum = rand() % (max - min + 1) + min;
    
    int rCol = randNum % dimension;
    int rRow = randNum / dimension;
    
    while (randNum == position /*|| alreadyVisited(randNum, playerWasHere)*/) {
        randNum = rand() % (max - min + 1) + min;
        //cout << randNum << " ";
    }
    
    goal = randNum;
}