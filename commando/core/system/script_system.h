#ifndef SCRIPT_SYSTEM_H
#define SCRIPT_SYSTEM_H

class ScriptSystem : public ISystem {
protected:
    
public:
    ScriptSystem(unordered_map<string, Entity *> *entities);
    
    virtual void update();
};

#endif
