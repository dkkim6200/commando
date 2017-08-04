#ifndef PLAYER_CONTROLLER_SCRIPT_H
#define PLAYER_CONTROLLER_SCRIPT_H

class IScript;

class PlayerControllerScript : public IScript {
private:
    TransformComponent *transformComp;
    PhysicsComponent *physicsComp;
    SpriteComponent *spriteComp;
    AnimatorComponent *animatorComp;
    
    Entity *destChecker;
    
    bool touched;
    
    double destX;
    double destY;
    
    double prevX;
    double prevY;
    
public:
    PlayerControllerScript(Entity *thisEntity);
    
    void start();
    void update();
    void onCollisionEnter(Entity *entity);
};

#endif
