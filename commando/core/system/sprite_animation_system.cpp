#include "main.h"

SpriteAnimationSystem::SpriteAnimationSystem(unordered_map<string, Entity *> *entities) : ISystem(entities) {
}

void SpriteAnimationSystem::update() {
    
restartIteration:
    int entitiesSize = entities->size();
    for (auto it = entities->begin(); it != entities->end(); it++) {
        if (entitiesSize != entities->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration;
        }
        
        string curId = it->first;
        Entity *curEntity = it->second;
        
        if (curEntity->has(SPRITE_COMPONENT_NAME) &&
            curEntity->has(ANIMATOR_COMPONENT_NAME)) {
            
            SpriteComponent *spriteComp = (SpriteComponent *) curEntity->get(SPRITE_COMPONENT_NAME);
            AnimatorComponent *animatorComp = (AnimatorComponent *) curEntity->get(ANIMATOR_COMPONENT_NAME);
            
            if (animatorComp->curAnim != NO_ANIMATION) {
                Animation *anim = animatorComp->anims->at(animatorComp->curAnim);
                
                animatorComp->curFrame += anim->fps * Time::deltaTime;
                spriteComp->imageName = anim->frames->at(fmod(animatorComp->curFrame, anim->frames->size()));
            }
        }
    }
}