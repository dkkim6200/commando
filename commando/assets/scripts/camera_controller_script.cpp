#include "main.h"

CameraControllerScript::CameraControllerScript(Entity *thisEntity) : IScript("CameraControllerScript", thisEntity) {
}

void CameraControllerScript::start() {
    // Initialization in here
    
    transformComp = (TransformComponent *) thisEntity->get("TransformComponent");
    
    playerTransformComp = (TransformComponent *) player->get("TransformComponent");
}

void CameraControllerScript::update() {
    // Called every frame
    
    if (playerTransformComp->y < LEVEL_1_HEIGHT - Screen::height / 2 &&
        playerTransformComp->y > 0 + Screen::height / 2) {
        transformComp->x = playerTransformComp->x;
        transformComp->y = playerTransformComp->y;
    }
}