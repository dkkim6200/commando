#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

class System;

class TimeSystem : public ISystem {
protected:
    double prevTime;
    double curTime;
    
public:
    TimeSystem(unordered_map<string, Entity *> *entities);
    
    virtual void update();
};

#endif