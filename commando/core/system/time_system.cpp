#include "main.h"

TimeSystem::TimeSystem(unordered_map<string, Entity *> *entities) : ISystem(entities) {
    Time::deltaTime = 0;
    Time::timeFromStart = 0;
    
    prevTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    curTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void TimeSystem::update() {
    prevTime = curTime;
    curTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    
    Time::deltaTime = (curTime - prevTime) / 1000000000.0;
    
    Time::timeFromStart += Time::deltaTime;
}