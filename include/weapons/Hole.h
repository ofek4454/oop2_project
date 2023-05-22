#pragma once

#include "Weapon.h"
class Hole : public Weapon{
public:
    Hole() : Weapon() {}
    ~Hole() = default;
    virtual bool fight(Weapon& other) override {}
    virtual bool fight(Scissors& other) override {}
    virtual bool fight(Paper& other) override {}
    virtual bool fight(Rock& other) override {}
    virtual bool fight(Hole& other) override {}
    virtual bool fight(Undefined& other) override {}
    virtual bool fight(Flag& other) override {}

};


