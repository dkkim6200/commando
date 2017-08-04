#include "main.h"

ButtonComponent::ButtonComponent(string normalImageName) : IComponent(BUTTON_COMPONENT_NAME) {
    this->normalImageName = normalImageName;
    this->highlightedImageName = "";
    this->onClick = new vector<function<void()>>();
}

ButtonComponent::ButtonComponent(string normalImageName, string highlightedImageName) : IComponent(BUTTON_COMPONENT_NAME) {
    this->normalImageName = normalImageName;
    this->highlightedImageName = highlightedImageName;
    this->onClick = new vector<function<void()>>();
}

void ButtonComponent::addTrigger(function<void ()> func) {
    onClick->push_back(func);
}