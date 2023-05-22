#pragma once
#include "SFML/Graphics.hpp"

const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.75;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.75;

const int NUM_OF_TEXTURES = 16;

// Board Size

const int BOARD_SIZE = 8;

const float rect_size = (std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 0.7) / BOARD_SIZE;


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
};