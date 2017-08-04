#ifndef ISCRIPT_H
#define ISCRIPT_H

class Entity;
class System;
class Scene;

class IScript {
protected:
    Entity *thisEntity;
    string name;
    
public:
    IScript(string name, Entity *thisEntity);
    
    Entity *getAttachedEntity();
    string getName();
    
    virtual void start();
    virtual void update();
    virtual void onCollisionEnter(Entity *entity);
    virtual void onCollisionExit(Entity *entity);
};

#endif