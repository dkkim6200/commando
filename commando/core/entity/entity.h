#ifndef ENTITY_H
#define ENTITY_H

class IComponent;

class Entity {
protected:
    string id;
    string tag;
    unordered_map<string, IComponent *> *components;
    
public:
    unordered_map<string, IScript *> *scripts;
    
    Entity();
    Entity(string tag);
    virtual ~Entity();
    
    string getId();
    string getTag();
    
    bool has(string name);
    IComponent *get(string name);
    
    void add(IComponent *component);
    
    IScript *getScript(string name);
    void addScript(IScript *script);
};

#endif
