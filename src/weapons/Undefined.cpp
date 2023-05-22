//
// Created by Bar Kobi on 21/05/2023.
//

#include "Undefined.h"

bool Undefined::fight(Weapon &other) {
    if (&other == this)
        return false;

    other.fight(*this);
}
