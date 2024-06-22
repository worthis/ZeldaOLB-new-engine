#include "Action.h"

Action::Action() {
    reset();
}

Action::~Action() {
}

void Action::setAction(ActionType key, bool b) {
    actions[key] = b;
}

bool Action::isAction(ActionType key) {
    return actions[key];
}

void Action::reset() {
    for (int i = 0; i < NB_ACTIONS; i++) {
        actions[i] = false;
    }
}
