#include "main.h"

TankControllerScript::TankControllerScript(Entity *thisEntity) : IScript("TankControllerScript", thisEntity) {
}

void TankControllerScript::start() {
    // Initialization in here
    
    transformComp = (TransformComponent *) thisEntity->get("TransformComponent");
    physicsComp = (PhysicsComponent *) thisEntity->get("PhysicsComponent");
    
    lastTimeBulletFired = Time::timeFromStart;
    
    physicsComp->velocity = 30;
}

void TankControllerScript::update() {
    // Called every frame
    
    if (lastTimeBulletFired + TANK_FIRE_INTERVAL < Time::timeFromStart) {
        //=============== bullet =====================
        
        Entity *bullet = new Entity("tankBullet");
        bullet->add(new TransformComponent(transformComp->x, transformComp->y, 5, 5, 4, transformComp->rotation));
        bullet->add(new SpriteComponent("bullet_0"));
        bullet->add(new PhysicsComponent());
        ((PhysicsComponent *) bullet->get("PhysicsComponent"))->velocity = BULLET_SPEED;
        
        BulletControllerScript *bulletControllerScript = new BulletControllerScript(bullet);
        bullet->addScript(bulletControllerScript);
        
        gEngine->addEntity(bullet);
        
        lastTimeBulletFired = Time::timeFromStart;
        
        //============================================
    }
    
    transformComp->rotation += 30 * Time::deltaTime;
}

void TankControllerScript::onCollisionEnter(Entity *entity) {
    // Called when collided
}

void TankControllerScript::onCollisionExit(Entity *entity) {
    // Called when exiting collided area
}