// HOW TO USE
// Change every TemplateScript to NAME_OF_YOUR_SCRIPT
// Change template_script.h to YOUR_SCRIPT_HEADER_FILE_NAME.h

#include "main.h"

#include "template_script.h" // REMOVE THIS

TemplateScript::TemplateScript(Entity *thisEntity) : IScript("TemplateScript", thisEntity) {
}

void TemplateScript::start() {
    // Initialization in here
}

void TemplateScript::update() {
    // Called every frame
}

void TemplateScript::onCollisionEnter(Entity *entity) {
    // Called when collided
}

void TemplateScript::onCollisionExit(Entity *entity) {
    // Called when exiting collided area
}