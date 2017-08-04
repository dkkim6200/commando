#ifndef COMPONENT_H
#define COMPONENT_H

class IComponent {
protected:
    string name;
    
public:
    IComponent();
    IComponent(string name);
    virtual ~IComponent();
    
    string getName();
};

#endif