/*
 * StageBuilder.cpp
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#include "../headers/GameGUIBuilder.h"
#include <cstdlib>

using namespace std;

GameGUIBuilder::GameGUIBuilder() {
	// TODO Auto-generated constructor stub

}

GameGUIBuilder::GameGUIBuilder(string path) {
	this->configFilePath = path;

}

GameGUIBuilder::~GameGUIBuilder() {
	// TODO Auto-generated destructor stub
}

bool fileExists(const char *s)
{
	ifstream archivo(s, std::ifstream::binary);

	if (archivo.good()) {
		return true;
	}else{
		FILE_LOG(logERROR) << "File not found: " << s;
		return false;
	}
}

float getRatio(int dimPx, int dimLg, std::string type) {
	float ratio = (float)dimPx / (float)dimLg;
	if (type == "X"){
		FILE_LOG(logDEBUG) << "RatioX (window_width_px / window_width_lg): " << ratio;
	}else if (type == "Y"){
		FILE_LOG(logDEBUG) << "RatioY (window_height_px / stage_height_lg): " << ratio;
	}
	return ratio;
}

Window* jsonGetWindow(Json::Value root) {

	FILE_LOG(logDEBUG) << "WINDOW CONFIGURATION";
	Json::Value windowValue = root[JSON_KEY_VENTANA];

	int win_width_px;
	int win_height_px;
	int win_width;
	try {
		 string strValue = windowValue.get(JSON_KEY_ANCHOPX, "").asString();
	     win_width_px = atoi(strValue.c_str());
	     FILE_LOG(logDEBUG) << "JSON - Window width: " << strValue << " px";
	}catch(std::exception const & e){
		win_width_px=0;
	}
	try {
		 string strValue = windowValue.get(JSON_KEY_ALTOPX, "").asString();
		 win_height_px = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Window height: " << strValue << " px";
	}catch(std::exception const & e){
		win_height_px=0;
	}
	try {
		 string strValue = windowValue.get(JSON_KEY_ANCHO, 0).asString();
		 win_width = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Window width: " << strValue;
	}catch(std::exception const & e){
		win_width=0;
	}

	//validaciones de parametros para ventana
	bool widthPxOk = ((win_width_px>0) && (win_width_px <=MAX_WINDOW_WIDTH_PX));
	bool heightPxOk = ((win_height_px>0) && (win_height_px <=MAX_WINDOW_HEIGHT_PX));
	bool widthOk =(win_width_px>0);
	if (!widthOk || !widthPxOk || !heightPxOk){
			if (!(win_width>0)){
				FILE_LOG(logWARNING) << "Window logical width out of range or inexistent. Set by default: " <<DEFAULT_WINDOW_WIDTH;
				win_width = DEFAULT_WINDOW_WIDTH;
			}
			if (!widthPxOk) {
				win_width_px=DEFAULT_WINDOW_WIDTH_PX;
				FILE_LOG(logWARNING) << "Window width px out of range or inexistent (" <<"0 - "<< MAX_WINDOW_WIDTH_PX<<"). Set to default:"<<DEFAULT_WINDOW_WIDTH_PX<<" px";
			}
			if (!heightPxOk){
				win_height_px=DEFAULT_WINDOW_HEIGHT_PX;
				FILE_LOG(logWARNING) << "Window height px out of range or inexistent (" <<"0 - "<< MAX_WINDOW_HEIGHT_PX<<"). Set to default:"<<DEFAULT_WINDOW_HEIGHT_PX<<" px";
			}
			FILE_LOG(logWARNING) << "Window size set to: (" << win_width_px<<"-"<<win_height_px<<")";
	}
	//set de posiciones para centrado de ventana en pantalla
	int windowXpos = ((MAX_WINDOW_WIDTH_PX-win_width_px)/2);
	int windowYpos = ((MAX_WINDOW_HEIGHT_PX-win_height_px)/2);

	Window* ptrWindow = new Window(GAME_TITLE, windowXpos, windowYpos, win_width_px, win_height_px, win_width);
	return ptrWindow;
}

Stage* jsonGetStage(Json::Value root, int win_width_lg) {
	FILE_LOG(logDEBUG) << "STAGE CONFIGURATION";
	Json::Value stageValue = root[JSON_KEY_ESCENARIO];

	int stage_width;
	int stage_height;
	int stage_ypiso;

	try {
		 string strValue  = stageValue.get(JSON_KEY_ANCHO, 0).asString();
		 stage_width = atof(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Stage width: " << strValue;
	}catch(std::exception const & e){
		stage_width=0;
	}
	try {
		 string strValue  = stageValue.get(JSON_KEY_ALTO, 0).asString();
		 stage_height = atof(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Stage height: " << stage_height;
	}catch(std::exception const & e){
		stage_height=0;
	}
	try {
		 string strValue = stageValue.get(JSON_KEY_YPISO, 0).asString();
		 stage_ypiso = atof(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Stage ypiso: " << strValue;
	}catch(std::exception const & e){
		stage_ypiso=0;
	}

	//validaciones de parametros para escenario
	bool heightOk = (stage_height>0);
	if (!heightOk){
		stage_height = DEFAULT_STAGE_HEIGHT;
		FILE_LOG(logWARNING) << "Stage logical height out of range or inexistent (must be positive). Set to default:"<<DEFAULT_STAGE_HEIGHT;
	}

	bool yPisoOk = (stage_ypiso>0) && (stage_ypiso<=stage_height);
	if (!yPisoOk){
		//por defecto altura piso es 10% de la altura logica del escenario
		stage_ypiso = (stage_height * 0.91);
		FILE_LOG(logWARNING) << "Stage floor 'y' position out of range or inexistent (0 - "<<stage_height<< "). Set to default:"<<stage_ypiso;
	}

	bool widthOk = (stage_width >=win_width_lg);
	if (!widthOk){
		stage_width = DEFAULT_STAGE_WIDTH;
		FILE_LOG(logWARNING) << "Stage logical width out of range or inexistent (must be higher than window logical width: "<<win_width_lg<< "). Set to default:"<<DEFAULT_STAGE_WIDTH;
	}

	Stage* ptrStage = new Stage(stage_width, stage_height, stage_ypiso);
	return ptrStage;
}

void resizeImage(float* width, float win_width, int stage_width, float widthPiso) {
	*width = (stage_width * (*width)) / widthPiso;
	if (*width < win_width) *width = win_width;
	//if (*width > stage_width) *width = stage_width;
}

vector<Layer*> jsonGetLayers(Json::Value root, float ratioX, float ratioY, Window* window, Stage* stage) {
	FILE_LOG(logDEBUG) << "LAYERS CONFIGURATION";
	const Json::Value array = root.get(JSON_KEY_CAPAS,0);

	FILE_LOG(logDEBUG) << "JSON - Number of Layers to process: " << array.size();
	vector<Layer*> layers;
	string path;
	float width;

	/* PROPORCION USADA PARA AJUSTAR SIZE DE LAS IMAGENES
	 * SIN VALIDAR */
	//float widthPiso = ::atof(array[array.size()-1].get(JSON_KEY_ANCHO, "").asString().c_str());
	///VALIDACION DE PISO
	int indexPiso=-1;
	float widthPiso;
	for (unsigned int index = 0; index < array.size(); ++index) {
		path = array[index].get(JSON_KEY_IMAGEN_FONDO, "").asString();
		if (fileExists(path.c_str())){
			indexPiso = index;
		}
	}
	try {
		 string strValue = array[indexPiso].get(JSON_KEY_ANCHO, "").asString();
		 widthPiso = atof(strValue.c_str());
	}catch(std::exception const & e){
		widthPiso=stage->getWidth();
	}
	///////////////////////////////////////////////////////////////////////////////////////


	for (unsigned int index = 0; index < array.size(); ++index) {
		path = array[index].get(JSON_KEY_IMAGEN_FONDO, "").asString();

		//validar existencia de imagen
		if (fileExists(path.c_str())) {
			try {
				 string strValue = array[index].get(JSON_KEY_ANCHO, "").asString();
				 width = atof(strValue.c_str());

				 FILE_LOG(logDEBUG) << "JSON - Layer "<<index<<" input width: " << strValue;
			}catch(std::exception const & e){
				width=0;
			}
			//validaciones de parametros para layer
			bool widthOk = (width>0);
			if (!widthOk){
				width = stage->getWidth();
				FILE_LOG(logWARNING) << "Layer logical width out of range or inexistent (must be positive). Set by default:"<<stage->getWidth();
			}

			stringstream sLayerName;
			sLayerName.clear();
			sLayerName << "layer";
			sLayerName << index;
			FILE_LOG(logDEBUG) << "JSON - Layer "<< index <<" ID: " << sLayerName.str();
			FILE_LOG(logDEBUG) << "JSON - Layer " << index << " background image: "	<< path;
			FILE_LOG(logDEBUG) << "JSON - Layer " << index << " width: "	<< width;

//			if (index == 0) {widthPiso = width;}
			resizeImage(&width, window->width, stage->getWidth(), widthPiso);
			FILE_LOG(logDEBUG) << "JSON - Layer " << index << " width recalculado: "	<< width;

			//TODO calcular ratio
			Layer* layer = new Layer(new LoaderParams(0, 0, width, window->heightPx / ratioY, index, ratioX, ratioY, sLayerName.str()));
			layer->setImagePath(path);
			//Add layers to the game loop
			MKGame::Instance()->getObjectList().push_back(layer);
			layers.push_back(layer);
		}
	}
	FILE_LOG(logDEBUG) << "JSON - Number of Layers successfully process: " << layers.size();
	return layers;
}

