#include "main.h"

PlayerControllerScript::PlayerControllerScript(Entity *thisEntity) : IScript("PlayerControllerScript", thisEntity) {
}

void PlayerControllerScript::start() {
    // Initialization in here
    
    transformComp = (TransformComponent *)thisEntity->get("TransformComponent");
    physicsComp = (PhysicsComponent *)thisEntity->get("PhysicsComponent");
    spriteComp = (SpriteComponent *)thisEntity->get("SpriteComponent");
    animatorComp = (AnimatorComponent *)thisEntity->get("AnimatorComponent");
    
    touched = false;
    
    destChecker = NULL;
}

void PlayerControllerScript::update() {
    // Called every frame
    
    
// ================== Player is controlled by joystick ====================
//    if (Input::touching &&
//        !touched &&
//        
//        !(Input::touchX > transformComp->x - transformComp->xScale / 2 &&
//        Input::touchX < transformComp->x + transformComp->xScale / 2 &&
//        Input::touchY > transformComp->y - transformComp->yScale / 2 &&
//        Input::touchY < transformComp->y + transformComp->yScale / 2)) {
//            
//        destX = Input::touchX;
//        destY = Input::touchY;
//        
//        if (destChecker != NULL) {
//            gEngine->removeEntity(destChecker->getId());
//        }
//        
//        //========== destChecker ============
//        
//        destChecker = new Entity("destChecker");
//        destChecker->add(new TransformComponent(destX, destY, 10, 10, 1, 0));
//        destChecker->add(new PhysicsComponent(1, 1, 1));
//        
//        gEngine->addEntity(destChecker);
//        
//        //=================================
//        
//        physicsComp->velocity = PLAYER_SPEED; // rotation is set in below; if rotation is set only once in here, player sometimes does not get to the destination, because of some inaccracies in calcuations.
//        
//        animatorComp->setAnim("playerWalkAnimation");
//        
//        touched = true;
//    }
//    else if (!Input::touching &&
//             touched) {
//        touched = false;
//    }
//    
//    transformComp->rotation = atan2((destY - transformComp->y) , (destX - transformComp->x)) * 180 / PI;
    
    if (animatorComp->curAnim == "playerFireAnimation") {
        physicsComp->velocity = 0;
        
        if (animatorComp->curFrame > 2) {
            animatorComp->setAnim("playerIdleAnimation");
        }
    }
}

void PlayerControllerScript::onCollisionEnter(Entity *entity) {
    
    if (entity->getTag() == "destChecker") {
        physicsComp->velocity = 0;
        animatorComp->setAnim("playerIdleAnimation");
        
        gEngine->removeEntity(entity->getId());
    }
}