#ifndef IMAGE_COMPONENT_H
#define IMAGE_COMPONENT_H

class ImageComponent : public IComponent {
public:
    ImageComponent(string imageName);
    
    string imageName;
    double opacity;
};

#endif