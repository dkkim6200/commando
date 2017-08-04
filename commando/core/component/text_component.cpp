#include "main.h"

TextComponent::TextComponent(string text, string font, int size, int alignment,
                             int colorR, int colorG, int colorB, int colorA) : IComponent(TEXT_COMPONENT_NAME) {
    
    this->text = text;
    this->font = font;
    this->size = size;
    this->alignment = alignment;
    
    this->colorR = colorR;
    this->colorG = colorG;
    this->colorB = colorB;
    this->colorA = colorA;
}