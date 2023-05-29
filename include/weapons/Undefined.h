#pragma once

#include "Weapon.h"
#include "WindowManager.h"

class Undefined : public Weapon{
public:
    Undefined(bool isMine);

    virtual void fight(Weapon& other) override;
    virtual void fight(Scissors& other) override;
    virtual void fight(Paper& other) override;
    virtual void fight(Rock& other) override;
    virtual void fight(Hole& other) override;
    virtual void fight(Undefined& other) override;
    virtual void fight(Flag& other) override;

private:

};


