#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

class TextComponent : public IComponent {
public:
    TextComponent(string text, string font, int size, int alignment,
                  int colorR, int colorG, int colorB, int colorA);
    
    string text;
    string font;
    int size;
    
    int alignment;
    
    int colorR;
    int colorG;
    int colorB;
    int colorA;
};

#endif
