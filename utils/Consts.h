#pragma once
#include "SFML/Graphics.hpp"

const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.75;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.75;

const int NUM_OF_TEXTURES = 16;

// Board Size

const int IMAGE_COUNT = 20;

const int BOARD_SIZE = 8;

const float RECT_SIZE = (std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 0.7) / BOARD_SIZE;

const int IMAGE_WIDTH = 480 / 3;

const int IMAGE_HEIGHT = 1260 / 5;

const int MOVING_ANIMATION_ARR[IMAGE_COUNT] = {0, 0,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,
                        IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,IMAGE_WIDTH * 2,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,0,0};


enum Weapons_t{
    Rock_t,
    Paper_t,
    Scissors_t,
    Flag_t,
    Hole_t,
    Undefined_t,
};

enum Textures{
    Warriors,
    Rps,
    Arrow,
};

enum Direction{
    Up,
    Down,
    Left,
    Right,
    Non_Direction,
};

const sf::Color GRAY_COLOR = sf::Color(181, 193, 105);
const sf::Color GREEN_COLOR = sf::Color(181, 221, 94);