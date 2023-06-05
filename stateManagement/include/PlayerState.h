#pragma once

#include "Consts.h"
#include "PlayerModel.h"
#include "Warrior.h"
#include "WindowManager.h"
#include "Weapon.h"
#include "memory"
#include "array"
#include "RoomState.h"

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

    virtual bool move() = 0;
    std::unique_ptr<Warrior>* getWarrior(const Location location);
    std::vector<std::unique_ptr<Warrior>>* getAllWarriors() { return &m_warriors;}
    void handleHover(const int row, const int col);
    const PlayerModel &getPlayerModel() const;
    bool isAnimating() const {return m_isAnimating;}

    Location getWarriorLocation() const {return m_selectedPlayerLocation;}
    std::string getPlayerSymbol() {return m_playerSymbol;}
    void setPlayerSymbol(std::string s){m_playerSymbol=s;}
    void checkDeletion();
    void setWarriorLocation(Location location){ m_selectedPlayerLocation = location;}

protected:
    Location m_newLocation;
    std::vector<std::unique_ptr<Warrior>> m_warriors;
    bool m_playerChose = false;
    Direction_t m_direction;
    bool m_isAnimating;
    Location m_selectedPlayerLocation;
    PlayerModel m_player;
    float m_pixelOffset = RECT_SIZE / IMAGE_COUNT;
    std::string m_playerSymbol;
private:

};


