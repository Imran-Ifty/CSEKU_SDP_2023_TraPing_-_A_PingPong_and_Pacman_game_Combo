#pragma once
#include "Header.h"
const int GRID_SIZE = 32; // Size of each grid cell
const int GRID_WIDTH = 28; // Number of grid cells in the horizontal direction
const int GRID_HEIGHT = 28; // Number of grid cells in the vertical direction
const int WINDOW_WIDTH = GRID_SIZE * GRID_WIDTH; // Width of the game window
const int WINDOW_HEIGHT = GRID_SIZE * GRID_HEIGHT;


class Player {
public:
    bool left, right;
    sf::Sprite sprite; // Sprite for the player
    int x = 2, y = 14; // Position of the player in the grid
    sf::Texture playerTexture;
    Player();
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
};
