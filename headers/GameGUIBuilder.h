/*
 * GameGuiBuilder.h
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#ifndef GAMEGUIBUILDER_H_
#define GAMEGUIBUILDER_H_
#include <fstream>
#include <iostream>
#include <json/value.h>
#include <json/json.h>
#include "GameGUI.h"
#include "Constants.h"
#include "Messages.h"

class GameGUIBuilder {
public:
	GameGUIBuilder();
	GameGUI* create();
	GameGUI* createDefault();
	virtual ~GameGUIBuilder();
};

#endif /* GAMEGUIBUILDER_H_ */
