#ifndef CAMERA_CONTROLLER_SCRIPT_H
#define CAMERA_CONTROLLER_SCRIPT_H

class IScript;

class CameraControllerScript : public IScript {
private:
    TransformComponent *transformComp;
    
    TransformComponent *playerTransformComp;
    
public:
    Entity *player;
    
    CameraControllerScript(Entity *thisEntity);
    
    void start();
    void update();
};

#endif
