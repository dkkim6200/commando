#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

class Component;

class TransformComponent : public IComponent {
public:
    TransformComponent();
    TransformComponent(double x, double y, double z, double width, double height, int rotation);
    
    double x;
    double y;
    double z;
    
    double xScale;
    double yScale;
    double zScale;
    
    double rotation;
    
    void translate(double x, double y, double z);
};

#endif