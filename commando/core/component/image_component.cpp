#include "main.h"

ImageComponent::ImageComponent(string imageName) : IComponent(IMAGE_COMPONENT_NAME) {
    this->imageName = imageName;
    opacity = 1;
}