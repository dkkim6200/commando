#include "main.h"

SpriteComponent::SpriteComponent(string imageName) : IComponent(SPRITE_COMPONENT_NAME) {
    this->imageName = imageName;
    opacity = 1;
}