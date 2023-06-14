#pragma once

#include "Consts.h"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "EventLoop.h"

class TimeCounting {
public:
    TimeCounting();
    void setCount(int count) { m_countLength = count;}
    void updateCount();
    void setText(float dt);
    void print();
    void setColor(sf::Color color);
private:
    sf::CircleShape m_circle;
    sf::Text m_countdownText;
    int m_countLength = 0;
    int numLines;
    const int numSegments = 60; // Number of line segments
    sf::RenderWindow *m_window;
};


