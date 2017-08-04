#include "main.h"

PathSystem::PathSystem(unordered_map<string, Entity *> *entities) : ISystem(entities) {
}

void PathSystem::update() {
    
restartIteration:
    int entitiesSize = entities->size();
    for (auto it = entities->begin(); it != entities->end(); it++) {
        if (entitiesSize != entities->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration;
        }
        
        Entity *curEntity = it->second;
        
        if (curEntity->has(PATH_CONTROLLER_COMPONENT_NAME) &&
            
            // if Path is being played or should be played
            ((PathControllerComponent *) curEntity->get(PATH_CONTROLLER_COMPONENT_NAME))->playing) {
            
            PathControllerComponent *pathControllerComp = (PathControllerComponent *) curEntity->get(PATH_CONTROLLER_COMPONENT_NAME);
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            
            // get what Path to play
            Path *curAnim = pathControllerComp->paths->at(pathControllerComp->curPath);
            
            // get current frame from the Path
            PathFrameWrapper *curFrame = curAnim->frames->at(curAnim->curFrameIndex);
            
            if (pathControllerComp->started) {
                pathControllerComp->xDiff = curFrame->x - transformComp->x;
                pathControllerComp->yDiff = curFrame->y - transformComp->y;
                pathControllerComp->rotationDiff = curFrame->rotation - transformComp->rotation;
                
                pathControllerComp->started = false;
            }
            
            // changes the location of entity according to the information of current frame
            
            if (curAnim->isLocAbsolute) {
                transformComp->x = curFrame->x;
                transformComp->y = curFrame->y;
                transformComp->rotation = curFrame->rotation;
            }
            else {
                transformComp->x = curFrame->x - pathControllerComp->xDiff;
                transformComp->y = curFrame->y - pathControllerComp->yDiff;
                transformComp->rotation = curFrame->rotation;
            }
            
            // increase the index of what frame to render
            curAnim->curFrameIndex += 60 * Time::deltaTime;
//            curAnim->curFrameIndex++;
            
            if (curAnim->curFrameIndex >= curAnim->frames->size() - 1) {
                if (curAnim->loop) {
                    curAnim->curFrameIndex = 0; // loop the Path
                } else { // curAnim->loop == false
                    pathControllerComp->stopPath();
                }
            }
        }
    }
}