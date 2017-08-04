#ifndef BULLET_CONTROLLER_SCRIPT_H
#define BULLET_CONTROLLER_SCRIPT_H

class IScript;

class BulletControllerScript : public IScript {
private:
    TransformComponent *transformComp;
    PhysicsComponent *physicsComp;
    
public:
    BulletControllerScript(Entity *thisEntity);
    
    void start();
    void update();
    void onCollisionEnter(Entity *entity);
    void onCollisionExit(Entity *entity);
};

#endif