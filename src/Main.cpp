#include "../headers/MKGame.h"
#include "../headers/Constants.h"
#include "../src/Log.h"

// our Game object
MKGame* mkGame = 0;

int main(int argc, char* argv[]){
	mkGame = new MKGame();
	mkGame->init(GAME_TITLE, 100, 100, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 0);
	while(mkGame->running()) {
		mkGame->handleEvents();
		mkGame->update();
		mkGame->render();
	}
	mkGame->clean();
	return 0;
}
