#include "../headers/MKGame.h"
#include "../headers/Constants.h"
#include "../headers/Log.h"
#include "../headers/GameGUIBuilder.h"
#include "../headers/GameGUI.h"

// our Game object
MKGame* mkGame = 0;

int main(int argc, char* argv[]){

	mkGame = new MKGame();
	mkGame->init(GAME_TITLE, 100, 100, DEFAULT_WINDOW_WIDTH_PX, DEFAULT_WINDOW_HEIGHT_PX, 0);
	while(mkGame->running()) {
		mkGame->handleEvents();
		mkGame->update();
		mkGame->render();
	}
	mkGame->clean();

//	GameGUIBuilder gameGUIBuilder;
//	GameGUI *gameGUI = gameGUIBuilder.create();



	return 0;
}
