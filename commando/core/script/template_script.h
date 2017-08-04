#ifndef TEMPLATE_SCRIPT_H
#define TEMPLATE_SCRIPT_H

class IScript;

class TemplateScript : public IScript {
private:
public:
    TemplateScript(Entity *thisEntity);
    
    void start();
    void update();
    void onCollisionEnter(Entity *entity);
    void onCollisionExit(Entity *entity);
};

#endif
