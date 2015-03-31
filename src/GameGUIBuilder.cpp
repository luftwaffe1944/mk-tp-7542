/*
 * StageBuilder.cpp
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#include "../headers/GameGUIBuilder.h"
using namespace std;

GameGUIBuilder::GameGUIBuilder() {
	// TODO Auto-generated constructor stub

}

GameGUIBuilder::~GameGUIBuilder() {
	// TODO Auto-generated destructor stub
}

GameGUI* GameGUIBuilder::create() {

	GameGUI *gameGUI = GameGUI::getInstance();

	Json::Value root;
	Json::Reader reader;

	std::ifstream stage_config("src/stageConfig.json", std::ifstream::binary);

	bool parsingSuccessful = reader.parse(stage_config, root, false);
	if (!parsingSuccessful) {
		// report to the user the failure and their locations in the document.
		cout << reader.getFormatedErrorMessages() << "\n";
	}

	Json::Value windowValue = root[JSON_KEY_VENTANA];
	int win_width_px = windowValue.get(JSON_KEY_ANCHOPX, 700).asInt();
	int win_height_px = windowValue.get(JSON_KEY_ALTOPX, 700).asInt();
	int win_width = windowValue.get(JSON_KEY_ANCHO, 700).asInt();
	Window window(win_width_px, win_height_px, win_width);

	Json::Value stageValue = root[JSON_KEY_ESCENARIO];
	int stage_width = stageValue.get(JSON_KEY_ANCHO, 700).asInt();
	int stage_win_height = stageValue.get(JSON_KEY_ALTO, 700).asInt();
	int stage_win_ypiso = stageValue.get(JSON_KEY_YPISO, 700).asInt();
	Stage stage(stage_width, stage_win_height, stage_win_ypiso);

	const Json::Value array = root[JSON_KEY_CAPAS];
	vector<Layer> layers;
	string backgroundImage;
	int layerWidth;
	for (unsigned int index = 0; index < array.size(); ++index) {
		backgroundImage = array[index].get(JSON_KEY_IMAGEN_FONDO, "png").asString();
		layerWidth = array[index].get(JSON_KEY_ANCHO, 50).asInt();
		Layer layer(backgroundImage, layerWidth);
		layers.push_back(layer);
	}

	Json::Value characterValue = root[JSON_KEY_PERSONAJE];
	int character_width = characterValue.get(JSON_KEY_ANCHO, 700).asInt();
	int character_height = characterValue.get(JSON_KEY_ALTO, 700).asInt();
	int character_zindex = characterValue.get(JSON_KEY_ZINDEX, 700).asInt();
	vector<Character> characters;
	Character character(character_width, character_height, character_zindex);
	characters.push_back(character);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);
	gameGUI->setCharacters(characters);
	gameGUI->setLayers(layers);

	return gameGUI;

}

