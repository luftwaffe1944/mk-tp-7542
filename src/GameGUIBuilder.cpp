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

	//TODO refactor harcoded file path
	ifstream gameConfig("src/stageConfig.json", std::ifstream::binary);

	if (!gameConfig.good()) {
		MessageError fileNotFound(ERROR_FILE_NOT_FOUND, FILE_CONFIG_NOT_FOUND, LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(fileNotFound);
		return createDefault();
	}

	bool parsingSuccessful = reader.parse(gameConfig, root, false);
	if (!parsingSuccessful) {
		MessageError parseException(ERROR_PARSER_JSON, reader.getFormattedErrorMessages(), LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(parseException);
	}

	Json::Value windowValue = root[JSON_KEY_VENTANA];
	int win_width_px = windowValue.get(JSON_KEY_ANCHOPX, 700).asInt();
	int win_height_px = windowValue.get(JSON_KEY_ALTOPX, 700).asInt();
	int win_width = windowValue.get(JSON_KEY_ANCHO, 700).asInt();
	FILE_LOG(logDEBUG) << "JSON - Windows width: " << win_width_px << "px";
	FILE_LOG(logDEBUG) << "JSON - Windows height: " << win_height_px << "px";
	FILE_LOG(logDEBUG) << "JSON - Windows width: " << win_width;
	Window window(GAME_TITLE,100,100,win_width_px, win_height_px, win_width);

	Json::Value stageValue = root[JSON_KEY_ESCENARIO];
	int stage_width = stageValue.get(JSON_KEY_ANCHO, 700).asInt();
	int stage_win_height = stageValue.get(JSON_KEY_ALTO, 700).asInt();
	int stage_win_ypiso = stageValue.get(JSON_KEY_YPISO, 700).asInt();
	FILE_LOG(logDEBUG) << "JSON - Stage width: " << stage_width;
	FILE_LOG(logDEBUG) << "JSON - Stage height: " << stage_win_height;
	FILE_LOG(logDEBUG) << "JSON - Stage ypiso: " << stage_win_ypiso;
	Stage stage(stage_width, stage_win_height, stage_win_ypiso);

	const Json::Value array = root[JSON_KEY_CAPAS];
	vector<Layer> layers;
	string backgroundImage;
	int layerWidth;
	for (unsigned int index = 0; index < array.size(); ++index) {
		backgroundImage =
				array[index].get(JSON_KEY_IMAGEN_FONDO, "png").asString();
		layerWidth = array[index].get(JSON_KEY_ANCHO, 50).asInt();
		FILE_LOG(logDEBUG) << "JSON - Layer" << index << " background image: " << backgroundImage;
		FILE_LOG(logDEBUG) << "JSON - Layer" << index << " width: " << layerWidth;
		Layer layer(backgroundImage, layerWidth, index);
		layers.push_back(layer);
	}

	Json::Value characterValue = root[JSON_KEY_PERSONAJE];
	int character_width = characterValue.get(JSON_KEY_ANCHO, 700).asInt();
	int character_height = characterValue.get(JSON_KEY_ALTO, 700).asInt();
	int character_zindex = characterValue.get(JSON_KEY_ZINDEX, 700).asInt();
	string character_orientation = characterValue.get(JSON_KEY_ORIENTACION, "right").asString();

	FILE_LOG(logDEBUG) << "JSON - Character width: " << character_width;
	FILE_LOG(logDEBUG) << "JSON - Character height: " << character_height;
	FILE_LOG(logDEBUG) << "JSON - Character z-index: " << character_zindex;
	FILE_LOG(logDEBUG) << "JSON - Character orientation: " << character_orientation;

	vector<Character> characters;
	Character character(character_width, character_height, character_zindex, character_orientation);
	characters.push_back(character);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);
	gameGUI->setCharacters(characters);
	gameGUI->setLayers(layers);

	return gameGUI;

}

GameGUI* GameGUIBuilder::createDefault() {

	GameGUI *gameGUI = GameGUI::getInstance();

	Window window(DEFAULT_WINDOW_WIDTH_PX, DEFAULT_WINDOW_HEIGHT_PX,
	DEFAULT_WINDOW_WIDTH);
	Stage stage(DEFAULT_STAGE_WIDTH, DEFAULT_STAGE_HEIGHT,
	DEFAULT_STAGE_YFLOOR);

	vector<Character> characters;
	Character character(DEFAULT_CHARACTER_WIDTH, DEFAULT_CHARACTER_HEIGHT,
	DEFAULT_CHARACTER_ZINDEX, DEFAULT_CHARACTER_ORIENTATION);
	characters.push_back(character);

	vector<Layer> layers;
	Layer layer(DEFAULT_LAYER1_IMAGE, DEFAULT_LAYER1_WIDTH, 0);
	layers.push_back(layer);
	Layer layer2(DEFAULT_LAYER2_IMAGE, DEFAULT_LAYER2_WIDTH, 1);
	layers.push_back(layer2);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);
	gameGUI->setCharacters(characters);
	gameGUI->setLayers(layers);

	return gameGUI;

}

void GameGUIBuilder::handleError(string msgError) {

	//TODO log msg in level ERROR
	cout << msgError << endl;

}

