#pragma once

#include "Weapon.h"
class Flag : public Weapon{
public:
    Flag(){}
    ~Flag() = default;
    virtual void fight(const Weapon& other) override {}
};


