#include "main.h"

IComponent::IComponent() {
    name = "";
}

IComponent::IComponent(string name) {
    this->name = name;
}

IComponent::~IComponent() {
}

string IComponent::getName() {
    return name;
}