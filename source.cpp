#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "detectEdge.h"
#include "gameLogic.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

void printGrid(const int user, const int goal, const float cellSize, const float offset, sf::RenderWindow& window, sf::Font& font);
char getNextMove(const char prevChar, bool& refresh, sf::RenderWindow& window, sf::Event& event, bool& active);
void movePlayer(int& user, const char input, const float delay, sf::Clock& clock, const vector<int> player);
void initVector(vector<int>& mapGrid);
void placeGoal(const int user, int& goal, const vector<int> player);
void updatePlayerVector(const int user, const int lastPos, const int level, vector<int>& player);
void resetVector(vector<int>& resetMe);

int const dimension = 9;
int const vecSize = dimension * dimension;
int const center = dimension * (dimension / 2) + dimension / 2;
const sf::Color scoreboardColor(50, 50, 50);
const sf::Color scoreTextColor(255, 255, 255);
const sf::Color mapColor(88, 181, 80);
const sf::Color cellOutlineColor(0, 0, 0);
const sf::Color snakeHeadColor(199, 69, 22);
const sf::Color snakeBodyColor(255, 90 ,31);
const sf::Color goalColor(232, 242, 0);
bool playerIsHere(const int cellNum, const vector<int> player);
vector<int> mapGrid; // set size to dim*dim, and set each index equal to 0
vector<int> snakeBody;

int main() {

    const float offset = 50;

    sf::RenderWindow window(sf::VideoMode(800, 800+offset), "David's Snake");
    sf::Clock clock;
    

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
    const float userDelayInSeconds = 0.15f;
    const float autoDelayInSeconds = 0.2f;
    
    bool refresh;
    bool active;
    char input = 0;
    initVector(mapGrid);
    placeGoal(user, goal, snakeBody);

    while (window.isOpen()) {
        sf::Event event;
        refresh = false;
        active = false;
        window.clear(sf::Color(scoreboardColor));

        //checks events from user
        lastPos = user;
        input = getNextMove(input, refresh, window, event, active);

        if (active) {
            movePlayer(user, input, userDelayInSeconds, clock, snakeBody);
        }
        else {
            movePlayer(user, input, autoDelayInSeconds, clock, snakeBody);
        }
        
        

        //refreshes the user's position
        if (refresh) {
            user = center;
            resetVector(snakeBody);
            placeGoal(user, goal, snakeBody);


        }
        else if(user == goal) {
            snakeBody.insert(snakeBody.begin(), user);
            placeGoal(user, goal, snakeBody);
            level++;

        }
        else {
            updatePlayerVector(user, lastPos, level, snakeBody);
            
        }

        
        // Create a text object for the scoreboard
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Level: " + std::to_string(level));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(scoreTextColor);
        scoreText.setPosition(10, 10);

        // Draw the scoreboard
        window.draw(scoreText);

        printGrid(user, goal, cellSize, offset, window, font);


        window.display();
    }

    return 0;
}

void printGrid(const int user, const int goal, const float cellSize, const float offset, sf::RenderWindow& window, sf::Font& font) {
    string cellNum;
    int cellNumber;

    for (int row = 0; row < dimension; ++row) {

        for (int col = 0; col < dimension; ++col) {
            cellNumber = mapGrid[row * dimension + col];

            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(col * cellSize, row * cellSize + offset);

            // Set cell color based on its value in mapGrid
            if (cellNumber == user) {
                cell.setFillColor(snakeHeadColor);  // User cell
            }
            else if (playerIsHere(cellNumber, snakeBody)) {
                cell.setFillColor(snakeBodyColor);  // User cell
            }
            else if (cellNumber == goal) {
                cell.setFillColor(goalColor);  // User cell
            }
            else {
                cell.setFillColor(mapColor);  // Empty cell
                
            }

            cell.setOutlineColor(cellOutlineColor);
            cell.setOutlineThickness(2);

            window.draw(cell);

            /* UNCOMMENT FOR CELL NUMBERS TO BE DISPLAY
            * 
            * 
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
            cellText.setPosition(col * cellSize + cellSize / 2.0f, row * cellSize + offset + cellSize / 2.0f);
            

            window.draw(cellText);
            */
        }
    }
}

void movePlayer(int& user, const char input, const float delay, sf::Clock& clock, const vector<int> player) {
    
    if (clock.getElapsedTime().asSeconds() > delay) {
        switch (input) {
        case 'w':
            if (validMove(user, user - dimension, dimension, player)) {
                user -= dimension;
                clock.restart();
            }
            break;
        case 's':
            if (validMove(user, user + dimension, dimension, player)) {
                user += dimension;
                clock.restart();
            }
            break;
        case 'a':
            if (validMove(user, user - 1, dimension, player)) {
                user -= 1;
                clock.restart();
            }
            break;
        case 'd':
            if (validMove(user, user + 1, dimension, player)) {
                user += 1;
                clock.restart();
            }
            break;
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


void updatePlayerVector(const int user, const int lastPos, const int level, vector<int>& player) {
    if (lastPos != user) {
        player.insert(player.begin(), user);
        cout << "\nplayer size:" << player.size() << "\n";
        for (int i = 0; i < player.size(); i++) {
            cout << player[i];
        }
    }


    if (player.size() > level) {
        player.pop_back();
    }
}

char getNextMove(const char prevChar, bool& refresh, sf::RenderWindow& window, sf::Event& event, bool& active) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                refresh = true;
                return 'c';
            }
            else if (event.key.scancode == sf::Keyboard::Scan::W) {
                active = true;
                    return 'w';
            }
            else if (event.key.scancode == sf::Keyboard::Scan::S) {
                active = true;
                    return 's';
            }
            else if (event.key.scancode == sf::Keyboard::Scan::D) {
                active = true;
                    return 'd';
            }
            else if (event.key.scancode == sf::Keyboard::Scan::A) {
                active = true;
                return 'a';
            }
        }
        
    }
    return prevChar;
}
void resetVector(vector<int>& resetMe) {
    vector<int> temp;
    resetMe = temp;
}