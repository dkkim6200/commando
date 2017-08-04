#include "main.h"

ISystem::ISystem(unordered_map<string, Entity *> *entities) {
    this->entities = entities;
}

ISystem::~ISystem() {
}