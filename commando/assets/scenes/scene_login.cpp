#include "main.h"

SceneLogin::SceneLogin() {
}

void SceneLogin::start() {
    //========= mainCamera =============
    
    Entity *mainCamera = new Entity("mainCamera");
    mainCamera->add(new TransformComponent(Screen::width / 2, Screen::height / 2, 10, 1, 1, 1));
    
    gEngine->addEntity(mainCamera);
    
    
    //==================================
    
    
    
    
    //======== idField =================
    
    Entity *idField = new Entity();
    
    idField->add(new TransformComponent(Screen::width / 2 + 30, Screen::height - 200, 0, ID_FIELD_WIDTH, ID_FIELD_HEIGHT, 1));
    idField->add(new TextFieldComponent("Enter anything", "Arial", ID_FIELD_FONT_SIZE));
    
    gEngine->addEntity(idField);
    
    //==================================
    
    
    //====== idText =================
    
    Entity *idText = new Entity();
    idText->add(new TransformComponent(Screen::width / 2 - 50, Screen::height - 200, 0, 30, 20 * 2, 1));
    idText->add(new TextComponent("ID", "C64 Pro", 20, ALIGNMENT_CENTER, COLOR_WHITE));
    
    gEngine->addEntity(idText);
    
    //=================================
    
    
    
    
    //======== passwordField ===========
    Entity *passwordField = new Entity();
    
    passwordField->add(new TransformComponent(Screen::width / 2 + 30, Screen::height - 240, 0, ID_FIELD_WIDTH, ID_FIELD_HEIGHT, 1));
    passwordField->add(new TextFieldComponent("Enter anything", "Arial", ID_FIELD_FONT_SIZE, true));
    
    gEngine->addEntity(passwordField);
    
    //==================================
    
    
    //====== passwordText =================
    
    Entity *passwordText = new Entity();
    passwordText->add(new TransformComponent(Screen::width / 2 - 90, Screen::height - 240, 0, 110, 20 * 2, 1));
    passwordText->add(new TextComponent("PASSWD", "C64 Pro", 20, ALIGNMENT_CENTER, COLOR_WHITE));
    
    gEngine->addEntity(passwordText);
    
    //=================================
    
    
    
    
    //======= loginButton ==============
    
    Entity *loginButton = new Entity();
    
    loginButton->add(new TransformComponent(Screen::width - 40, Screen::height - 220, 0, LOGIN_BUTTON_WIDTH, LOGIN_BUTTON_HEIGHT, 1));
    
    ButtonComponent *loginButtonBtnComp = new ButtonComponent("LoginButton");
    loginButtonBtnComp->addTrigger([idField, passwordField]{
        
        if (((TextFieldComponent *)idField->get("TextFieldComponent"))->text != "" &&
            ((TextFieldComponent *)passwordField->get("TextFieldComponent"))->text != "") {
        
            string userId = ((TextFieldComponent *)idField->get("TextFieldComponent"))->text;
            string password = ((TextFieldComponent *)passwordField->get("TextFieldComponent"))->text;
            
            Network::sendRequest("login", userId, password);
            
            gEngine->loadScene(new SceneCommando());
        }
        
    });
    loginButton->add(loginButtonBtnComp);
    
    gEngine->addEntity(loginButton);
    
    //=================================
}