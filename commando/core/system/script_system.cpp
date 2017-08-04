#include "main.h"

ScriptSystem::ScriptSystem(unordered_map<string, Entity *> *entities) : ISystem(entities) {
}

void ScriptSystem::update() {
restartIteration1:
    int entitiesSize = entities->size();
    for (auto it1 = entities->begin(); it1 != entities->end(); it1++) {
        if (entitiesSize != entities->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration1;
        }
        
        string curId = it1->first;
        Entity *curEntity = it1->second;
        
    restartIteration2:
        int scriptSize = curEntity->scripts->size();
        for (auto it2 = curEntity->scripts->begin(); it2 != curEntity->scripts->end(); it2++) {
            if (scriptSize != curEntity->scripts->size()) {  // if entities has been changed, and 'it' has been invalidated
                goto restartIteration2;
            }
            
            it2->second->update();
        }
    }
}