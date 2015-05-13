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
#include "AlternativeColor.h"
#include "GameInfo.h"
#include "ThrowableObject.h"
using namespace std;

class GameGUIBuilder {
private:
	string configFilePath;

public:

	GameGUIBuilder(string path);
	GameGUIBuilder();
	GameGUI* create();
	GameGUI* createDefault();
	vector<Layer*> buildLayersByDefault(float ratioX, float ratioY, Window* window, Stage* stage);
	void handleError(string msgError);
	virtual ~GameGUIBuilder();
	void setConfigFilePath(string path);

};

#endif /* GAMEGUIBUILDER_H_ */
