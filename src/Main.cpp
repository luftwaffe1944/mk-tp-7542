#include "../headers/MKGame.h"
#include "../headers/Constants.h"
#include "../headers/Log.h"
#include "../headers/GameGUIBuilder.h"
#include "../headers/GameGUI.h"
#include "../headers/Timer.h"


// our Game object
MKGame* mkGame = 0;

int main(int argc, char* argv[]) {

	string configFilePath = "";


	if (argc > 2){
		//PARAMETROS (jsonPath , reportinLevel)
		FILELog::reportingLevel() = FILELog::fromString(argv[2]);
		configFilePath = argv[1];
	}else if (argc > 1){
		//PARAMETROS (jsonPath)
		configFilePath = argv[1];
		FILELog::reportingLevel() = FILELog::fromString("DEBUG");
	}

	bool runApp = true;
	do{
		GameGUIBuilder gameGUIBuilder(configFilePath);
		GameGUI* gameGUI = gameGUIBuilder.create();
		LayerManager::Instance()->init();

		if (MKGame::Instance()->init(gameGUI)) {
			std::cout << "game init success" << endl;
			while ((MKGame::Instance()->running()) && !(MKGame::Instance()->reset()))  {
				MKGame::Instance()->handleEvents();
				MKGame::Instance()->update();
				MKGame::Instance()->render();
				SDL_Delay(5);
			}
			if (!(MKGame::Instance()->running())){
				runApp = false;
			}
		} else {
			std::cout << "game init failure - " << SDL_GetError() << endl;
			return -1;
		}
		std::cout << "game closing..." << endl;
		MKGame::Instance()->clean();
	}while(runApp);

	return 0;

}
