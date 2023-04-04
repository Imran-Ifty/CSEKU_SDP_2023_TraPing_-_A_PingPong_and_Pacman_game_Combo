#include "Player.h"

Player::Player()
{
    if (!playerTexture.loadFromFile("img/blinky.png")) {
        std::cout << "Player image not found !!! " << std::endl;
    }
    sprite.setTexture(playerTexture);
    sprite.setPosition(x * 32, y * 32);
    this->x = x;
    this->y = y;
}

void Player:: moveUp() {
    if (y > 1) {
        y--;
        sprite.move(0, -32);
    }
}


void Player:: moveDown() {
    if (y < GRID_HEIGHT - 2) {
        y++;
        sprite.move(0, 32);
    }
}

void Player::moveLeft() {
    

    sprite.setScale(-1, 1);
    if (left == false) {
        right = false;
        goto r;
    }
    if (x > 2 ) {
        x--;
        sprite.move(-32, 0);
        left = true;
    }
r:
    left = true;
    
}

void Player:: moveRight() {

    sprite.setScale(1, 1);
    if (right == false) {
        left = false;
        goto r;
    }
    if (x < GRID_WIDTH - 2) {
        x++;
        sprite.move(32, 0);
        right = true;
    }
r:
    right = true;
}