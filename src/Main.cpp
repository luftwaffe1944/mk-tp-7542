#include "../headers/MKGame.h"
#include "../headers/Constants.h"
#include "../headers/Log.h"
#include "../headers/GameGUIBuilder.h"
#include "../headers/GameGUI.h"

// our Game object
MKGame* mkGame = 0;

int main(int argc, char* argv[]){

	//TODO tomar por parametro el nivel de log hardcodeado
	FILELog::reportingLevel() = FILELog::fromString("DEBUG");

	GameGUIBuilder gameGUIBuilder;
	GameGUI* gameGUI = gameGUIBuilder.create();

	mkGame = new MKGame();
	mkGame->init(gameGUI);
	while(mkGame->running()) {
		mkGame->handleEvents();
		mkGame->update();
		mkGame->render();
	}
	mkGame->clean();

	return 0;
}
