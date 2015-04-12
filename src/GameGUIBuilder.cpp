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

float jsonGetRatio(Json::Value root) {
	Json::Value windowValue = root[JSON_KEY_VENTANA];
	int win_width_px = windowValue.get(JSON_KEY_ANCHOPX, 700).asInt();
	int win_width = windowValue.get(JSON_KEY_ANCHO, 700).asInt();
	float ratio = win_width_px / win_width;
	FILE_LOG(logDEBUG) << "Windows Ratio: " << ratio;
	return ratio;

}

Window jsonGetWindow(Json::Value root) {

	Json::Value windowValue = root[JSON_KEY_VENTANA];
	int win_width_px = windowValue.get(JSON_KEY_ANCHOPX, 700).asInt();
	int win_height_px = windowValue.get(JSON_KEY_ALTOPX, 700).asInt();
	int win_width = windowValue.get(JSON_KEY_ANCHO, 700).asInt();
	FILE_LOG(logDEBUG) << "JSON - Windows width: " << win_width_px << "px";
	FILE_LOG(logDEBUG) << "JSON - Windows height: " << win_height_px << "px";
	FILE_LOG(logDEBUG) << "JSON - Windows width: " << win_width;
	Window window(GAME_TITLE, 100, 100, win_width_px, win_height_px, win_width);
	return window;
}

Stage jsonGetStage(Json::Value root) {
	Json::Value stageValue = root[JSON_KEY_ESCENARIO];
	int stage_width = stageValue.get(JSON_KEY_ANCHO, 700).asInt();
	int stage_win_height = stageValue.get(JSON_KEY_ALTO, 700).asInt();
	int stage_win_ypiso = stageValue.get(JSON_KEY_YPISO, 700).asInt();
	FILE_LOG(logDEBUG) << "JSON - Stage width: " << stage_width;
	FILE_LOG(logDEBUG) << "JSON - Stage height: " << stage_win_height;
	FILE_LOG(logDEBUG) << "JSON - Stage ypiso: " << stage_win_ypiso;
	Stage stage(stage_width, stage_win_height, stage_win_ypiso);
	return stage;
}

void resizeImage(int* width, int win_width_px, int* height, int win_height_px, int stage_width) {
	if (*width < win_width_px) *width = win_width_px;
}

vector<Layer*> jsonGetLayers(Json::Value root, float ratio) {

	Json::Value windowValue = root[JSON_KEY_VENTANA];
	int win_height_px = windowValue.get(JSON_KEY_ALTOPX, 700).asInt();
	int win_width_px = windowValue.get(JSON_KEY_ANCHOPX, 700).asInt();
	int stage_width = GameGUI::getInstance()->getStage().getWidth();

	const Json::Value array = root.get(JSON_KEY_CAPAS,0);
	FILE_LOG(logDEBUG) << "JSON - Number of Layers: " << array.size();
	vector<Layer*> layers;
	string path;
	int width;
	int height;
	for (unsigned int index = 0; index < array.size(); ++index) {
		path = array[index].get(JSON_KEY_IMAGEN_FONDO, "png").asString();
		width = array[index].get(JSON_KEY_ANCHO, 50).asInt();
		height = array[index].get(JSON_KEY_ALTO, 50).asInt();
		resizeImage(&width, win_width_px, &height, win_height_px, stage_width);
		stringstream sLayerName;
		sLayerName.clear();
		sLayerName << "layer";
		sLayerName << index;

		//TODO calcular ratio
		Layer* layer = new Layer(
				new LoaderParams(0, 0, width, win_height_px, index, ratio,
						sLayerName.str()));
		layer->setImagePath(path);
		//Add layers to the game loop
		MKGame::Instance()->getObjectList().push_back(layer);

		FILE_LOG(logDEBUG) << "JSON - Layer ID: " << sLayerName.str();
		FILE_LOG(logDEBUG) << "JSON - Layer" << index << " background image: "
				<< path;
		FILE_LOG(logDEBUG) << "JSON - Layer" << index << " width: "
				<< width;
		layers.push_back(layer);
	}
	return layers;
}

