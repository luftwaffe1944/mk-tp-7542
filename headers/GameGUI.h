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
using namespace std;

class GameGUI {

public:

private:
	static bool instanceFlag;
	static GameGUI *gameGui;
	GameGUI() {
		//private constructor
	}
	Stage* stage;
	Window* window;
	vector<Character*> characters;
	vector<Layer*> layers;

public:
	static GameGUI* getInstance();
	void clean();
	~GameGUI() {
		instanceFlag = false;
	}
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
};

#endif /* GAMEGUI_H_ */