vector<Character*> jsonGetCharacters(Json::Value root, float ratioX, float ratioY, Stage* stage) {
	FILE_LOG(logDEBUG) << "CHARACTERS CONFIGURATION";
	int stage_win_ypiso = stage->getYGround();

	const Json::Value charactersArray = root.get(JSON_KEY_PERSONAJES,0);
	FILE_LOG(logDEBUG) << "JSON - Number of Characters to process: " << charactersArray.size();

	vector<Character*> characters;
	float characterPosX = GameGUI::getInstance()->getWindow()->widthPx / 2;

	for (unsigned int index = 0; index < charactersArray.size(); ++index) {
		Json::Value characterValue = charactersArray[index];
		string character_name;
		float character_width;
		float character_height;
		int character_zindex;
		bool set_default_alternative_color = false;
		double character_alt_color_h_inicial;
		double character_alt_color_h_final;
		double character_alt_color_shift;
		try {
			character_name =	characterValue.get(JSON_KEY_NOMBRE, "").asString();
			FILE_LOG(logDEBUG) << "JSON - Input Character name: " << character_name;
		}catch(std::exception const & e){
			character_name = "subzero"; //TODO: review if it should be "default"
		}
		try {
			 string strValue = characterValue.get(JSON_KEY_ANCHO, "").asString();
			 character_width = atof(strValue.c_str());
			 FILE_LOG(logDEBUG) << "JSON - Input Character width: " << strValue;
		}catch(std::exception const & e){
			character_width=0;
		}
		try {
			 string strValue = characterValue.get(JSON_KEY_ALTO, "").asString();
			 character_height = atof(strValue.c_str());
			 FILE_LOG(logDEBUG) << "JSON - Input Character height: " << strValue;
		}catch(std::exception const & e){
			character_height=0;
		}
		try {
			 string strValue = characterValue.get(JSON_KEY_ZINDEX, "").asString();
			 character_zindex = atoi(strValue.c_str());
			 FILE_LOG(logDEBUG) << "JSON - Input Character z-index: " << strValue;
		}catch(std::exception const & e){
			character_zindex=99;
		}


		try {
			 Json::Value altColorValue = characterValue.get(JSON_KEY_COLOR_ALTERNATIVO, "");
			 FILE_LOG(logDEBUG) << "JSON - tag COLOR-ALTERNATIVO de personaje leido. ";
			 character_alt_color_h_inicial = atof(altColorValue.get(JSON_KEY_H_INICIAL, "").asString().c_str());
			 character_alt_color_h_final = atof(altColorValue.get(JSON_KEY_H_FINAL, "").asString().c_str());
			 character_alt_color_shift = atof(altColorValue.get(JSON_KEY_DESPLAZAMIENTO, "").asString().c_str());
			 FILE_LOG(logDEBUG) << "JSON - tag COLOR-ALTERNATIVO h_inicial leido: " << character_alt_color_h_inicial;
			 FILE_LOG(logDEBUG) << "JSON - tag COLOR-ALTERNATIVO h_final leido: " << character_alt_color_h_final;
			 FILE_LOG(logDEBUG) << "JSON - tag COLOR-ALTERNATIVO desplazamiento leido: " << character_alt_color_shift;

			 if (character_alt_color_h_inicial > character_alt_color_h_final){
				 FILE_LOG(logDEBUG) << "JSON - COLOR-ALTERNATIVO h_inicial mayor a h_final, "
						 "se procede a configurar color alternativo por default";
				 set_default_alternative_color = true;
			 }
		}catch(std::exception const & e) {
			 FILE_LOG(logDEBUG) << "JSON - eeror leyendo COLOR-ALTERNATIVO,  "
					 "se procede a configurar color alternativo por default";
			set_default_alternative_color = true;
		}

		//TODO: Validate against a list of valid characters
		if ((character_name != "subzero") && (character_name != "scorpion")){
			character_name = "subzero";
			FILE_LOG(logWARNING) << "JSON - Invalid character name. Set by default to: " << character_name;
		}
		if (!character_width>0){
			character_width = DEFAULT_CHARACTER_WIDTH;
			FILE_LOG(logDEBUG) << "JSON - Incorrect Character width (must be positive). Set by default: " << DEFAULT_CHARACTER_WIDTH;
		}
		if (!character_height>0){
			character_height = DEFAULT_CHARACTER_HEIGHT;
			FILE_LOG(logDEBUG) << "JSON - Incorrect Character height (must be positive). Set by default: " << DEFAULT_CHARACTER_HEIGHT;
		}
		if (!character_zindex>0){
			character_zindex = DEFAULT_CHARACTER_ZINDEX;
			FILE_LOG(logDEBUG) << "JSON - Incorrect Character z-index (0 - 99). Set by default: " << DEFAULT_CHARACTER_ZINDEX;
		}

		if (set_default_alternative_color){
			 character_alt_color_h_inicial = 40;
			 character_alt_color_h_final = 45;
			 character_alt_color_shift = 30;
		}
		FILE_LOG(logDEBUG) << "Final values for character.";
		FILE_LOG(logDEBUG) << "JSON - Character name: " << character_name;
		FILE_LOG(logDEBUG) << "JSON - Character width: " << character_width;
		FILE_LOG(logDEBUG) << "JSON - Character height: " << character_height;
		FILE_LOG(logDEBUG) << "JSON - Character z-index: " << character_zindex;
		FILE_LOG(logDEBUG) << "JSON - Character alternative color h_inicial: " << character_alt_color_h_inicial;
		FILE_LOG(logDEBUG) << "JSON - Character alternative color h_final: " << character_alt_color_h_final;
		FILE_LOG(logDEBUG) << "JSON - Character alternative color shift: " << character_alt_color_shift;

		float characterPosY = ( stage_win_ypiso - character_height ) * ratioY;
		LoaderParams* characterParams = new LoaderParams(characterPosX  - character_width * ratioX/2, characterPosY, character_width, character_height, character_zindex, ratioX, ratioY, character_name);
		AlternativeColor* altColor = new AlternativeColor(character_alt_color_h_inicial, character_alt_color_h_final, character_alt_color_shift);
		Character* player = new Character(characterParams);
		player->setAlternativeColor(altColor);
		//Add player to the game loop
		//MKGame::Instance()->getObjectList().push_back(player); //TODO: Do it in Fight class
		characters.push_back(player);
	}
	return characters;
}

