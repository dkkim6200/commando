#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H

class ButtonComponent : public IComponent {
public:
    ButtonComponent(string normalImageName);
    ButtonComponent(string normalImageName, string highlightedImageName);
    
    void addTrigger(function<void()> func);
    
    string normalImageName;
    string highlightedImageName;
    
    vector<function<void()>> *onClick;
};

#endif