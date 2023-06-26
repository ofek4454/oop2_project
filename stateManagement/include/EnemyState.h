#pragma once
#include "PlayerState.h"

class EnemyState : public PlayerState {
public:
    EnemyState(PlayerModel &player);

    ~EnemyState() = default;

    virtual void init();
    virtual bool move();

    virtual void doTurn(sf::Event::MouseButtonEvent *click = NULL,sf::Event::KeyEvent *key = NULL,Location indicator = Location(-1, -1));

    virtual void print() {
        for (auto &warrior: m_warriors)
            warrior.second->draw();
    }
    Emojis getEmoji() const {return m_emoji;}
    void setEmoji(const Emojis emoji) {m_emoji = emoji;}
    Location extractLocation(const std::string& str);
    bool isTie() const {return m_tie;}
    void setTieFalse() {m_tie = false;}
    std::string getPrevWeapon() const {return m_prevWeapon;}
private:
    Emojis m_emoji = NonEmoji_t;
    std::string m_prevWeapon;
    sf::Clock clock;
    bool m_tie = false;
};


