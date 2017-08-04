//
//  GameScene.m
//  galaga
//
//  Created by 김대건 on 2016-04-07.
//  Copyright (c) 2016 DaekunKim. All rights reserved.
//

#import "GameScene.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>

using namespace std;

#include "main.h"

@implementation GameScene {
    Engine *engine;
    
    NSTimer *gameLoopTimer;
    
    unordered_map<string, SKTexture *> *textures;
    unordered_map<string, SKSpriteNode *> *sprites;
    unordered_map<string, UILabel *> *texts;
    unordered_map<string, UIButton *> *buttons;
    unordered_map<string, UITextField *> *textFields;
    unordered_map<string , SKSpriteNode *> *images;
    
    double screenTouchX;
    double screenTouchY;
}

-(void)didMoveToView:(SKView *)view {
    self.anchorPoint = CGPointMake(0, 0);
    self.size = [[UIScreen mainScreen] bounds].size;
    
    Screen::width = self.size.width;
    Screen::height = self.size.height;
    
    self.backgroundColor = [SKColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
    
    engine = new Engine();
    
    textures = new unordered_map<string, SKTexture *>();
    sprites = new unordered_map<string, SKSpriteNode *>();
    texts = new unordered_map<string, UILabel *>();
    buttons = new unordered_map<string, UIButton *>();
    textFields = new unordered_map<string, UITextField *>();
    images = new unordered_map<string, SKSpriteNode *>();
    
    gameLoopTimer = [NSTimer scheduledTimerWithTimeInterval:(1.0 / 300.0) target:self
                                           selector:@selector(gameLoop) userInfo:nil repeats:YES];
    
    screenTouchX = 0;
    screenTouchY = 0;
}

-(void)gameLoop {
    engine->update();
}

-(SKTexture *)getTextureWithImageNamed:(string)name {
    if (textures->find(name) == textures->end()) {
        SKTexture *texture = [SKTexture textureWithImageNamed:[NSString stringWithUTF8String:name.c_str()]];
        texture.filteringMode = SKTextureFilteringNearest;
        
        textures->emplace(name, texture);
    }
    
    return textures->at(name);
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[[event allTouches] allObjects] objectAtIndex:0];
    
    NSLog(@"%f, %f", [touch locationInNode:self].x, [touch locationInNode:self].y);
    
//    screenTouchX = [touch locationInNode:self].x;
//    screenTouchY = [touch locationInNode:self].y;
//    
//    TransformComponent *cameraTransformComponent = (((TransformComponent *)(engine->getMainCamera()->get(TRANSFORM_COMPONENT_NAME))));
//    Input::touchX = (cameraTransformComponent->x - Screen::width / 2) + screenTouchX;
//    Input::touchY = (cameraTransformComponent->y - Screen::height / 2) + screenTouchY;
    
    Input::touchX = [touch locationInNode:self].x;
    Input::touchY = [touch locationInNode:self].y;
    
    Input::touching = true;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[[event allTouches] allObjects] objectAtIndex:0];
    
    NSLog(@"%f, %f", [touch locationInNode:self].x, [touch locationInNode:self].y);
    
//    screenTouchX = [touch locationInNode:self].x;
//    screenTouchY = [touch locationInNode:self].y;
//
//    TransformComponent *cameraTransformComponent = (((TransformComponent *)(engine->getMainCamera()->get(TRANSFORM_COMPONENT_NAME))));
//    Input::touchX = (cameraTransformComponent->x - Screen::width / 2) + screenTouchX;
//    Input::touchY = (cameraTransformComponent->y - Screen::height / 2) + screenTouchY;
    
    Input::touchX = [touch locationInNode:self].x;
    Input::touchY = [touch locationInNode:self].y;
}

-(void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[[event allTouches] allObjects] objectAtIndex:0];
    
    NSLog(@"%f, %f", [touch locationInNode:self].x, [touch locationInNode:self].y);
    
//    screenTouchX = [touch locationInNode:self].x;
//    screenTouchY = [touch locationInNode:self].y;
//
//    TransformComponent *cameraTransformComponent = (((TransformComponent *)(engine->getMainCamera()->get(TRANSFORM_COMPONENT_NAME))));
//    Input::touchX = (cameraTransformComponent->x - Screen::width / 2) + screenTouchX;
//    Input::touchY = (cameraTransformComponent->y - Screen::height / 2) + screenTouchY;
    
    Input::touchX = [touch locationInNode:self].x;
    Input::touchY = [touch locationInNode:self].y;
    
    Input::touching = false;
}

