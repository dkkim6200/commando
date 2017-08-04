#include "main.h"

JoystickScript::JoystickScript(Entity *thisEntity) : IScript("JoystickScript", thisEntity) {
}

void JoystickScript::start() {
    // Initialization in here
    
    transformComp = (TransformComponent *) thisEntity->get("TransformComponent");
    
    playerTransformComp = (TransformComponent *) player->get("TransformComponent");
    playerPhysicsComp = (PhysicsComponent *) player->get("PhysicsComponent");
    
    cameraTransformComp = (TransformComponent *) mainCamera->get("TransformComponent");
    
    isTouching = false;
}

void JoystickScript::update() {
    // Called every frame
    
    if (Input::touching &&
        
        Input::touchX > transformComp->x - transformComp->xScale / 2 &&
        Input::touchX < transformComp->x + transformComp->xScale / 2 &&
        Input::touchY > transformComp->y - transformComp->yScale / 2 &&
        Input::touchY < transformComp->y + transformComp->yScale / 2) {
        
        isTouching = true;
    }
    else if (!Input::touching) {
        isTouching = false;
    }
    
    if (isTouching) {
        double dist = sqrt((Input::touchY - JOYSTICK_Y) * (Input::touchY - JOYSTICK_Y) + (Input::touchX - JOYSTICK_X) * (Input::touchX - JOYSTICK_X));
        double rotation = atan2((Input::touchY - JOYSTICK_Y) , (Input::touchX - JOYSTICK_X));
        
        double radius = min(dist, (double)JOYSTICK_RADIUS);
        
        transformComp->x = (cos(rotation) * radius) + JOYSTICK_X;
        transformComp->y = (sin(rotation) * radius) + JOYSTICK_Y;
        
        playerTransformComp->rotation = rotation * 180 / PI;
        playerPhysicsComp->velocity = PLAYER_SPEED;
    }
    else {
        transformComp->x = JOYSTICK_X;
        transformComp->y = JOYSTICK_Y;
        
        playerPhysicsComp->velocity = 0;
    }
}

void JoystickScript::onCollisionEnter(Entity *entity) {
    // Called when collided
}

void JoystickScript::onCollisionExit(Entity *entity) {
    // Called when exiting collided area
}