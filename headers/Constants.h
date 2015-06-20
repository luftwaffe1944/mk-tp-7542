/*
 * Constants.h
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#define GAME_TITLE "Mortal Kombat"
//Default GameGUI measures
#include <string>
using namespace std;
//screen
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Parameters for Special Moves
#define TIME_TOLERANCE_SPECIAL_MOVES 5 //seconds
#define ERROR_TOLERANCE_SPECIAL_MOVES 2 //quantity
#define SIMBOLS_TO_SHOW_SPECIAL_MOVES 10 //quantity

#define CHARACTER_FOR_SPECIAL_MOVE_UP "U"
#define CHARACTER_FOR_SPECIAL_MOVE_DOWN "D"
#define CHARACTER_FOR_SPECIAL_MOVE_LEFT "L"
#define CHARACTER_FOR_SPECIAL_MOVE_RIGHT "R"
#define CHARACTER_FOR_SPECIAL_MOVE_FIRE "F"
#define CHARACTER_FOR_SPECIAL_MOVE_BLOCK "B"
#define CHARACTER_FOR_SPECIAL_MOVE_KICKHIGH "K"
#define CHARACTER_FOR_SPECIAL_MOVE_KICKLOW "H"
#define CHARACTER_FOR_SPECIAL_MOVE_PUNCHHIGH "P"
#define CHARACTER_FOR_SPECIAL_MOVE_PUNCHLOW "J"

#define SECUENCE_FOR_SPECIAL_MOVE_0 "KKKK"
#define SECUENCE_FOR_SPECIAL_MOVE_1 "DKP"
#define SECUENCE_FOR_SPECIAL_MOVE_2 "UDJ"
#define SECUENCE_FOR_SPECIAL_MOVE_3 "PPPP"


#define FALATITY_NUMBER_SPECIAL_MOVE 10


//Draw collitionable boxes
const bool DRAW_COLLITIONABLE_BOXES = false;

//Throwable Speed Object
#define OBJECT_SPEED 120

//IA
#define IDLE_CHANCE 100

//Sounds
#define SFX_JUMP "../sounds/sfx/0897.ogg"

//Joystick
#define MAX_XAXIS 32000 //max 32767
#define MAX_YAXIS 32000
#define MIN_XAXIS -32000 //min -32768
#define MIN_YAXIS -32000

//window
#define MAX_WINDOW_WIDTH_PX 1366
#define MAX_WINDOW_HEIGHT_PX 768
#define DEFAULT_WINDOW_WIDTH_PX 640
#define DEFAULT_WINDOW_HEIGHT_PX 480
#define DEFAULT_WINDOW_WIDTH 150
#define WINDOW_MARGIN 4

//stage
#define DEFAULT_STAGE_WIDTH 400
#define DEFAULT_STAGE_HEIGHT 167
#define DEFAULT_STAGE_YFLOOR 151//125

//layers
const float FRONTAL_LAYER_SPEED = 2;
#define DEFAULT_LAYER1_ID "layer0"
#define DEFAULT_LAYER1_PATH "images/arenas/default/p_3n.png"
#define DEFAULT_LAYER1_WIDTH 206
#define DEFAULT_LAYER2_ID "layer1"
#define DEFAULT_LAYER2_PATH "images/arenas/default/p_2n.png"
#define DEFAULT_LAYER2_WIDTH 237.43
#define DEFAULT_LAYER3_ID "layer2"
#define DEFAULT_LAYER3_PATH "images/arenas/default/p_1n.png"
#define DEFAULT_LAYER3_WIDTH 342.85

//characters
#define MARGIN_BETWEEN_CHARACTERS 4
#define DEFAULT_CHARACTER_WIDTH 55
#define DEFAULT_CHARACTER_HEIGHT 70
#define DEFAULT_CHARACTER_ZINDEX 99
#define DEFAULT_CHARACTER_ORIENTATION "right"
#define STANCE "stance"
#define JUMPING_MOVEMENT "jumping"
#define JUMPING_RIGHT_MOVEMENT "jumping_right"
#define JUMPING_LEFT_MOVEMENT "jumping_left"
#define WALKING_RIGHT_MOVEMENT "walkingRight"
#define WALKING_LEFT_MOVEMENT "walkingLeft"
#define DUCKING_MOVEMENT "ducking"
#define PUNCHING_HIGH_MOVEMENT "punchingHigh"
#define PUNCHING_LOW_MOVEMENT "punchingLow"
#define PUNCHING_DUCK_MOVEMENT "punchingDuck"
#define UPPERCUT_MOVEMENT "uppercut"
#define LOW_KICK_MOVEMENT "lowKick"
#define HIGH_KICK_MOVEMENT "highKick"
#define DUCK_LOW_KICK_MOVEMENT "duckLowKick"
#define DUCK_HIGH_KICK_MOVEMENT "duckHighKick"
#define SUPER_KICK_MOVEMENT "superKick"
#define AIR_HIGH_kICK_MOVEMENT "airHighKick"
#define AIR_LOW_kICK_MOVEMENT "airLowKick"
#define BLOCK_MOVEMENT "block"
#define DUCK_BLOCK_MOVEMENT "duckBlock"
#define UNDER_KICK_MOVEMENT "underKick"
#define AIR_PUNCH_MOVEMENT "airPunch"
#define BEING_HINT_STANCE_UP_MOVEMENT "beingHintStanceUp"
#define BEING_HINT_STANCE_DOWN_MOVEMENT "beingHintStanceDown"
#define BEING_HINT_FALLING_UNDER_KICK_MOVEMENT "beingHintFallingUnderKick"
#define HINT_FLYING_MOVEMENT "hintFlying"
#define HINT_FLYING_UPPER_MOVEMENT "hintFlyingUpper"
#define GET_UP_MOVEMENT "getUp"
#define SWEEP_MOVEMENT "sweep"
#define FIRE_MOVEMENT "fire"
#define BABALITY_MOVEMENT "babality"
#define FATALITY_MOVEMENT "fatality"
#define HEADLESS_MOVEMENT "headless"
#define HEADLESS_BLOOD_MOVEMENT "headless_blood"
#define BURNING_MOVEMENT "burning"
#define LAZY_MOVEMENT "lazy"
#define FRIENDSHIP_MOVEMENT "friendship"
#define VICTORY_MOVEMENT "victory"
#define REPTILE_MOVEMENT "reptile"
#define JUMPING_X_SPEED 4
#define SWEEP_X_SPEED 8

//Movement suffixes
#define WALK_SUFFIX "Walk"
#define STANCE_SUFFIX "Stance"
#define JUMP_SUFFIX "Jump"
#define JUMP_DIAGONAL_SUFFIX "JumpDiagonal"
#define DUCK_SUFFIX "Duck"
#define HI_PUNCH_SUFFIX "Hi_Punch"
#define LO_PUNCH_SUFFIX "Lo_Punch"
#define DUCK_PUNCH_SUFFIX "Duck_Punch"
#define UPPERCUT_SUFFIX "Uppercut"
#define LOW_KICK_SUFFIX "lowKick"
#define HIGH_KICK_SUFFIX "highKick"
#define DUCK_LOW_KICK_SUFFIX "duckLowKick"
#define DUCK_HIGH_KICK_SUFFIX "duckHighKick"
#define SUPER_KICK_SUFFIX "superKick"
#define AIR_HIGH_kICK_SUFFIX "airHighKick"
#define AIR_LOW_kICK_SUFFIX "airLowKick"
#define BLOCK_SUFFIX "block"
#define DUCK_BLOCK_SUFFIX "duckBlock"
#define UNDER_KICK_SUFFIX "underKick"
#define AIR_PUNCH_SUFFIX "airPunch"
#define BEING_HINT_STANCE_UP_SUFFIX "beingHintStanceUp"
#define BEING_HINT_STANCE_DOWN_SUFFIX "beingHintStanceDown"
#define BEING_HINT_FALLING_UNDER_KICK_SUFFIX "beingHintFallingUnderKick"
#define HINT_FLYING_SUFFIX "hintFlying"
#define GET_UP_SUFFIX "getUp"
#define SWEEP_SUFFIX "sweep"
#define FIRE_SUFFIX "fire"
#define BABALITY_SUFFIX "babality"
#define FATALITY_SUFFIX "fatality"
#define HEADLESS_SUFFIX "headless"
#define HEADLESS_BLOOD_SUFFIX "headless_blood"
#define BURNING_SUFFIX "burning"
#define FRIENDSHIP_SUFFIX "friendship"
#define VICTORY_SUFFIX "victory"
#define LAZY_SUFFIX "lazy"
#define REPTILE_SUFFIX "reptile"
//Commons Strings
#define EMPTY_STRING ""
#define WHITE_SPACE " "


//Sprites images
const string WALK_SPRITE = "/walk.png";
const string JUMP_SPRITE = "/jump.png";
const string STANCE_SPRITE = "/stance.png";
const string DIAGONAL_JUMP_SPRITE = "/diagonalJump.png";
const string DUCK_SPRITE = "/singleDuck.png";
const string HIPUNCH_SPRITE = "/highPunch.png";
const string LOPUNCH_SPRITE = "/lowPunch.png";
const string DUCKPUNCH_SPRITE = "/duckPunch.png";
const string UPPERCUT_SPRITE = "/uppercut.png";
const string LOW_KICK_SPRITE = "/lowKick.png";
const string HIGH_KICK_SPRITE = "/highKick.png";
const string DUCK_LOW_KICK_SPRITE = "/duckLowKick.png";
const string DUCK_HIGH_KICK_SPRITE = "/duckHighKick.png";
const string SUPER_KICK_SPRITE = "/superKick.png";
const string AIR_HIGH_KICK_SPRITE = "/airHighKickSingle.png";
const string AIR_LOW_KICK_SPRITE = "/airLowKickSingle.png";
const string DUCK_BLOCK_SPRITE = "/duckBlockSingle.png";
const string BLOCK_SPRITE = "/blockSingle.png";
const string UNDER_KICK_SPRITE = "/underKick.png";
const string AIR_PUNCH_SPRITE = "/airPunch.png";
const string BEING_HINT_STANCE_UP_SPRITE = "/hintStance1.png";
const string BEING_HINT_STANCE_DOWN_SPRITE = "/hintStance2.png";
const string BEING_HINT_FALLING_UNDER_KICK_SPRITE = "/hintFallingUnderKick.png";
const string HINT_FLYING_SPRITE = "/hintSuperDamage2.png";
const string GET_UP_SPRITE ="/getUp.png";
const string SWEEP_SPRITE ="/sweep.png";
const string FIRE_SPRITE = "/fire.png";
const string BABALITY_SPRITE ="/babality.png";
const string FATALITY_SPRITE ="/fatality.png";
const string BURNING_SPRITE ="/burning.png";
const string HEADLESS_SPRITE ="/headless.png";
const string HEADLESS_BLOOD_SPRITE ="/headless_blood.png";
const string FRIENDSHIP_SPRITE ="/friendship.png";
const string VICTORY_SPRITE ="/victory.png";
const string LAZY_SPRITE ="/lazy.png";
const string REPTILE_SPRITE ="/reptile.png";
const string DEFAULT_PATH_SPRITE_CONTAINER = "default";
const string ROOT_IMAGE_PATH = "images/";
const string FIGHT_IMAGE_SPRITE = "images/fight/fight.png";
const string FIGHT2_IMAGE_SPRITE = "images/fight/fight2.png";
const string FINISH_HIM_IMAGE_SPRITE = "images/fight/finishHim.png";
const string FATALITY_IMAGE_SPRITE = "images/fight/fatality.png";
const string LOW_PUNCH = "low_punch";
const string HIGH_PUNCH = "high_punch";
const string LOW_KICK = "low_kick";
const string HIGH_KICK = "high_kick";
const string FIRE = "fire";
const string BLOCK = "block";

// Json config constants

#define JSON_KEY_VENTANA "ventana"
#define JSON_KEY_ANCHOPX "anchopx"
#define JSON_KEY_ALTOPX "altopx"
#define JSON_KEY_ANCHO "ancho"

#define JSON_KEY_ESCENARIO "escenario"
#define JSON_KEY_ALTO "alto"
#define JSON_KEY_YPISO "ypiso"

#define JSON_KEY_CAPAS "capas"
#define JSON_KEY_IMAGEN_FONDO "imagen_fondo"

#define JSON_KEY_NOMBRE "nombre"
#define JSON_KEY_PERSONAJE "personaje"
#define JSON_KEY_PERSONAJES "personajes"
#define JSON_KEY_PELEA "pelea"
#define JSON_KEY_LUCHADOR_1 "luchador1"
#define JSON_KEY_LUCHADOR_2 "luchador2"
#define JSON_KEY_COLOR_ALTERNATIVO "color-alternativo"
#define JSON_KEY_H_INICIAL "h-inicial"
#define JSON_KEY_H_FINAL "h-final"
#define JSON_KEY_DESPLAZAMIENTO "desplazamiento"
#define JSON_KEY_ZINDEX "zindex"
#define JSON_KEY_ORIENTACION "orientacion"

#define JSON_KEY_JOYSTICKS "joysticks"
#define JSON_KEY_HIGH_PUNCH "piña_alta"
#define JSON_KEY_LOW_PUNCH "piña_baja"
#define JSON_KEY_HIGH_KICK "patada_alta"
#define JSON_KEY_LOW_KICK "patada_baja"
#define JSON_KEY_BLOCK "bloquear"
#define JSON_KEY_FIRE "disparar"

#define JSON_KEY_SECUENCES "secuencias"
#define JSON_KEY_SPECIAL_MOVE "secuence_for_special_move"
#define JSON_KEY_TOLERANCE_SECUENCES "tolerancia_secuencias"
#define JSON_KEY_TIME_SECUENCES "tiempo_secuencias"

#define SPRITE_WIDTH 200
#define SPRITE_HEIGHT 170

#endif /* CONSTANTS_H_ */
