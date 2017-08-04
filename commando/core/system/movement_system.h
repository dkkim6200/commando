#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

class System;

class MovementSystem : public ISystem {
protected:
    
public:
    MovementSystem(unordered_map<string, Entity *> *entities);
    
    virtual void update();
};

#endif