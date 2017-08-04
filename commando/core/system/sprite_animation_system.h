#ifndef SPRITE_ANIMATION_SYSTEM_H
#define SPRITE_ANIMATION_SYSTEM_H

class SpriteAnimationSystem : public ISystem {
protected:
    
public:
    SpriteAnimationSystem(unordered_map<string, Entity *> *entities);
    
    virtual void update();
};

#endif
