#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "detectEdge.h"
#include "gameLogic.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

/*Fix snake length*/

void printGrid(const int user, const int goal, const float cellSize, sf::RenderWindow& window, sf::Font& font);
void movePlayer(vector<int>& mapGrid, int& user, sf::RenderWindow& window, sf::Event& event, bool& refresh);
void initVector(vector<int>& mapGrid);
void placeGoal(const int user, int& goal, const vector<int> player);
void continueMoving(vector<int> player);

int const dimension = 9;
int const vecSize = dimension * dimension;
int const center = dimension * (dimension / 2) + dimension / 2;
bool playerIsHere(const int cellNum, const vector<int> player);
vector<int> mapGrid; // set size to dim*dim, and set each index equal to 0
vector<int> playerWasHere;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "David's Snake");
    sf::Clock clock;
    sf::Time elapsed1 = clock.getElapsedTime();
    std::cout << elapsed1.asSeconds() << std::endl;
    clock.restart();

    // Load a font
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Size of each cell (assuming a square window)
    float cellSize = window.getSize().x / dimension;
    srand(time(NULL));
    int user = center;
    int lastPos = user;
    int goal;
    int level = 1;
    bool refresh;
    initVector(mapGrid);
    placeGoal(user, goal, playerWasHere);

    while (window.isOpen()) {
        sf::Event event;
        refresh = false;
        window.clear();

        //checks events from user
        lastPos = user;
        movePlayer(mapGrid, user, window, event, refresh);
        
        printGrid(user, goal, cellSize, window, font);

        //refreshes the user's position
        if (refresh) {
            user = center;
            placeGoal(user, goal, playerWasHere);
        }
        else if(user == goal) {
            playerWasHere.insert(playerWasHere.begin(), user);
            placeGoal(user, goal, playerWasHere);
            level++;

        }
        else {

            if (lastPos != user) {
                playerWasHere.insert(playerWasHere.begin(), user);
                cout << "\nplayer size:" << playerWasHere.size() << "\n";
                for (int i = 0; i < playerWasHere.size(); i++) {
                    cout << playerWasHere[i];
                }
            }

            
            if (playerWasHere.size() > level) {
                playerWasHere.pop_back();
            }
        }


        window.display();
    }

    return 0;
}

void printGrid(const int user, const int goal, const float cellSize, sf::RenderWindow& window, sf::Font& font) {
    string cellNum;
    int cellNumber;

    for (int row = 0; row < dimension; ++row) {

        for (int col = 0; col < dimension; ++col) {
            cellNumber = mapGrid[row * dimension + col];

            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(col * cellSize, row * cellSize);

            // Set cell color based on its value in mapGrid
            if (cellNumber == user) {
                cell.setFillColor(sf::Color::Black);  // User cell
            }
            else if (playerIsHere(cellNumber, playerWasHere)) {
                cell.setFillColor(sf::Color::Red);  // User cell
            }
            else if (cellNumber == goal) {
                cell.setFillColor(sf::Color::Yellow);  // User cell
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

void placeGoal(const int user, int& goal, const vector<int> player) {
    int max = vecSize-1;
    int min = 0;
    int randNum;
    
    randNum = rand() % (max - min + 1) + min;
    
    while (randNum == user || playerIsHere(randNum, player)) {
        randNum = rand() % (max - min + 1) + min;
        //cout << randNum << " ";
    }
    
    goal = randNum;
}

bool playerIsHere(const int cellNum, const vector<int> player) {
    if (!player.empty()){ 
        for (int i = 0; i < player.size(); i++) {
            if (player[i] == cellNum)
                return true;
        }
    }
    return false;
}