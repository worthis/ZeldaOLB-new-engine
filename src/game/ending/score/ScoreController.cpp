#include "ScoreController.h"

ScoreController::ScoreController() {
}

ScoreController::~ScoreController() {
}

void ScoreController::launch() {
    score.init();
}

void ScoreController::handleActions(Action* action) {
    score.handleActions(action);
}

void ScoreController::loop() {
}

void ScoreController::draw() {
    score.draw();
}
