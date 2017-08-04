#include "main.h"

Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

PhysicsSystem::PhysicsSystem(unordered_map<string, Entity *> *entities) : ISystem(entities) {
}

void PhysicsSystem::update() {
    
restartIteration1:
    int entitiesSize1 = entities->size();
    for (auto it1 = entities->begin(); it1 != entities->end(); it1++) {
        if (entitiesSize1 != entities->size()) {  // if entities has been changed, and it1 has been invalidated
            goto restartIteration1;
        }
        
        Entity *entity1 = it1->second;
        
        if (entity1->has(PHYSICS_COMPONENT_NAME)) {
            
            PhysicsComponent *physicsComp1 = (PhysicsComponent *) entity1->get(PHYSICS_COMPONENT_NAME);
            TransformComponent *transformComp1 = (TransformComponent *) entity1->get(TRANSFORM_COMPONENT_NAME);
            
restartIteration2:
            int entitiesSize2 = entities->size();
            for (auto it2 = entities->begin(); it2 != entities->end(); it2++) {
                if (entitiesSize2 != entities->size()) { // if entities has been changed, and it2 has been invalidated
                    goto restartIteration2;
                }
                
                Entity *entity2 = it2->second;
                
                if (entity1 != entity2 &&
                    entity2->has(PHYSICS_COMPONENT_NAME)) {
                    
                    PhysicsComponent *physicsComp2 = (PhysicsComponent *) entity2->get(PHYSICS_COMPONENT_NAME);
                    TransformComponent *transformComp2 = (TransformComponent *) entity2->get(TRANSFORM_COMPONENT_NAME);
                    
                    if (isColliding(transformComp1->x, transformComp1->y, transformComp1->xScale * physicsComp1->xScale, transformComp1->yScale * physicsComp1->yScale, transformComp1->rotation,
                                    transformComp2->x, transformComp2->y, transformComp2->xScale * physicsComp2->xScale, transformComp2->yScale * physicsComp2->yScale, transformComp2->rotation)) {
                        
                        if (!physicsComp1->isColliding) {
                            callOnCollisionEnter(entity1, entity2);
                            
                            physicsComp1->isColliding = true;
                        }
                        
                        // Used 'else if' instead of 'if' because if in onCollisionEnter(), entity2 has been deleted, then it will cause EXC_BAD_ACCESS error. Plus, since 1st and 2nd for loop will both access entities one whole time, one pair would be accessed 2 times, so using 'else if' does not matter.
                        // For instance, if pair (entities->at(1), entities->at(2)) is being accessed, pair (entities->at(2), entities->at(1)) is alse being accessed.
                        
                        else if (!physicsComp2->isColliding) {
                            callOnCollisionEnter(entity2, entity1);
                            
                            physicsComp2->isColliding = true;
                        }
                        
                    } else { // not colliding
                        
                        if (physicsComp1->isColliding) {
                            callOnCollisionExit(entity1, entity2);
                            
                            physicsComp1->isColliding = false;
                        }
                        
                        else if (physicsComp2->isColliding) {
                            callOnCollisionExit(entity2, entity1);
                            
                            physicsComp2->isColliding = false;
                        }
                        
                    }
                }
            }
        }
    }
}

