#include "main.h"

PhysicsComponent::PhysicsComponent() : IComponent(PHYSICS_COMPONENT_NAME) {
    isColliding = false;
    
    xScale = 1;
    yScale = 1;
    zScale = 1;
    
    velocity = 0;
}

PhysicsComponent::PhysicsComponent(double xScale, double yScale, double zScale)  : IComponent(PHYSICS_COMPONENT_NAME) {
    isColliding = false;
    
    this->xScale = xScale;
    this->yScale = yScale;
    this->zScale = zScale;
    
    velocity = 0;
}