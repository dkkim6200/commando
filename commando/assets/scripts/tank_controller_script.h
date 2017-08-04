#ifndef TANK_CONTROLLER_SCRIPT_H
#define TANK_CONTROLLER_SCRIPT_H

class IScript;

class TankControllerScript : public IScript {
private:
    TransformComponent *transformComp;
    PhysicsComponent *physicsComp;
    
    double lastTimeBulletFired;
    
public:
    TankControllerScript(Entity *thisEntity);
    
    void start();
    void update();
    void onCollisionEnter(Entity *entity);
    void onCollisionExit(Entity *entity);
};

#endif
