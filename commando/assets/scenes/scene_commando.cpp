#include "main.h"

SceneCommando::SceneCommando() {
}

void SceneCommando::start() {
    //========= mainCamera =============
    
    Entity *mainCamera = new Entity("mainCamera");
    mainCamera->add(new TransformComponent(Screen::width / 2, Screen::height / 2, 10, 1, 1, 0));
    
    gEngine->addEntity(mainCamera);
    
    //==================================
    
    
    //====== background ============
    
    Entity *background = new Entity();
    background->add(new TransformComponent(LEVEL_1_WIDTH / 2, LEVEL_1_HEIGHT / 2, -1, LEVEL_1_WIDTH, LEVEL_1_HEIGHT, 0));
    background->add(new SpriteComponent("level_1_background_0000"));
    
    gEngine->addEntity(background);
    
    //=================================
    
    
    //=========== tank1 =============
    
    Entity *tank1 = new Entity("tank");
    tank1->add(new TransformComponent(200, 500, 2, 50, 25, 270));
    tank1->add(new SpriteComponent("tank_0000"));
    tank1->add(new PhysicsComponent(1, 1, 1));
    
    TankControllerScript *tankControllerScript = new TankControllerScript(tank1);
    tank1->addScript(tankControllerScript);
    
    gEngine->addEntity(tank1);
    
    //===============================
    
    
    //========== player ============
    
    Entity *player = new Entity("player");
    player->add(new TransformComponent(Screen::width / 2, Screen::height / 2, 1, 30, 20, 90));
    player->add(new SpriteComponent("player_0000"));
    player->add(new PhysicsComponent(1, 1, 1));
    
    
    AnimatorComponent *playerAnimatorComp = new AnimatorComponent();
    
    //=== playerWalkAnimation ===
    vector<string> *playerWalkAnimFrames = new vector<string>();
    for (int i = 2; i < 8; i++) {
        char cStrBuffer[256]; sprintf(cStrBuffer, "player_%04d", i);
        string animFrameName = cStrBuffer;
        
        playerWalkAnimFrames->push_back(animFrameName);
    }
    playerAnimatorComp->addAnim( new Animation("playerWalkAnimation", playerWalkAnimFrames, 5) );
    //===========================
    
    //=== playerFireAnimation ===
    vector<string> *playerShootAnimFrames = new vector<string>();
    for (int i = 0; i < 2; i++) {
        char cStrBuffer[256]; sprintf(cStrBuffer, "player_%04d", i);
        string animFrameName = cStrBuffer;
        
        playerShootAnimFrames->push_back(animFrameName);
    }
    playerAnimatorComp->addAnim( new Animation("playerFireAnimation", playerShootAnimFrames, 5) );
    //===========================
    
    //=== playerIdleAnimation ===
    vector<string> *playerIdleAnimFrames = new vector<string>();
    for (int i = 5; i < 6; i++) {
        char cStrBuffer[256]; sprintf(cStrBuffer, "player_%04d", i);
        string animFrameName = cStrBuffer;
        
        playerIdleAnimFrames->push_back(animFrameName);
    }
    playerAnimatorComp->addAnim( new Animation("playerIdleAnimation", playerIdleAnimFrames, 5) );
    //===========================
    
    playerAnimatorComp->setAnim("playerIdleAnimation");
    player->add(playerAnimatorComp);
    
    
    PlayerControllerScript *playerControllerScript = new PlayerControllerScript(player);
    player->addScript(playerControllerScript);
    
    gEngine->addEntity(player);
    
    //=================================
    
    
    //======= shootButton ==============
    
    Entity *fireButton = new Entity();
    
    fireButton->add(new TransformComponent(Screen::width - 55, 50, 0, 70, 70, 0));
    
    ButtonComponent *fireButtonBtnComp = new ButtonComponent("pistol_0000");
    fireButtonBtnComp->addTrigger([playerAnimatorComp, player]{
        
        TransformComponent *transformComp = (TransformComponent *)player->get("TransformComponent");
        
        playerAnimatorComp->setAnim("playerFireAnimation");
        
        //=============== bullet =====================
        
        Entity *bullet = new Entity("playerBullet");
        bullet->add(new TransformComponent(transformComp->x, transformComp->y, 4, 5, 5, transformComp->rotation));
        bullet->add(new SpriteComponent("bullet_0"));
        bullet->add(new PhysicsComponent());
        ((PhysicsComponent *) bullet->get("PhysicsComponent"))->velocity = BULLET_SPEED;
        
        BulletControllerScript *bulletControllerScript = new BulletControllerScript(bullet);
        bullet->addScript(bulletControllerScript);
        
        gEngine->addEntity(bullet);
        
        //============================================
        
    });
    fireButton->add(fireButtonBtnComp);
    
    gEngine->addEntity(fireButton);
    
    //==================================
    
    
    //=========joystickBackground============
    
    Entity *joystickBackground = new Entity("");
    joystickBackground->add(new TransformComponent(JOYSTICK_X, JOYSTICK_Y, 20, 80, 80, 0));
    joystickBackground->add(new ImageComponent("joystick_background_0000"));
    
    gEngine->addEntity(joystickBackground);
    
    //==================================
    
    
    //=========joystickStick============
    
    Entity *joystickStick = new Entity("");
    joystickStick->add(new TransformComponent(JOYSTICK_X, JOYSTICK_Y, 21, 40, 40, 0));
    joystickStick->add(new ImageComponent("joystick_stick_0000"));
    
    JoystickScript *joystickScript = new JoystickScript(joystickStick);
    joystickScript->player = player;
    joystickScript->mainCamera = mainCamera;
    joystickStick->addScript(joystickScript);
    
    gEngine->addEntity(joystickStick);
    
    //==================================
    
    
    
    CameraControllerScript *cameraControllerScript = new CameraControllerScript(mainCamera);
    cameraControllerScript->player = player;
    mainCamera->addScript(cameraControllerScript);
}