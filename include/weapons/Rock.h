#pragma once
#include "SFML/Graphics.hpp"
#include "Weapon.h"

class Rock : public Weapon{
public:
    Rock();
    ~Rock() = default;
    virtual void fight(const Weapon& other) override {}
private:

};


