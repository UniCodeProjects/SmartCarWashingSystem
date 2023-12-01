#include "GuardsManager.h"

GuardsManager& GuardsManager::getInstance() {
    static GuardsManager instance;
    return instance;
}

void GuardsManager::prepareForWashing() {
    openGate = false;
    vacant = false;
    washStart = true;
}

void GuardsManager::prepareForCheckOut() {
    washingComplete = true;
    washStart = false;
}

void GuardsManager::prepareForCheckIn() {
    openGate = false;
    vacant = true;
}

void GuardsManager::setGateOpened(const bool value) {
    openGate = value;
}

void GuardsManager::setVacant(const bool value) {
    vacant = value;
}

void GuardsManager::setCanWashStart(const bool value) {
    washStart = value;
}

void GuardsManager::setIsWashingComplete(const bool value) {
    washingComplete = value;
}

void GuardsManager::setBtnPressed(const bool value) {
    btnPressed = value;
}

bool GuardsManager::isGateOpen() {
    return openGate;
}

bool GuardsManager::isVacant() {
    return vacant;
}

bool GuardsManager::canWashStart() {
    return washStart;
}

bool GuardsManager::isWashingComplete() {
    return washingComplete;
}

bool GuardsManager::isBtnPressed() {
    return btnPressed;
}
