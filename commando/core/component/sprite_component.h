#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

class Component;

class SpriteComponent : public IComponent {
public:
    SpriteComponent(string imageName);
    
    string imageName;
    double opacity;
};

#endif