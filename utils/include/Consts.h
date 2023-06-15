#pragma once
#include "SFML/Graphics.hpp"
#include "nlohmann/json.hpp"
#include "HttpRequestsManager.h"

const float WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.75f;
const float WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.75f;

const int NUM_OF_TEXTURES = 25;
const int NUM_OF_HELP_SCREEN_PAGES = 4;

// Board Size
const int NUMBER_OF_SOUNDS = 16;
const int MENU_BUTTONS = 5;
const int IMAGE_COUNT = 25;
const int BOARD_SIZE = 8;
const int ROWS = 6;
const float RECT_SIZE = (std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 0.7f) / (ROWS);
const int IMAGE_WIDTH = 480 / 3;
const int IMAGE_HEIGHT = 1260 / 5;
const int WEP_WIDTH = 363 / 3;
const int WEP_HEIGHT = 768 / 6;

const int MOVING_ANIMATION_ARR[IMAGE_COUNT] = {0, 0,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,
                        IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,IMAGE_WIDTH * 2, IMAGE_WIDTH * 2,IMAGE_WIDTH * 2,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,IMAGE_WIDTH,0,0};

const sf::FloatRect BOARD_FRAME((WINDOW_WIDTH * 0.775f - BOARD_SIZE * RECT_SIZE) / 2 + RECT_SIZE / 2, WINDOW_HEIGHT / 2 - RECT_SIZE * (ROWS / 2) + RECT_SIZE / 2,RECT_SIZE * BOARD_SIZE,RECT_SIZE * ROWS);
const sf::FloatRect BOARD_TOP_LEFT(BOARD_FRAME.left - RECT_SIZE/2 ,BOARD_FRAME.top - RECT_SIZE/2 ,RECT_SIZE,RECT_SIZE);

const float CIRCLE_RADIUS = std::min(WINDOW_WIDTH*0.16f, WINDOW_HEIGHT*0.232f)/2;

const sf::Vector2f CLOCK_CIRCLE_CENTER = sf::Vector2f(WINDOW_WIDTH*0.875f + CIRCLE_RADIUS/30, WINDOW_HEIGHT*0.83f + 5);

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
    RefereeTexture,
    ExitButton,
    RoomButton,
    Trap,
    ShuffleButton,
    ScissorsFlip,
    ThrowPlayer,
    PaperFlip,
    RockFlip,
    WinningJump,
    RefereeDeclareWinning,
    Logo,
};


enum Sounds_t{
    tieP,
    tieR,
    tieS,
    winP,
    winR,
    winS,
    blueJump,
    blueTurn,
    redJump,
    redTurn,
    WinFight,
    LoseFight,
    JumpFight,
    GeneratingWeapons,
    ChooseWeapon,
    NoSound,
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
    FightRP,
    FightRS,
    FightRR,
    FightPS,
    FightPP,
    FightSS,
    AttackingUndefined,
    HoleFall,
    Rematch,
    TimeOver,
    Test // TODO remove
};

enum Turn_t{
    P1,
    P2,
};

enum Winner_t{
    P1Won,
    P2Won,
    Tie,
    NoneEvent
};

const sf::Color GRAY_COLOR = sf::Color(181, 193, 105);
const sf::Color GREEN_COLOR = sf::Color(181, 221, 94);
const sf::Color DARK_GREEN_COLOR = sf::Color(103, 133, 39,120);

const float H1 = WINDOW_HEIGHT * 0.065f;
const float H2 = WINDOW_HEIGHT * 0.055f;
const float H3 = WINDOW_HEIGHT * 0.04f;