//==========================================================================================
// Sprite Related
//==========================================================================================
-(void)createSprite:(string) entityId
         spriteComp:(SpriteComponent *)spriteComp
      transformComp:(TransformComponent *)transformComp {
    
    SKSpriteNode *curSprite = [SKSpriteNode spriteNodeWithTexture:[self getTextureWithImageNamed:spriteComp->imageName]];
    curSprite.name = [NSString stringWithUTF8String:spriteComp->imageName.c_str()]; // name of texture
    
    curSprite.xScale = transformComp->xScale / curSprite.size.width;
    curSprite.yScale = transformComp->yScale / curSprite.size.height;
    
    curSprite.anchorPoint = CGPointMake(0.5, 0.5);
    curSprite.position = CGPointMake(transformComp->x, transformComp->y);
    
    curSprite.zPosition = transformComp->z;
    curSprite.zRotation = transformComp->rotation * M_PI / 180;
    
    curSprite.alpha = spriteComp->opacity;
    
    [self addChild:curSprite];
    sprites->emplace(entityId, curSprite);
}

//==========================================================================================
// Text (UILabel) Related
//==========================================================================================
-(void)createText:(string) entityId
         textComp:(TextComponent *)textComp
    transformComp:(TransformComponent *)transformComp {
    
    UILabel *curText = [[UILabel alloc] initWithFrame:CGRectMake(transformComp->x,Screen::height - transformComp->y, transformComp->xScale, transformComp->yScale)];
    curText.center = CGPointMake(transformComp->x, Screen::height - transformComp->y);
    
    curText.text = [NSString stringWithUTF8String:textComp->text.c_str()];
    curText.font = [UIFont fontWithName:[NSString stringWithUTF8String: textComp->font.c_str()] size:textComp->size];
    
    curText.backgroundColor = [UIColor clearColor];
    curText.textColor = [UIColor colorWithRed:textComp->colorR green:textComp->colorG blue:textComp->colorB alpha:textComp->colorA];
    
    if (textComp->alignment == ALIGNMENT_LEFT) {
        curText.textAlignment = NSTextAlignmentLeft;
    } else if (textComp->alignment == ALIGNMENT_CENTER) {
        curText.textAlignment = NSTextAlignmentCenter;
    } else if (textComp->alignment == ALIGNMENT_RIGHT) {
        curText.textAlignment = NSTextAlignmentRight;
    }
    
    [self.view addSubview:curText];
    texts->emplace(entityId, curText);
}

//==========================================================================================
// Button Related
//==========================================================================================
-(void)createButton:(string) entityId
         buttonComp:(ButtonComponent *)buttonComp
      transformComp:(TransformComponent *)transformComp {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.accessibilityLabel = [NSString stringWithUTF8String:entityId.c_str()];

    [button addTarget:self
               action:@selector(onButtonClick:)
     forControlEvents:UIControlEventTouchUpInside];

    UIImage *normalImage = [UIImage imageNamed:[NSString stringWithUTF8String:buttonComp->normalImageName.c_str()]];
    [button setImage:normalImage forState:UIControlStateNormal];
    
    if (buttonComp->highlightedImageName != "") {
        UIImage *highlightedImage = [UIImage imageNamed:[NSString stringWithUTF8String:buttonComp->highlightedImageName.c_str()]];
        [button setImage:highlightedImage forState:UIControlStateHighlighted];
    }
    
    button.frame = CGRectMake(0, 0, transformComp->xScale, transformComp->yScale);
    button.center = CGPointMake(transformComp->x, Screen::height - transformComp->y);
    
    [self.view addSubview:button];
    buttons->emplace(entityId, button);
}

-(void)onButtonClick: (id)sender{
    UIButton *uiButton = (UIButton *)sender;
    
    Entity *button = engine->getEntity([uiButton.accessibilityLabel UTF8String]);
    ButtonComponent *buttonComp = (ButtonComponent *) button->get(BUTTON_COMPONENT_NAME);
    
    for (int i = 0; i < buttonComp->onClick->size(); i++) {
        buttonComp->onClick->at(i)();
    }
}

//==========================================================================================
// TextField Related
//==========================================================================================
-(BOOL) textFieldShouldReturn:(UITextField *)sender{
    [sender resignFirstResponder];
    return YES;
}

-(BOOL) textFieldShouldEndEditing:(UITextField *)sender{
    [sender resignFirstResponder];
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    NSString *newString = [textField.text stringByReplacingCharactersInRange:range withString:string];
    
    Entity *textFieldEntity = engine->getEntity([textField.accessibilityLabel UTF8String]);
    TextFieldComponent *textFieldComp = (TextFieldComponent *) textFieldEntity->get(TEXTFIELD_COMPONENT_NAME);
    textFieldComp->text = [newString UTF8String];
    
    return YES;
}

