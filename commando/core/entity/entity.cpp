#include "main.h"

Entity::Entity() {
    tag = DEFAULT_ENTITY_TAG;
    id = randString(ID_LEN);
    components = new unordered_map<string, IComponent *>();
    scripts = new unordered_map<string, IScript *>();
}

Entity::Entity(string tag) {
    this->tag = tag;
    id = randString(ID_LEN);
    components = new unordered_map<string, IComponent *>();
    scripts = new unordered_map<string, IScript *>();
}

Entity::~Entity() {
    for (auto it = components->begin(); it != components->end(); it++) {
        delete it->second;
    }
    delete components;
}

string Entity::getId() {
    return id;
}

string Entity::getTag() {
    return tag;
}

bool Entity::has(string name) {
    return (components->find(name) != components->end());
}

IComponent *Entity::get(string name) {
    return components->at(name);
}

void Entity::add(IComponent *component) {
    this->components->emplace(component->getName(), component);
}

IScript *Entity::getScript(string name) {
    if (scripts->find(name) != scripts->end()) {
        return scripts->at(name);
    } else {
        return NULL; // if not found, return NULL
    }
}

void Entity::addScript(IScript *script) {
    scripts->emplace(script->getName(), script);
    script->start();
}