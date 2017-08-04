#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

class System;

class Vector2D {
public:
    Vector2D();
    Vector2D(double x, double y);
    
    double x;
    double y;
};

class PhysicsSystem : public ISystem {
protected:
    bool isColliding(double A_x, double A_y, double A_width, double A_height, double A_rotation,
                     double B_x, double B_y, double B_width, double B_height, double B_rotation);
    
    Vector2D rotatePoint(Vector2D pVec, Vector2D centerVec, double rotation);
    Vector2D projectPointToVec (Vector2D pVec, Vector2D lineVec);
    
    void callOnCollisionEnter(Entity *entity1, Entity *entity2);
    void callOnCollisionExit(Entity *entity1, Entity *entity2);
    
public:
    PhysicsSystem(unordered_map<string, Entity *> *entities);
    
    virtual void update();
};

#endif