-(void) createTextField:(string) entityId
          textFieldComp:(TextFieldComponent *)textFieldComp
          transformComp:(TransformComponent *)transformComp {
    
    UITextField* textField = [[UITextField alloc] initWithFrame:CGRectMake(0, 0, transformComp->xScale, transformComp->yScale)];
    textField.center = CGPointMake(transformComp->x, Screen::height - transformComp->y);
    
    textField.accessibilityLabel = [NSString stringWithUTF8String:entityId.c_str()];
    
    textField.font = [UIFont fontWithName:[NSString stringWithUTF8String:textFieldComp->font.c_str()] size:textFieldComp->size];
    textField.placeholder = [NSString stringWithUTF8String:textFieldComp->placeHolder.c_str()];
    textField.secureTextEntry = textFieldComp->isPassword;
    
    textField.borderStyle = UITextBorderStyleRoundedRect;
    textField.autocorrectionType = UITextAutocorrectionTypeNo;
    textField.keyboardType = UIKeyboardTypeDefault;
    textField.returnKeyType = UIReturnKeyDone;
    textField.clearButtonMode = UITextFieldViewModeWhileEditing;
    textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    [textField setAutocapitalizationType:UITextAutocapitalizationTypeNone];
    
    [textField setDelegate:self];
    [self.view addSubview:textField];
    textFields->emplace(entityId, textField);
}

//==========================================================================================
// Image Related
//==========================================================================================
-(void)createImage:(string) entityId
        imageComp:(ImageComponent *)imageComp
     transformComp:(TransformComponent *)transformComp {
    
    SKSpriteNode *curImage = [SKSpriteNode spriteNodeWithTexture:[self getTextureWithImageNamed:imageComp->imageName]];
    curImage.name = [NSString stringWithUTF8String:imageComp->imageName.c_str()]; // name of texture
    
    curImage.xScale = transformComp->xScale / curImage.size.width;
    curImage.yScale = transformComp->yScale / curImage.size.height;
    
    curImage.anchorPoint = CGPointMake(0.5, 0.5);
    curImage.position = CGPointMake(transformComp->x, transformComp->y);
    
    curImage.zPosition = transformComp->z;
    curImage.zRotation = transformComp->rotation * M_PI / 180;
    
    curImage.alpha = imageComp->opacity;
    
    [self addChild:curImage];
    images->emplace(entityId, curImage);
}