Fight* jsonGetFight(Json::Value root) {
	FILE_LOG(logDEBUG) << "FIGHT CONFIGURATION";
	Json::Value fightValue = root[JSON_KEY_PELEA];
	Fight* fight = new Fight();
	string fighterOneName;
	string fighterTwoName;

	try {
		 string fighterOneNameValue = fightValue.get(JSON_KEY_LUCHADOR_1, "").asString();
		 fighterOneName = fighterOneNameValue;
		 FILE_LOG(logDEBUG) << "JSON - Input fighter one name: " << fighterOneName;
	}catch(std::exception const & e){
		fighterOneName="subzero";
	}
	try {
		 string fighterTwoNameValue = fightValue.get(JSON_KEY_LUCHADOR_2, "").asString();
		 fighterTwoName = fighterTwoNameValue;
		 FILE_LOG(logDEBUG) << "JSON - Input fighter one name: " << fighterTwoName;
	}catch(std::exception const & e){
		fighterTwoName="subzero";
	}
	vector<Character*> characters = GameGUI::getInstance()->getCharacters();
	bool isFighterOneNameValid = false;
	bool isFighterTwoNameValid = false;
	Character* defaultCharacter;
	if (characters.size() > 0) {
		defaultCharacter = characters[0];
	}

	for (unsigned int index=0; index<characters.size(); index++) {
		Character* character = characters[index];
		if (character->getName() == fighterOneName) {
			Character* fighterOne = character->getCopyInstance();
			fighterOne->setPlayerNumber("1");
			fight->setFighterOne(fighterOne);
			isFighterOneNameValid = true;
		}
		if (character->getName() == fighterTwoName) {
			Character* fighterTwo = character->getCopyInstance();
			fighterTwo->setPlayerNumber("2");
			fighterTwo->setPositionX(fighterTwo->getPositionX() + 120); //TODO: posX character2 hardcoded
			fight->setFighterTwo(fighterTwo);
			isFighterTwoNameValid = true;
		}
	}

	if (!isFighterOneNameValid) {
		FILE_LOG(logDEBUG) << "JSON - Fighter one name is not valid, "
				"default character was set: " << defaultCharacter->getName();
		Character* fighterOne = defaultCharacter->getCopyInstance();
		fighterOne->setPlayerNumber("1");
		fight->setFighterOne(fighterOne);
	}

	if (!isFighterTwoNameValid) {
		FILE_LOG(logDEBUG) << "JSON - Fighter two name is not valid, "
				"default character was set: " << defaultCharacter->getName();
		Character* fighterTwo = defaultCharacter->getCopyInstance();
		fighterTwo->setPlayerNumber("2");
		fighterTwo->setPositionX(fighterTwo->getPositionX() + 120); //TODO: posX character2 hardcoded
		fight->setFighterTwo(fighterTwo);
	}
	return fight;
}

