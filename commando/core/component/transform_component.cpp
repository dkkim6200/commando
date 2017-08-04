#include "main.h"

TransformComponent::TransformComponent() : IComponent(TRANSFORM_COMPONENT_NAME) {
    x = DEFAULT_TRANSFORM_COMPONENT_X;
    y = DEFAULT_TRANSFORM_COMPONENT_Y;
    rotation = DEFAULT_TRANSFORM_COMPONENT_ROTATION;
}

TransformComponent::TransformComponent(double x, double y, double z, double xScale, double yScale, int rotation) : IComponent(TRANSFORM_COMPONENT_NAME) {
    this->x = x;
    this->y = y;
    this->z = z;
    
    this->xScale = xScale;
    this->yScale = yScale;
    this->zScale = Z_SCALE_2D;
    
    this->rotation = rotation;
}

void TransformComponent::translate(double x, double y, double z) {
    this->x += x;
    this->y += y;
    this->z += z;
}