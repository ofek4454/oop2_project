#pragma once

#include "Weapon.h"
class Undefined : public Weapon{
public:
    Undefined(bool isMine);

    ~Undefined() = default;
    virtual bool fight(Weapon& other) override;
    virtual bool fight(Scissors& other) override {}
    virtual bool fight(Paper& other) override {}
    virtual bool fight(Rock& other) override {}
    virtual bool fight(Hole& other) override {}
    virtual bool fight(Undefined& other) override {std::cout << "Undefined fight" << std::endl; return false;}
    virtual bool fight(Flag& other) override {}

};


