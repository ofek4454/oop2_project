
#include "Undefined.h"
#include "Warrior.h"
#include "EventLoop.h"

Undefined::Undefined(bool isMine) : Weapon("U")  {
}

void Undefined::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}

void Undefined::fight(Scissors &other) {
    std::cout << "undefined ssicors\n";
    chooseWeapon();

}

void Undefined::fight(Paper &other) {
    std::cout << "undefined paper \n";
    chooseWeapon();

}

void Undefined::fight(Rock &other) {
    std::cout << "undefined rock\n";
    chooseWeapon();

}

void Undefined::fight(Undefined &other) {
    std::cout << "undefined undefined\n";
    chooseWeapon();

}

void Undefined::fight(Hole &other) {
    lose();
}

void Undefined::fight(Flag &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

