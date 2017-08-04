#include "main.h"

Animation::Animation(string name, vector<string> *frames, int fps) {
    this->name = name;
    this->frames = frames;
    this->fps = fps;
}

AnimatorComponent::AnimatorComponent() : IComponent(ANIMATOR_COMPONENT_NAME) {
    anims = new unordered_map<string, Animation *>();
    
    curAnim = NO_ANIMATION;
    curFrame = 0;
}

void AnimatorComponent::addAnim(Animation *anim) {
    anims->emplace(anim->name, anim);
}

void AnimatorComponent::setAnim(string anim) {
    if (curAnim != anim) {
        curAnim = anim;
        curFrame = 0;
    }
}