//==========================================================================================
// Main Game Loop
//==========================================================================================
-(void)update:(CFTimeInterval)currentTime {
    TransformComponent *cameraTransformComponent = (((TransformComponent *)(engine->getMainCamera()->get(TRANSFORM_COMPONENT_NAME))));
    
//    Input::touchX = (cameraTransformComponent->x - Screen::width / 2) + screenTouchX;
//    Input::touchY = (cameraTransformComponent->y - Screen::height / 2) + screenTouchY;
    
    unordered_map<string, Entity *> *entities = engine->getEntities();
    
restartIteration1:
    int entitiesSize = entities->size();
    for (auto it = entities->begin(); it != entities->end(); it++) {
        if (entitiesSize != entities->size()) {  // if entities has been changed, and 'it' has been invalidated
            goto restartIteration1;
        }
        
        Entity *curEntity = it->second;
        string curEntityId = it->first;
        
        if (curEntity->has(SPRITE_COMPONENT_NAME)) {
            
            SpriteComponent *spriteComp = (SpriteComponent *) curEntity->get(SPRITE_COMPONENT_NAME);
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            
            if (sprites->find(curEntityId) == sprites->end()) {
                // if sprite hasn't been created, create one
                
                [self createSprite:curEntityId
                        spriteComp:spriteComp
                     transformComp:transformComp];
            }
            
            if (spriteComp->imageName != [sprites->at(curEntityId).name UTF8String]) { // if the sprite's image has been changed
                sprites->at(curEntityId).texture = [self getTextureWithImageNamed:spriteComp->imageName];
                sprites->at(curEntityId).name = [NSString stringWithUTF8String:spriteComp->imageName.c_str()];
                
//                sprites->at(curEntityId).xScale = transformComp->xScale / sprites->at(curEntityId).size.width;
//                sprites->at(curEntityId).yScale = transformComp->yScale / sprites->at(curEntityId).size.height;
                
                sprites->at(curEntityId).anchorPoint = CGPointMake(0.5, 0.5);
            }
            
            sprites->at(curEntityId).position = CGPointMake(transformComp->x - (cameraTransformComponent->x - Screen::width / 2),
                                                            transformComp->y - (cameraTransformComponent->y - Screen::height / 2));
            sprites->at(curEntityId).zPosition = transformComp->z;
            sprites->at(curEntityId).zRotation = transformComp->rotation * M_PI / 180;
            sprites->at(curEntityId).alpha = spriteComp->opacity;
            
        }
        
        else if (curEntity->has(TEXT_COMPONENT_NAME)) {
            
            TextComponent *textComp = (TextComponent *) curEntity->get(TEXT_COMPONENT_NAME);
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            
            if (texts->find(curEntityId) == texts->end()) {
                [self createText:curEntityId
                        textComp:textComp
                   transformComp:transformComp];
            }
            
            texts->at(curEntityId).text = [NSString stringWithUTF8String:textComp->text.c_str()];
            
            CGFloat red, green, blue, alpha;
            [texts->at(curEntityId).textColor getRed:(&red)
                                               green:(&green)
                                                blue:(&blue)
                                               alpha:(&alpha)];
            if (red != textComp->colorR ||
                green != textComp->colorG ||
                blue != textComp->colorB ||
                alpha != textComp->colorA) {
                
                // if the color of the text have changed
                
                texts->at(curEntityId).textColor = [UIColor colorWithRed:textComp->colorR green:textComp->colorG blue:textComp->colorB alpha:textComp->colorA];
            }
        }
        
        else if (curEntity->has(BUTTON_COMPONENT_NAME)) {
            
            ButtonComponent *buttonComp = (ButtonComponent *) curEntity->get(BUTTON_COMPONENT_NAME);
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            
            if (buttons->find(curEntityId) == buttons->end()) {
                [self createButton:curEntityId
                        buttonComp:buttonComp
                   transformComp:transformComp];
            }
        }
        
        else if (curEntity->has(TEXTFIELD_COMPONENT_NAME)) {
            
            TextFieldComponent *textFieldComp = (TextFieldComponent *) curEntity->get(TEXTFIELD_COMPONENT_NAME);
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            
            if (textFields->find(curEntityId) == textFields->end()) {
                [self createTextField:curEntityId
                        textFieldComp:textFieldComp
                        transformComp:transformComp];
            }
        }
        
        else if (curEntity->has(IMAGE_COMPONENT_NAME)) {
            
            ImageComponent *imageComp = (ImageComponent *) curEntity->get(IMAGE_COMPONENT_NAME);
            TransformComponent *transformComp = (TransformComponent *) curEntity->get(TRANSFORM_COMPONENT_NAME);
            
            if (images->find(curEntityId) == images->end()) {
                // if sprite hasn't been created, create one
                
                [self createImage:curEntityId
                        imageComp:imageComp
                    transformComp:transformComp];
            }
            
            images->at(curEntityId).position = CGPointMake(transformComp->x, transformComp->y);
            images->at(curEntityId).zPosition = transformComp->z;
            images->at(curEntityId).zRotation = transformComp->rotation * M_PI / 180;
            images->at(curEntityId).alpha = imageComp->opacity;
            
        }
    }
    
restartIteration2:
    for (auto it = sprites->begin(); it != sprites->end(); it++) {
        string curEntityId = it->first;
        
        if (entities->find(curEntityId) == entities->end()) {
            [sprites->at(curEntityId) removeFromParent];
            sprites->erase(curEntityId);
            goto restartIteration2; // We have to restart the loop, because changing the element of unordered_map while iterating it caused EXC_BAD_ACCESS exception (likely because of concurrent accessing)
        }
    }
    
restartIteration3:
    for (auto it = texts->begin(); it != texts->end(); it++) {
        string curEntityId = it->first;
        
        if (entities->find(curEntityId) == entities->end()) {
            [texts->at(curEntityId) removeFromSuperview];
            texts->erase(curEntityId);
            goto restartIteration3;
        }
    }
    
restartIteration4:
    for (auto it = buttons->begin(); it != buttons->end(); it++) {
        string curEntityId = it->first;
        
        if (entities->find(curEntityId) == entities->end()) {
            [buttons->at(curEntityId) removeFromSuperview];
            buttons->erase(curEntityId);
            goto restartIteration4;
        }
    }
    
restartIteration5:
    for (auto it = textFields->begin(); it != textFields->end(); it++) {
        string curEntityId = it->first;
        
        if (entities->find(curEntityId) == entities->end()) {
            [textFields->at(curEntityId) removeFromSuperview];
            textFields->erase(curEntityId);
            goto restartIteration5;
        }
    }
    
restartIteration6:
    for (auto it = images->begin(); it != images->end(); it++) {
        string curEntityId = it->first;
        
        if (entities->find(curEntityId) == entities->end()) {
            [images->at(curEntityId) removeFromParent];
            images->erase(curEntityId);
            goto restartIteration6; // We have to restart the loop, because changing the element of unordered_map while iterating it caused EXC_BAD_ACCESS exception (likely because of concurrent accessing)
        }
    }
}

@end