#include "main.h"

MovementSystem::MovementSystem(unordered_map<string, Entity *> *entities) : ISystem(entities) {
}

void MovementSystem::update() {
    
restartIteration:
    int entitiesSize = entities->size();
    for (auto it = entities->begin(); it != entities->end(); it++) {
        if (entitiesSize != entities->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration;
        }
        
        string curId = it->first;
        Entity *curEntity = it->second;
        
        if (curEntity->has(PHYSICS_COMPONENT_NAME)) {
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            PhysicsComponent *physicsComp = (PhysicsComponent *) curEntity->get(PHYSICS_COMPONENT_NAME);
            
            double prevX = transformComp->x;
            double prevY = transformComp->y;
            
            if (transformComp->rotation >= 360) {
                transformComp->rotation = fmod(transformComp->rotation, 360);
            }
            
            if (transformComp->rotation < 0) {
                transformComp->rotation += 360;
            }
            
            transformComp->x = prevX + cos((transformComp->rotation * PI / 180)) * physicsComp->velocity * Time::deltaTime;
            transformComp->y = prevY + sin((transformComp->rotation * PI / 180)) * physicsComp->velocity * Time::deltaTime;
        }
    }
}