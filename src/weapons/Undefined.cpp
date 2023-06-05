
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
    chooseWeapon();

}

void Undefined::fight(Paper &other) {
    chooseWeapon();

}

void Undefined::fight(Rock &other) {
    chooseWeapon();

}

void Undefined::fight(Undefined &other) {
    chooseWeapon();

}

void Undefined::fight(Hole &other) {
    lose();
}

void Undefined::fight(Flag &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

