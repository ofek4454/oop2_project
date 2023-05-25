#pragma once

#include "Weapon.h"

class Hole : public Weapon{
public:
    Hole();
    ~Hole() = default;
    virtual void fight(Weapon& other) override;
    virtual void fight(Scissors& other) override;
    virtual void fight(Paper& other) override;
    virtual void fight(Rock& other) override;
    virtual void fight(Hole& other) override{}
    virtual void fight(Undefined& other) override{}
    virtual void fight(Flag& other) override{}

};


