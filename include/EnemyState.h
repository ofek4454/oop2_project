#pragma once

#include "PlayerState.h"

class EnemyState : public PlayerState {
public:
    EnemyState(const std::string &name, const std::string &id);

    ~EnemyState() = default;

    virtual void init();

    virtual void hoverFlag(const int row, const int col) {};

    virtual void hoverHole(const int row, const int col) {};

    virtual void doTurn(sf::Event::MouseButtonEvent *click);


    virtual void print() {
        auto window = WindowManager::instance().getWindow();
        for (auto &warrior: m_warriors)
            warrior->draw();
    }


private:
};


