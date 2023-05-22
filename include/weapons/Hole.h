#pragma once

#include "Weapon.h"
class Hole : public Weapon{
public:
    Hole() : Weapon() {}
    ~Hole() = default;
    virtual void fight(const Weapon& other) override {}

};


