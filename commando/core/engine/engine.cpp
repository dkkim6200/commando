#include "main.h"

Engine *gEngine;

Engine::Engine() {
    Time::timeFromStart = 0;
    Time::deltaTime = 0;
    
    Input::touching = false;
    Input::touchX = 0;
    Input::touchY = 0;
    
    init();
    
    gEngine = this;
    
    isChangingScene = false;
    nextScene = NULL;
    
    scene = new INIT_SCENE();
    scene->start();
}

Engine::~Engine() {
    for (auto it = systems->begin(); it != systems->end(); it++) {
        delete (*it);
    }
    systems->clear();
    delete systems;
    
    for (auto it = entities->begin(); it != entities->end(); it++) {
        delete it->second;
    }
    entities->clear();
    delete entities;
}

void Engine::init() {
    entities = new unordered_map<string, Entity *>();
    systems = new vector<ISystem *>();
    
    addSystem( (ISystem *) (new PathSystem(entities)) );
    addSystem( (ISystem *) (new SpriteAnimationSystem(entities)) );
    addSystem( (ISystem *) (new MovementSystem(entities)) );
    addSystem( (ISystem *) (new PhysicsSystem(entities)) );
    addSystem( (ISystem *) (new ScriptSystem(entities)) );
    addSystem( (ISystem *) (new TimeSystem(entities)) );
}

void Engine::update() {
    if (isChangingScene) {
        for (auto it = entities->begin(); it != entities->end(); it++) {
            delete it->second;
        }
        entities->clear();
        
        delete this->scene;
        
        this->scene = nextScene;
        scene->start();
        
        mainCamera = getEntitiesWithTag("mainCamera")->at(0);
        
        isChangingScene = 0;
        nextScene = NULL;
    }
    
    for (int i = 0; i < systems->size(); i++) {
        systems->at(i)->update();
    }
}

void Engine::addEntity(Entity *entity) {
    entities->emplace(entity->getId(), entity);
    
    if (entity->getTag() == "mainCamera") {
        mainCamera = entity;
    }
}

Entity *Engine::getEntity(string id) {
    return entities->at(id);
}

vector<Entity *> *Engine::getEntitiesWithTag(string tag) {
    vector<Entity *> * vectorToReturn = new vector<Entity *>();
    
    for (auto it = entities->begin(); it != entities->end(); it++) {
        if (it->second->getTag() == tag) {
            vectorToReturn->push_back(it->second);
        }
    }
    
    return vectorToReturn;
}

void Engine::removeEntity(string id) {
    entities->erase(id);
}

void Engine::addSystem(ISystem *system) {
    systems->push_back(system);
}

void Engine::loadScene(IScene *scene) {
    isChangingScene = true;
    nextScene = scene;
}

Entity *Engine::getMainCamera() {
    return mainCamera;
}

unordered_map<string, Entity *> *Engine::getEntities() {
    return entities;
}