#include "main.h"

TextFieldComponent::TextFieldComponent(string placeHolder, string font, int size) : IComponent(TEXTFIELD_COMPONENT_NAME) {
    this->text = "";
    
    this->placeHolder = placeHolder;
    this->font = font;
    this->size = size;
    
    this->isPassword = false;
}

TextFieldComponent::TextFieldComponent(string placeHolder, string font, int size, bool isPassword) : IComponent(TEXTFIELD_COMPONENT_NAME) {
    this->text = "";
    
    this->placeHolder = placeHolder;
    this->font = font;
    this->size = size;
    
    this->isPassword = isPassword;
}