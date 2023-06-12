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
    Warrior* getWarrior() {return getWarrior(m_selectedWarriorId);};
    Warrior* getWarrior(const std::string warrior_id);
    Warrior* getWarrior(const Location location);
    Warrior* pickRandomWarrior();

    std::unordered_map<std::string,std::unique_ptr<Warrior>>* getAllWarriors() { return &m_warriors;}
    void handleHover(const int row, const int col);
    const PlayerModel &getPlayerModel() const;
    bool isAnimating() const {return m_isAnimating;}
    void setSelectedWarriorId(std::string id) { m_selectedWarriorId = id;}
    std::string getPlayerSymbol() {return m_playerSymbol;}
    void setPlayerSymbol(std::string s){m_playerSymbol=s;}
    void checkDeletion();


protected:
    std::unordered_map<std::string,std::unique_ptr<Warrior>> m_warriors;
    bool m_playerChose = false;
    Direction_t m_direction;
    bool m_isAnimating;
    PlayerModel m_player;
    float m_pixelOffset = RECT_SIZE / IMAGE_COUNT;
    std::string m_playerSymbol;

    std::string m_selectedWarriorId;
private:

};


