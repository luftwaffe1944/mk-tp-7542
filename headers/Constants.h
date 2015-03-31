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

//window
#define DEFAULT_WINDOW_WIDTH_PX 640
#define DEFAULT_WINDOW_HEIGHT_PX 480
#define DEFAULT_WINDOW_WIDTH 640

//stage
#define DEFAULT_STAGE_WIDTH 1000
#define DEFAULT_STAGE_HEIGHT 150
#define DEFAULT_STAGE_YFLOOR 20

//layers
#define DEFAULT_LAYER1_IMAGE "pic1.png"
#define DEFAULT_LAYER1_WIDTH 500
#define DEFAULT_LAYER2_IMAGE "pic2.png"
#define DEFAULT_LAYER2_WIDTH 1000

//characters
#define DEFAULT_CHARACTER_WIDTH 20
#define DEFAULT_CHARACTER_HEIGHT 35
#define DEFAULT_CHARACTER_ZINDEX 1

//Commons Strings
#define EMPTY_STRING ""
#define WHITE_SPACE " "

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

#define JSON_KEY_PERSONAJE "personaje"
#define JSON_KEY_ZINDEX "zindex"

#endif /* CONSTANTS_H_ */
