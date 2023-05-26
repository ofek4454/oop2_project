#pragma once

#include "Weapon.h"
#include "Event.h"
#include "EventLoop.h"

class Flag : public Weapon{
public:
    Flag();
    virtual void fight(Weapon& other) override;
    virtual void fight(Scissors& other) override;
    virtual void fight(Paper& other) override;
    virtual void fight(Rock& other) override;
    virtual void fight(Hole& other) override{}
    virtual void fight(Undefined& other) override;
    virtual void fight(Flag& other) override{}
};


