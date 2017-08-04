#ifndef PATH_SYSTEM_H
#define PATH_SYSTEM_H

class PathSystem : public ISystem {
protected:
    
public:
    PathSystem(unordered_map<string, Entity *> *entities);
    
    virtual void update();
};

#endif