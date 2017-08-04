#ifndef TEXT_FIELD_COMPONENT_H
#define TEXT_FIELD_COMPONENT_H

class TextFieldComponent : public IComponent {
public:
    TextFieldComponent(string placeHolder, string font, int size);
    TextFieldComponent(string placeHolder, string font, int size, bool isPassword);
    
    string text;
    string placeHolder;
    string font;
    int size;
    
    bool isPassword;
};

#endif
