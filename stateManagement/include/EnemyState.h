#pragma once
#include "PlayerState.h"

class EnemyState : public PlayerState {
public:
    EnemyState(PlayerModel &player);

    ~EnemyState() = default;

    virtual void init();
    virtual bool move();
    virtual void hoverFlag(const int row, const int col) {};

    virtual void hoverHole(const int row, const  int col) {};

    virtual void doTurn(sf::Event::MouseButtonEvent *click = NULL,sf::Event::KeyEvent *key = NULL,Location indicator = Location(-1, -1));

    virtual void print() {
        for (auto &warrior: m_warriors)
            warrior.second->draw();
    }

    Location extractLocation(const std::string& str);
protected:

private:
    sf::Clock clock;
};


