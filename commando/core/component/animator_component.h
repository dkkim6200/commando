#ifndef ANIMATOR_COMPONENT_H
#define ANIMATOR_COMPONENT_H

class Animation {
public:
    Animation(string name, vector<string> *frames, int fps);
    
    string name;
    vector<string> *frames;
    int fps;
};

class AnimatorComponent : public IComponent {
public:
    AnimatorComponent();
    
    unordered_map<string, Animation *> *anims;
    
    string curAnim;
    double curFrame;
    
    void addAnim(Animation *anim);
    void setAnim(string anim);
};

#endif