void jsonGetJoysticks(Json::Value root) {

	FILE_LOG(logDEBUG) << "JOYSTICKS CONFIGURATION";

	const Json::Value array = root.get(JSON_KEY_JOYSTICKS,0);
	FILE_LOG(logDEBUG) << "JSON - Number of Joysticks to process: " << array.size();

	vector<map <string,int> > joystickActionButtons;
	string low_punch;
	string high_punch;
	string low_kick;
	string high_kick;
	for (unsigned int joyNum = 0; joyNum < array.size(); ++joyNum) {

		low_punch = array[joyNum].get(JSON_KEY_LOW_PUNCH, "").asString();
		high_punch = array[joyNum].get(JSON_KEY_HIGH_PUNCH, "").asString();
		low_kick = array[joyNum].get(JSON_KEY_LOW_KICK, "").asString();
		high_kick = array[joyNum].get(JSON_KEY_HIGH_KICK, "").asString();

		InputControl::Instance()->setActionButton(joyNum, LOW_PUNCH, atoi(low_punch.c_str()) );
		InputControl::Instance()->setActionButton(joyNum, HIGH_PUNCH, atoi(high_punch.c_str()) );
		InputControl::Instance()->setActionButton(joyNum, LOW_KICK, atoi(low_kick.c_str()) );
		InputControl::Instance()->setActionButton(joyNum, HIGH_KICK, atoi(high_kick.c_str()) );
}

	return;
}

