#ifndef SYSTEM_H
#define SYSTEM_H

class Entity;

class ISystem {
protected:
    unordered_map<string, Entity *> *entities;
    
public:
    ISystem(unordered_map<string, Entity *> *entities);
    virtual ~ISystem();
    
    virtual void update() = 0;
};

#endif