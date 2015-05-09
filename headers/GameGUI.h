/*
 * GameGui.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef GAMEGUI_H_
#define GAMEGUI_H_
#include "Stage.h"
#include "Window.h"
#include "Character.h"
#include "Layer.h"
#include <vector>
#include <iostream>
using namespace std;

class GameGUI {

public:

private:
	static GameGUI *gameGui;
	Stage* stage;
	Window* window;
	vector<Character*> characters;
	vector<Layer*> layers;

	GameGUI() {
		stage = NULL;
		window = NULL;
	}

public:
	static GameGUI* getInstance();
	void clean();
	void setStage(Stage* stage);
	Stage* getStage();
	void setWindow(Window* window);
	Window* getWindow();
	void setCharacters(vector<Character*>);
	vector<Character*> getCharacters();
	void setLayers(vector<Layer*> layers);
	vector<Layer*> getLayers();
	void addCharacter(Character* character);
	void addLayer(Layer* layer);
	~GameGUI() {
		if (gameGui != NULL) delete gameGui;
		gameGui = NULL;
	}
};

#endif /* GAMEGUI_H_ */
