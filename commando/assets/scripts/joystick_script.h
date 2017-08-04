#ifndef JOYSTICK_SCRIPT_H
#define JOYSTICK_SCRIPT_H

class IScript;

class JoystickScript : public IScript {
private:
    TransformComponent *transformComp;
    
    TransformComponent *playerTransformComp;
    PhysicsComponent *playerPhysicsComp;
    
    TransformComponent *cameraTransformComp;
    
    bool isTouching;
    
public:
    Entity *player;
    Entity *mainCamera;
    Entity *background;
    
    JoystickScript(Entity *thisEntity);
    
    void start();
    void update();
    void onCollisionEnter(Entity *entity);
    void onCollisionExit(Entity *entity);
};

#endif