bool PhysicsSystem::isColliding(double A_x, double A_y, double A_width, double A_height, double A_rotation,
                                   double B_x, double B_y, double B_width, double B_height, double B_rotation) {
    
    /*
     
     A_p1-------A_p2
     |          |
     |     A    |
     |          |
     |          |
     A_p3-------A_p4
     
     
     
     || =============>>
     ||
     || B_p1-------B_p2
     || |          |
     || |     B    |
     || |          |
     || |          |
     || B_p3-------B_p4
     \/
     
     */
    
    
    Vector2D A[4];
    A[0] = Vector2D(A_x - A_width / 2, A_y - A_height / 2);
    A[1] = Vector2D(A_x + A_width / 2, A_y - A_height / 2);
    A[2] = Vector2D(A_x - A_width / 2, A_y + A_height / 2);
    A[3] = Vector2D(A_x + A_width / 2, A_y + A_height / 2);
    
    Vector2D B[4];
    B[0] = Vector2D(B_x - B_width / 2, B_y - B_height / 2);
    B[1] = Vector2D(B_x + B_width / 2, B_y - B_height / 2);
    B[2] = Vector2D(B_x - B_width / 2, B_y + B_height / 2);
    B[3] = Vector2D(B_x + B_width / 2, B_y + B_height / 2);
    
    for (int i = 0; i < 4; i++) {
        A[i] = rotatePoint(A[i], Vector2D(A_x, A_y), A_rotation);
    }
    for (int i = 0; i < 4; i++) {
        B[i] = rotatePoint(B[i], Vector2D(B_x, B_y), B_rotation);
    }
    
    
    Vector2D axis[4];
    axis[0] = Vector2D(A[1].x - A[0].x, A[1].y - A[0].y);
    axis[1] = Vector2D(A[1].x - A[3].x, A[1].y - A[3].y);
    axis[2] = Vector2D(B[0].x - B[2].x, B[0].y - B[2].y);
    axis[3] = Vector2D(B[0].x - B[1].x, B[0].y - B[1].y);
    
    
    for (int i = 0; i < 4; i++) {
        double A_min = 0;
        double A_max = 0;
        for (int j = 0; j < 4; j++) {
            Vector2D projectedLoc = projectPointToVec(A[j], axis[i]);
            double scalarVal = projectedLoc.x * axis[i].x + projectedLoc.y * axis[i].y;
            
            if (scalarVal > A_max ||
                A_max == 0) {
                A_max = scalarVal;
            }
            else if (scalarVal < A_min ||
                     A_min == 0) {
                A_min = scalarVal;
            }
        }
        
        double B_min = 0;
        double B_max = 0;
        for (int j = 0; j < 4; j++) {
            Vector2D projectedLoc = projectPointToVec(B[j], axis[i]);
            double scalarVal = projectedLoc.x * axis[i].x + projectedLoc.y * axis[i].y;
            
            if (scalarVal > B_max ||
                B_max == 0) {
                B_max = scalarVal;
            }
            else if (scalarVal < B_min ||
                     B_min == 0) {
                B_min = scalarVal;
            }
        }
        
        if (!(B_min < A_max &&
            B_max > A_min)) { // No overlap!
            
            return false;
        }
    }
    
    return true;
}

Vector2D PhysicsSystem::rotatePoint(Vector2D pVec, Vector2D centerVec, double rotation) {
    double tempX = pVec.x - centerVec.x;
    double tempY = pVec.y - centerVec.y;
    
    return Vector2D(tempX * cos(rotation) - tempY * sin(rotation) + centerVec.x, tempX * sin(rotation) + tempY * cos(rotation) + centerVec.y);
}

Vector2D PhysicsSystem::projectPointToVec(Vector2D pVec, Vector2D lineVec) {
    double fraction = (pVec.x * lineVec.x + pVec.y * lineVec.y) / (pow(lineVec.x, 2) + pow(lineVec.y, 2));
    
    return Vector2D(fraction * lineVec.x, fraction * lineVec.y);
}

void PhysicsSystem::callOnCollisionEnter(Entity *entity1, Entity *entity2) {
restartIteration:
    int scriptSize = entity1->scripts->size();
    for (auto it = entity1->scripts->begin(); it != entity1->scripts->end(); it++) {
        if (scriptSize != entity1->scripts->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration;
        }
        
        it->second->onCollisionEnter(entity2);
    }
}

void PhysicsSystem::callOnCollisionExit(Entity *entity1, Entity *entity2) {
restartIteration:
    int scriptSize = entity1->scripts->size();
    for (auto it = entity1->scripts->begin(); it != entity1->scripts->end(); it++) {
        if (scriptSize != entity1->scripts->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration;
        }
        
        it->second->onCollisionExit(entity2);
    }
}