void createGameInfo(Window* window, vector<Character*> characters, float ratioX, float ratioY) {
	float windowWidth = window->getWidth();
	float windowHeight = window->getHeightPx();
	/*
	vector<string> playerName;
	for(unsigned int i = 0; i < characters.size(); ++i ) {
		playerName.push_back(characters[i]->getName());
	}*/
	LoaderParams* params = new LoaderParams(WINDOW_MARGIN, 0, windowWidth, windowHeight * 0.10 , 100, ratioX, ratioY, "gameInfo");
	GameInfo* info = new GameInfo(params, characters);
	MKGame::Instance()->getObjectList().push_back(info);
}

GameGUI* GameGUIBuilder::create() {
	FILE_LOG(logDEBUG) << "CONFIGURATION INITIALIZED";
	GameGUI *gameGUI = GameGUI::getInstance();

	Json::Value root;
	Json::Reader reader;

	ifstream gameConfig(this->configFilePath.c_str(), std::ifstream::binary);

	if (!gameConfig.good()) {
		MessageError fileNotFound(ERROR_FILE_NOT_FOUND, FILE_CONFIG_NOT_FOUND, LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(fileNotFound);
		return createDefault();
	}
	bool parsingSuccessful = reader.parse(gameConfig, root, false);

	if (!parsingSuccessful) {
		MessageError parseException(ERROR_PARSER_JSON, reader.getFormattedErrorMessages(), LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(parseException);
		return createDefault();
	}

	try{
		const Json::Value value1 = root.get(JSON_KEY_PERSONAJES, 0);
		const Json::Value value2 = root.get(JSON_KEY_CAPAS,0);
		Json::Value value3 = root[JSON_KEY_ESCENARIO];
		Json::Value value14 = root[JSON_KEY_VENTANA];
		Json::Value value5 = root[JSON_KEY_PELEA];
		Json::Value value6 = root[JSON_KEY_JOYSTICKS];
	}catch(std::exception const & e){
		FILE_LOG(logDEBUG) << "Corrupt JSON File. Exception: "<<e.what();
		return createDefault(); //TODO: Validate create default
	}
	Window* window = jsonGetWindow(root);
	Stage* stage = jsonGetStage(root,window->width);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);

	float ratioX = getRatio(window->widthPx, window->width,"X");
	float ratioY = getRatio(window->heightPx, stage->getHeight(),"Y");

	TextureManager::Instance()->ratioHeight = ratioY;
	TextureManager::Instance()->ratioWidth = ratioX;

	vector<Layer*> layers = jsonGetLayers(root, ratioX, ratioY, window, stage);
	if (layers.size()==0){layers = buildLayersByDefault(ratioX, ratioY,window,stage);}

	vector<Character*> characters = jsonGetCharacters(root, ratioX, ratioY, stage);
	gameGUI->setCharacters(characters);
	Fight* fight = jsonGetFight(root);
	gameGUI->setFight(fight);
	//if (fight->getFighterOne()->getName() == fight->getFighterTwo()->getName()) {
		fight->getFighterTwo()->setIsAlternativePlayer(true);
	//}
	fight->getFighterOne()->setIsRightOriented(true);
	MKGame::Instance()->getObjectList().push_back(fight->getFighterOne());
	MKGame::Instance()->getObjectList().push_back(fight->getFighterTwo());
	gameGUI->setLayers(layers);

	vector<Character*> fightingCharacters;
	fightingCharacters.push_back(fight->getFighterOne());
	fightingCharacters.push_back(fight->getFighterTwo());
	gameGUI->setCharacters(fightingCharacters);
	createGameInfo(window, fightingCharacters, ratioX, ratioY);


	jsonGetJoysticks(root);

	FILE_LOG(logDEBUG) << "CONFIGURATION FINISHED";

	return gameGUI;
}

GameGUI* GameGUIBuilder::createDefault() {

	FILE_LOG(logDEBUG) << "Entire configuration set by default";
	GameGUI *gameGUI = GameGUI::getInstance();

	//window by default
	int windowXpos = ((MAX_WINDOW_WIDTH_PX-DEFAULT_WINDOW_WIDTH_PX)/2);
	int windowYpos = ((MAX_WINDOW_HEIGHT_PX-DEFAULT_WINDOW_HEIGHT_PX)/2);
	Window* ptrWindow = new Window(GAME_TITLE, windowXpos, windowYpos, DEFAULT_WINDOW_WIDTH_PX, DEFAULT_WINDOW_HEIGHT_PX, DEFAULT_WINDOW_WIDTH);
    FILE_LOG(logDEBUG) << "JSON - Window width: " << DEFAULT_WINDOW_WIDTH_PX << " px";
	FILE_LOG(logDEBUG) << "JSON - Window height: " << DEFAULT_WINDOW_HEIGHT_PX << " px";
	FILE_LOG(logDEBUG) << "JSON - Window width: " << DEFAULT_WINDOW_WIDTH;

	gameGUI->setWindow(ptrWindow);

	//stage by default
	Stage* ptrStage = new Stage(DEFAULT_STAGE_WIDTH, DEFAULT_STAGE_HEIGHT, DEFAULT_STAGE_YFLOOR);
	 FILE_LOG(logDEBUG) << "JSON - Stage width: " << DEFAULT_STAGE_WIDTH;
	 FILE_LOG(logDEBUG) << "JSON - Stage height: " << DEFAULT_STAGE_HEIGHT;
	 FILE_LOG(logDEBUG) << "JSON - Stage ypiso: " << DEFAULT_STAGE_YFLOOR;

	 gameGUI->setStage(ptrStage);

	float ratioX = getRatio(DEFAULT_WINDOW_WIDTH_PX, DEFAULT_WINDOW_WIDTH,"X");
	float ratioY = getRatio(DEFAULT_WINDOW_HEIGHT_PX, DEFAULT_STAGE_HEIGHT,"Y");

	TextureManager::Instance()->ratioHeight = ratioY;
	TextureManager::Instance()->ratioWidth = ratioX;

	//characters by default
	vector<Character*> characters;

	//TODO put in constant
	float character_width = DEFAULT_CHARACTER_WIDTH;
	float character_height = DEFAULT_CHARACTER_HEIGHT;
	int character_zindex = DEFAULT_CHARACTER_ZINDEX;
	string character_name = "default";
	float characterPosX = GameGUI::getInstance()->getWindow()->widthPx / 2 - character_width * ratioX/2;
	float stage_win_ypiso = DEFAULT_STAGE_YFLOOR;
	float characterPosY = (stage_win_ypiso - character_height) * ratioY;
	bool isRightOrientation = true;
	LoaderParams* characterParams = new LoaderParams(characterPosX, characterPosY, character_width, character_height, character_zindex,
			ratioX, ratioY, character_name);

	Character* playerOne = new Character(characterParams, isRightOrientation);
	characters.push_back(playerOne);

	//Add layers to the game loop
	MKGame::Instance()->getObjectList().push_back(playerOne);

	gameGUI->setCharacters(characters);

	gameGUI->setLayers(buildLayersByDefault(ratioX, ratioY, ptrWindow, ptrStage));

	createGameInfo(ptrWindow, characters, ratioX, ratioY);

	FILE_LOG(logDEBUG) << "Configuration process finished";
	return gameGUI;

}

vector<Layer*> GameGUIBuilder::buildLayersByDefault(float ratioX, float ratioY, Window* window, Stage* stage){

	//layers by default
	vector<Layer*> layers;
	float width, widthPiso;

	width = DEFAULT_LAYER1_WIDTH;
	widthPiso = width;
	resizeImage(&width, window->width, stage->getWidth(), widthPiso);
	Layer* layer1 = new Layer(
			new LoaderParams(0, 0, width, window->heightPx / ratioY, 0, ratioX,
					ratioY, DEFAULT_LAYER1_ID));
	layer1->setImagePath(DEFAULT_LAYER1_PATH);
	layers.push_back(layer1);

	width = DEFAULT_LAYER2_WIDTH;
	resizeImage(&width, window->width, stage->getWidth(), widthPiso);
	Layer* layer2 = new Layer(
			new LoaderParams(0, 0, width, window->heightPx / ratioY, 1, ratioX,
					ratioY, DEFAULT_LAYER2_ID));
	layer2->setImagePath(DEFAULT_LAYER2_PATH);
	layers.push_back(layer2);

	width = DEFAULT_LAYER3_WIDTH;
	resizeImage(&width, window->width, stage->getWidth(), widthPiso);
	Layer* layer3 = new Layer(
			new LoaderParams(0, 0, width, window->heightPx / ratioY, 2, ratioX,
					ratioY, DEFAULT_LAYER3_ID));
	layer3->setImagePath(DEFAULT_LAYER3_PATH);
	layers.push_back(layer3);
	//Add layers to the game loop
	MKGame::Instance()->getObjectList().push_back(layer1);
	MKGame::Instance()->getObjectList().push_back(layer2);
	MKGame::Instance()->getObjectList().push_back(layer3);

	FILE_LOG(logDEBUG) << "Layer built by default";
	FILE_LOG(logDEBUG) << "Layer ID: " << DEFAULT_LAYER1_ID;
	FILE_LOG(logDEBUG) << "Layer" << 1 << " background image: "
			<< DEFAULT_LAYER1_PATH;
	FILE_LOG(logDEBUG) << "Layer" << 1 << " width: " << DEFAULT_LAYER1_WIDTH;
	FILE_LOG(logDEBUG) << "Layer ID: " << DEFAULT_LAYER2_ID;
	FILE_LOG(logDEBUG) << "Layer" << 2 << " background image: "
			<< DEFAULT_LAYER2_PATH;
	FILE_LOG(logDEBUG) << "Layer" << 2 << " width: " << DEFAULT_LAYER2_WIDTH;
	FILE_LOG(logDEBUG) << "Layer ID: " << DEFAULT_LAYER3_ID;
	FILE_LOG(logDEBUG) << "Layer" << 3 << " background image: "
			<< DEFAULT_LAYER3_PATH;
	FILE_LOG(logDEBUG) << "Layer" << 3 << " width: " << DEFAULT_LAYER3_WIDTH;

	return layers;
}

void GameGUIBuilder::setConfigFilePath(string path){
	this->configFilePath = path;
}

void GameGUIBuilder::handleError(string msgError) {

	//TODO log msg in level ERROR
	cout << msgError << endl;

}

