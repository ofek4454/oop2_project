#pragma once

#include "Consts.h"
#include "PlayerModel.h"
#include "Warrior.h"
#include "WindowManager.h"
#include "Weapon.h"
#include "memory"
#include "array"

class PlayerState {
public:
    PlayerState(PlayerModel &player);
    virtual ~PlayerState() = default;
    virtual void init() = 0;
    virtual void hoverFlag(const int row, const int col) = 0;
    virtual void hoverHole(const int row, const int col) = 0;
    virtual void doTurn(sf::Event::MouseButtonEvent *click = NULL) = 0;
    virtual void print() = 0;

    bool setAsFlag(const int row, const int col);
    bool setAsHole(const int row, const int col);

    bool* checkAvailableLocations(Location location);
    bool move();
    std::unique_ptr<Warrior>* getWarrior(const Location location);
    std::vector<std::unique_ptr<Warrior>>* getAllWarriors() { return &m_warriors;}
    void handleHover(const int row, const int col);
    const PlayerModel &getPlayerModel() const;
    bool isAnimating() const {return m_isAnimating;}
    void setAnimating(bool animating) {m_isAnimating = animating;}
    Location getWarriorLocation() const {return m_selectedPlayerLocation;}

    void setPlayerSymbol(std::string s){m_playerSymbol=s;}
    void checkDeletion();


protected:
    std::vector<std::unique_ptr<Warrior>> m_warriors;
    bool m_playerChose = false;
    Direction_t m_direction;
    bool m_isAnimating;
    Location m_selectedPlayerLocation;
private:
    float m_pixelOffset = RECT_SIZE / IMAGE_COUNT;
    PlayerModel m_player;

    std::string m_playerSymbol;
};


