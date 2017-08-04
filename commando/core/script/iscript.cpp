#include "main.h"

IScript::IScript(string name, Entity *thisEntity) {
    this->thisEntity = thisEntity;
    this->name = name;
}

Entity *IScript::getAttachedEntity() {
    return thisEntity;
}

string IScript::getName() {
    return name;
}

void IScript::start() {
    // N/A
}

void IScript::update() {
    // N/A
}

void IScript::onCollisionEnter(Entity *entity) {
    // N/A
}

void IScript::onCollisionExit(Entity *entity) {
    // N/A
}