#pragma once
#include "SFML/Graphics.hpp"

const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.75;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.75;

const int NUM_OF_TEXTURES = 16;

// Board Size

const int MENU_BUTTONS = 5;

const int IMAGE_COUNT = 25;

const int BOARD_SIZE = 8;

const float RECT_SIZE = (std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 0.7) / BOARD_SIZE;

const int IMAGE_WIDTH = 480 / 3;

const int IMAGE_HEIGHT = 1260 / 5;

const int MOVING_ANIMATION_ARR[IMAGE_COUNT] = {0, 0,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,
                        IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,IMAGE_WIDTH * 2,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,0,0};

const float STARTING_X = (WINDOW_WIDTH * 0.775 - BOARD_SIZE * RECT_SIZE) / 2 + RECT_SIZE / 2;
const float STARTING_Y = WINDOW_HEIGHT / 2 - RECT_SIZE * (BOARD_SIZE / 2) + RECT_SIZE / 2;

const sf::FloatRect BOARD_FRAME((WINDOW_WIDTH * 0.775 - BOARD_SIZE * RECT_SIZE) / 2, WINDOW_HEIGHT / 2 - RECT_SIZE * (BOARD_SIZE / 2),RECT_SIZE * 8,RECT_SIZE * 8);

const sf::FloatRect BOARD_START(STARTING_X - RECT_SIZE / 2,STARTING_Y - RECT_SIZE / 2,RECT_SIZE,RECT_SIZE);


enum Weapons_t{
    Rock_t,
    Paper_t,
    Scissors_t,
    Flag_t,
    Hole_t,
    Undefined_t,
};

enum Textures_t{
    Warriors,
    Rps,
    Arrow,
    PaperPaper,
    RockRock,
    ScissorsScissors,
    BluePR,
    BlueRS,
    BlueSP,
    RedPR,
    RedRS,
    RedSP,
    Background,
};

enum Direction_t {
    Up,
    Down,
    Left,
    Right,
    Non_Direction,
};

enum EventType_t{
    Won,
    Lose,
    TimeOver,
    FightRP,
    FightRS,
    FightRR,
    FightPS,
    FightPP,
    FightSS,
    UndefinedChoose,
    UndefinedUndefined,
};

enum Turn_t{
    P1,
    P2,
};

enum Winner_t{
    P1Won,
    P2Won,
    Tie,
};

const sf::Color GRAY_COLOR = sf::Color(181, 193, 105);
const sf::Color GREEN_COLOR = sf::Color(181, 221, 94);
const sf::Color DARK_GREEN_COLOR = sf::Color(103, 133, 39,120);

const float H1 = WINDOW_HEIGHT * 0.065;
const float H2 = WINDOW_HEIGHT * 0.055;
const float H3 = WINDOW_HEIGHT * 0.04;