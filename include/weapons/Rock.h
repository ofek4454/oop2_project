#pragma once

#include "SFML/Graphics.hpp"
#include "Weapon.h"
#include "Event.h"
#include "EventLoop.h"

class Rock : public Weapon{
public:
    Rock();
    ~Rock() = default;
    virtual bool fight(Weapon& other) override {}
    virtual bool fight(Scissors& other) override;
    virtual bool fight(Paper& other) override;
    virtual bool fight(Rock& other) override;
    virtual bool fight(Hole& other) override;
    virtual bool fight(Flag& other) override;
    virtual bool fight(Undefined& other) override {}
private:

};


