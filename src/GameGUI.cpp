/*
 * GameGui.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/GameGUI.h"

bool GameGUI::instanceFlag = false;
GameGUI* GameGUI::gameGui = NULL;
GameGUI* GameGUI::getInstance() {
	if (!instanceFlag) {
		gameGui = new GameGUI();
		instanceFlag = true;
		return gameGui;
	} else {
		return gameGui;
	}
}

void GameGUI::clean(){
	delete window;
	delete stage;

	vector<Character*>::const_iterator itr;

//	for(itr = this->characters.begin(); itr != this->characters.end(); ++itr){
//		delete (*itr);
//	}


	this->characters.erase(characters.begin(), characters.end());
	this->layers.erase(layers.begin(), layers.end());
}

void GameGUI::setWindow(Window* window) {
	this->window = window;
}

void GameGUI::setStage(Stage* stage) {
	this->stage = stage;
}

void GameGUI::setCharacters(vector<Character*> characters) {
	this->characters = characters;
}

void GameGUI::setLayers(vector<Layer*> layers) {
	this->layers = layers;
}

vector<Character*> GameGUI::getCharacters() {
	return this->characters;
}

vector<Layer*> GameGUI::getLayers() {
	return this->layers;
}

Window* GameGUI::getWindow() {
	return this->window;
}

Stage* GameGUI::getStage() {
	return this->stage;
}


