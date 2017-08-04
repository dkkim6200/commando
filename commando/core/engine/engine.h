#ifndef ENGINE_H
#define ENGINE_H

class Entity;
class ISystem;
class iOSSpriteWrapper;
class iOSTextWrapper;
class IScript;
class IScene;

class Engine {
protected:
    IScene *scene;
    Entity *mainCamera; // Reference from entities, don't put it in UML
    
    unordered_map<string, Entity *> *entities;
    vector<ISystem *> *systems;
    
private:
    bool isChangingScene;
    IScene *nextScene;
    
    void init();
    
    void addSystem(ISystem *system);
    
public:
    Engine();
    virtual ~Engine();
    
    virtual void update();
    
    void addEntity(Entity *entity);
    Entity *getEntity(string id);
    vector<Entity *> *getEntitiesWithTag(string tag);
    void removeEntity(string id);
    
    void loadScene(IScene *scene);
    
    Entity *getMainCamera();
    
    unordered_map<string, Entity *> *getEntities();
};



#endif