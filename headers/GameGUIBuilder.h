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
#include <vector>
#include <json/value.h>
#include <json/json.h>
#include "GameGUI.h"
#include "Constants.h"
#include "Messages.h"
#include "MessageError.h"
#include "MKGame.h"
#include "LoaderParams.h"
#include "Log.h"
#include <json/reader.h>
#include "LayerManager.h"

class GameGUIBuilder {
public:

	GameGUIBuilder();
	GameGUI* create();
	GameGUI* createDefault();
	void handleError(string msgError);
	virtual ~GameGUIBuilder();

};

#endif /* GAMEGUIBUILDER_H_ */
