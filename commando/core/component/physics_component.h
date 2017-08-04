#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

class Component;
class Entity;

class PhysicsComponent : public IComponent {
public:
    PhysicsComponent();
    PhysicsComponent(double xScale, double yScale, double zScale);
    
    bool isColliding;
    
    double xScale;
    double yScale;
    double zScale;
    
    double velocity;
};

#endif