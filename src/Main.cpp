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

	if (MKGame::Instance()->init(GAME_TITLE, 100, 100, 640, 480, false)) {
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

	return 0;
}