vector<Character*> jsonGetCharacters(Json::Value root, float ratio) {

	Json::Value stageValue = root[JSON_KEY_ESCENARIO];
	int stage_win_ypiso = stageValue.get(JSON_KEY_YPISO, 700).asInt();

	Json::Value characterValue = root[JSON_KEY_PERSONAJE];
	string character_name =
			characterValue.get(JSON_KEY_NOMBRE, "nombre").asString();
	int character_width = characterValue.get(JSON_KEY_ANCHO, 700).asInt();
	int character_height = characterValue.get(JSON_KEY_ALTO, 700).asInt();
	int character_zindex = characterValue.get(JSON_KEY_ZINDEX, 700).asInt();
	string character_orientation = characterValue.get(JSON_KEY_ORIENTACION,
			"right").asString();

	FILE_LOG(logDEBUG) << "JSON - Character name: " << character_name;
	FILE_LOG(logDEBUG) << "JSON - Character width: " << character_width;
	FILE_LOG(logDEBUG) << "JSON - Character height: " << character_height;
	FILE_LOG(logDEBUG) << "JSON - Character z-index: " << character_zindex;
	FILE_LOG(logDEBUG) << "JSON - Character orientation: " << character_orientation;

	vector<Character*> characters;
	Character* playerOne = new Character(
			new LoaderParams(0, stage_win_ypiso, character_width, character_height, character_zindex, ratio,
					character_name));


	//Add player to the game loop
	playerOne->setImagePath("images/spritesheets_subzero/");
	MKGame::Instance()->getObjectList().push_back(playerOne);

	characters.push_back(playerOne);
	return characters;
}

//TODO Fixme
GameGUI* GameGUIBuilder::create() {

	GameGUI *gameGUI = GameGUI::getInstance();

	Json::Value root;
	Json::Reader reader;

	//TODO refactor harcoded file path
	ifstream gameConfig("src/stageConfig.json", std::ifstream::binary);

	if (!gameConfig.good()) {
		MessageError fileNotFound(ERROR_FILE_NOT_FOUND, FILE_CONFIG_NOT_FOUND,
				LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(fileNotFound);
		return createDefault();
	}

	bool parsingSuccessful = reader.parse(gameConfig, root, false);
	if (!parsingSuccessful) {
		MessageError parseException(ERROR_PARSER_JSON,
				reader.getFormattedErrorMessages(), LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(parseException);
	}

	float ratio = jsonGetRatio(root);

	Window window = jsonGetWindow(root);

	Stage stage = jsonGetStage(root);

	vector<Layer*> layers = jsonGetLayers(root, ratio);

	vector<Character*> characters = jsonGetCharacters(root, ratio);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);
	gameGUI->setCharacters(characters);
	gameGUI->setLayers(layers);

	LayerManager::Instance()->init();

	return gameGUI;

}

GameGUI* GameGUIBuilder::createDefault() {

	GameGUI *gameGUI = GameGUI::getInstance();

	Window window(GAME_TITLE, 100, 100, DEFAULT_WINDOW_WIDTH_PX,
			DEFAULT_WINDOW_HEIGHT_PX, DEFAULT_WINDOW_WIDTH);
	Stage stage(DEFAULT_STAGE_WIDTH, DEFAULT_STAGE_HEIGHT,
			DEFAULT_STAGE_YFLOOR);

	float ratio = DEFAULT_WINDOW_WIDTH_PX / DEFAULT_WINDOW_WIDTH;
	vector<Character*> characters;
	Character* character = new Character(
			new LoaderParams(0, 0, 128, 82, 2, ratio, "scorpion"));

	//Add layers to the game loop
	MKGame::Instance()->getObjectList().push_back(character);

	characters.push_back(character);

	vector<Layer*> layers;
	Layer* layer = new Layer(
			new LoaderParams(0, 0, 128, 82, 1, ratio, "layer1"));
	layers.push_back(layer);
	Layer* layer2 = new Layer(
			new LoaderParams(0, 0, 128, 82, 2, ratio, "layer2"));
	layers.push_back(layer2);

	//Add layers to the game loop
	MKGame::Instance()->getObjectList().push_back(layer);
	MKGame::Instance()->getObjectList().push_back(layer2);

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

