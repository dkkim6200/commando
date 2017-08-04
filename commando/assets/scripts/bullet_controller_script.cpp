#include "main.h"

BulletControllerScript::BulletControllerScript(Entity *thisEntity) : IScript("BulletControllerScript", thisEntity) {
}

void BulletControllerScript::start() {
    // Initialization in here
    
    transformComp = (TransformComponent *) thisEntity->get("TransformComponent");
    physicsComp = (PhysicsComponent *) thisEntity->get("PhysicsComponent");
}

void BulletControllerScript::update() {
    // Called every frame
    
    if (transformComp->y < 0 ||
        transformComp->y > LEVEL_1_HEIGHT) {
        gEngine->removeEntity(thisEntity->getId());
    }
}

void BulletControllerScript::onCollisionEnter(Entity *entity) {
    // Called when collided
    
    if ((entity->getTag() == "tank" &&
         thisEntity->getTag() == "playerBullet") ||
        
        (entity->getTag() == "player" &&
        thisEntity->getTag() == "tankBullet")) {
            
        gEngine->removeEntity(entity->getId());
        gEngine->removeEntity(thisEntity->getId());
    }
}

void BulletControllerScript::onCollisionExit(Entity *entity) {
    // Called when exiting collided area
}