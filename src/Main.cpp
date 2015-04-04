#include "../headers/MKGame.h"
#include "../headers/Constants.h"
#include "../headers/Log.h"
#include "../headers/GameGUIBuilder.h"
#include "../headers/GameGUI.h"

// our Game object
MKGame* mkGame = 0;

int main(int argc, char* argv[]) {

	//TODO tomar por parametro el nivel de log hardcodeado
	FILELog::reportingLevel() = FILELog::fromString("DEBUG");

	GameGUIBuilder gameGUIBuilder;
	GameGUI* gameGUI = gameGUIBuilder.create();

	if (MKGame::Instance()->init(gameGUI)) {
		std::cout << "game init success" << endl;
		while (MKGame::Instance()->running()) {
			MKGame::Instance()->handleEvents();
			MKGame::Instance()->update();
			MKGame::Instance()->render();
			SDL_Delay(10);
		}
	} else {
		std::cout << "game init failure - " << SDL_GetError() << endl;
		return -1;
	}
	std::cout << "game closing..." << endl;
	MKGame::Instance()->clean();
	return 0;

}
