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
//window
#define MAX_WINDOW_WIDTH_PX 1366
#define MAX_WINDOW_HEIGHT_PX 768
#define DEFAULT_WINDOW_WIDTH_PX 640
#define DEFAULT_WINDOW_HEIGHT_PX 480
#define DEFAULT_WINDOW_WIDTH 200
#define WINDOW_MARGIN 4

//stage
#define DEFAULT_STAGE_WIDTH 1000
#define DEFAULT_STAGE_HEIGHT 150
#define DEFAULT_STAGE_YFLOOR 20

//layers
#define DEFAULT_LAYER1_ID "layer0"
#define DEFAULT_LAYER1_PATH "images/arenas/p_3n.png"
#define DEFAULT_LAYER1_WIDTH 206
#define DEFAULT_LAYER2_ID "layer1"
#define DEFAULT_LAYER2_PATH "images/arenas/p_2n.png"
#define DEFAULT_LAYER2_WIDTH 237.43
#define DEFAULT_LAYER3_ID "layer2"
#define DEFAULT_LAYER3_PATH "images/arenas/p_1n.png"
#define DEFAULT_LAYER3_WIDTH 342.85

//characters
#define DEFAULT_CHARACTER_WIDTH 20
#define DEFAULT_CHARACTER_HEIGHT 28.57
#define DEFAULT_CHARACTER_ZINDEX 99
#define DEFAULT_CHARACTER_ORIENTATION "right"
#define STANCE "stance"
#define JUMPING_MOVEMENT "jumping"
#define JUMPING_RIGHT_MOVEMENT "jumping_right"
#define JUMPING_LEFT_MOVEMENT "jumping_left"
#define WALKING_RIGHT_MOVEMENT "walkingRight"
#define WALKING_LEFT_MOVEMENT "walkingLeft"
#define DUCKING_MOVEMENT "ducking"

//Movement suffixes
#define WALK_SUFFIX "Walk"
#define STANCE_SUFFIX "Stance"
#define JUMP_SUFFIX "Jump"
#define JUMP_DIAGONAL_SUFFIX "JumpDiagonal"
#define DUCK_SUFFIX "Duck"
//Commons Strings
#define EMPTY_STRING ""
#define WHITE_SPACE " "


//Sprites images
const string WALK_SPRITE = "/walk.png";
const string JUMP_SPRITE = "/jump.png";
const string STANCE_SPRITE = "/stance.png";
const string DIAGONAL_JUMP_SPRITE = "/diagonalJump.png";
const string DUCK_SPRITE = "/duck.png";
const string DEFAULT_PATH_SPRITE_CONTAINER = "default";

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
#define JSON_KEY_ZINDEX "zindex"
#define JSON_KEY_ORIENTACION "orientacion"

#define SPRITE_WIDTH 100
#define SPRITE_HEIGHT 135

#endif /* CONSTANTS_H_ */
