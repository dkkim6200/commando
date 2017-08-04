#ifndef SCENE_H
#define SCENE_H

class Engine;
class iOSSpriteWrapper;

class IScene {
protected:
public:
    virtual ~IScene();
    
    virtual void start() = 0;
};

#endif