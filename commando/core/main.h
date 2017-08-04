#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <thread>
#include <ctime>
#include <unistd.h>
#include <chrono>

using namespace std;

#include "utils.h"

#include "engine.h"
#include "time.h"
#include "input.h"
#include "screen.h"
#include "network.h"

#include "entity.h"

#include "icomponent.h"
#include "path_controller_component.h"
#include "physics_component.h"
#include "sprite_component.h"
#include "animator_component.h"
#include "transform_component.h"

#include "button_component.h"
#include "text_component.h"
#include "text_field_component.h"
#include "image_component.h"

#include "isystem.h"
#include "path_system.h"
#include "physics_system.h"
#include "movement_system.h"
#include "script_system.h"
#include "sprite_animation_system.h"
#include "time_system.h"

#include "iscript.h"
#include "player_controller_script.h"
#include "camera_controller_script.h"
#include "tank_controller_script.h"
#include "bullet_controller_script.h"
#include "joystick_script.h"

#include "iscene.h"
#include "scene_login.h"
#include "scene_commando.h"

extern Engine *gEngine;
#define INIT_SCENE SceneLogin

//=================================================================================
// General
//=================================================================================
#define FPS
#define ID_LEN 20
#define PI 3.14159265359
#define MAX_LEN_BUF 1000

#define Z_SCALE_2D 1

//=================================================================================
// Commando
//=================================================================================
#define PLAYER_SPEED 70

#define TANK_FIRE_INTERVAL 2

#define BULLET_SPEED 300

#define SCORETEXT_WIDTH 200
#define SCORETEXT_HEIGHT 40
#define SCORETEXT_FONT_SIZE 25

#define RESTART_BUTTON_WIDTH 60
#define RESTART_BUTTON_HEIGHT 60

#define LOGIN_BUTTON_WIDTH 60
#define LOGIN_BUTTON_HEIGHT 60

#define ID_FIELD_FONT_SIZE 15
#define ID_FIELD_WIDTH 100
#define ID_FIELD_HEIGHT ID_FIELD_FONT_SIZE * 2

#define JOYSTICK_X 70
#define JOYSTICK_Y 70
#define JOYSTICK_RADIUS 40

#define LEVEL_1_WIDTH 640
#define LEVEL_1_HEIGHT 1800

//=================================================================================
// class Entity
//=================================================================================
#define DEFAULT_ENTITY_TAG "unknown"

//=================================================================================
// class PathControllerComponent
//=================================================================================
#define PATH_CONTROLLER_COMPONENT_NAME "PathControllerComponent"

//=================================================================================
// class AnimatorComponent
//=================================================================================
#define ANIMATOR_COMPONENT_NAME "AnimatorComponent"

#define NO_ANIMATION ""

//=================================================================================
// class TransformComponent
//=================================================================================
#define TRANSFORM_COMPONENT_NAME "TransformComponent"

#define DEFAULT_TRANSFORM_COMPONENT_X 0
#define DEFAULT_TRANSFORM_COMPONENT_Y 0
#define DEFAULT_TRANSFORM_COMPONENT_ROTATION 0

//=================================================================================
// class PhysicsComponent
//=================================================================================
#define PHYSICS_COMPONENT_NAME "PhysicsComponent"

//=================================================================================
// class SpriteComponent
//=================================================================================
#define SPRITE_COMPONENT_NAME "SpriteComponent"

#define DEFAULT_SPRITE_COMPONENT_IMAGE_NAME ""

//=================================================================================
// class ScriptComponent
//=================================================================================
#define SCRIPT_COMPONENT_NAME "ScriptComponent"

//=================================================================================
// class TextComponent
//=================================================================================
#define TEXT_COMPONENT_NAME "TextComponent"

#define ALIGNMENT_LEFT 0
#define ALIGNMENT_CENTER 1
#define ALIGNMENT_RIGHT 2

//=================================================================================
// class ButtonComponent
//=================================================================================
#define BUTTON_COMPONENT_NAME "ButtonComponent"

//=================================================================================
// class TextFieldComponent
//=================================================================================
#define TEXTFIELD_COMPONENT_NAME "TextFieldComponent"

//=================================================================================
// class ImageComponent
//=================================================================================
#define IMAGE_COMPONENT_NAME "ImageComponent"

//=================================================================================
// Color Presets
//=================================================================================
#define COLOR_WHITE 256, 256, 256, 256
#define COLOR_BLACK 0, 0, 0, 256

//=================================================================================
// class MovementSystem
//=================================================================================
#define WORLD_FRICTION 0.6
#define SIGNIFICANT_VELOCITY

#endif
