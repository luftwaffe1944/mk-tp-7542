/*
 * MKGame.0h
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef MKGAME_H_
#define MKGAME_H_
#include "InputControl.h"
#include "SDL.h"
#include "SDLObjectGUI.h"
#include "ObjectGUI.h"
#include "Character.h"
#include "GameGUI.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "LayerManager.h"
#include <algorithm>
#include "Log.h"
#include "SDL_ttf.h"
#include "CollitionManager.h"
#include "Menu.h"
#include "GameInfo.h"

//#include "SDL_gamecontroller.h"
//#include "SDL_joystick.h"

using namespace std;

template <typename T>
void delete_pointer_to(T* const ptr)  {
	delete ptr;
}

class MKGame {

private:
	static MKGame* mk_pInstance;
	bool m_bRunning;
	bool m_bReset;
	bool allowPlayerMovements;
	vector<SDLObjectGUI*> objectList;
	GameGUI* gameGui;
	InputControl keyboardControl;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	//SDL_Joystick* gGameController;

	bool shouldBeShaking;
	int shakeLength;
	int shakeIntensity;

	float offSetPosY;

	Menu* menuMk;
	Menu* menuNewGame;
	Menu* menuCharacterSelect;

	MKGame() {
		m_bRunning = false;
		m_bReset = false;
		m_pWindow = NULL;
		m_pRenderer = NULL;
		gameGui = NULL;
		shouldBeShaking = false;
		allowPlayerMovements = false;
		shakeIntensity = 5;
		shakeLength = 10;
		offSetPosY = 0;
		//gGameController = NULL;
	}

public:
	static MKGame* Instance();
	~MKGame() {
		std::for_each(objectList.begin(),objectList.end(),delete_pointer_to<SDLObjectGUI>);
		objectList.clear();

		LayerManager::Instance()->clean();

		TextureManager::Instance()->resetInstance();
		SDL_DestroyRenderer(this->m_pRenderer);
		SDL_DestroyWindow(this->m_pWindow);
		//SDL_JoystickClose( this->gGameController );

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		if (mk_pInstance != NULL) delete mk_pInstance;
		mk_pInstance = NULL;
	}
	bool init(GameGUI* gameGui);
	bool init(const char* title, int xpos, int ypos, int width, int height,
			int flags);

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	vector<SDLObjectGUI*>& getObjectList();
	void configureFight(std::string fighterOneName, std::string fighterTwoName);
	void draw();
	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();
	void setShaking(bool shaking);
	GameGUI* getGameGUI();

	bool running() {
		return m_bRunning;
	}
	bool reset() {
			return m_bReset;
	}
	void setOnReset(){m_bReset=true;}
	void setOffReset(){m_bReset=false;}
	void setAllowPlayerMovements(bool allowPlayerMovements){
		this->allowPlayerMovements = allowPlayerMovements;
	}

	bool getAllowPlayerMovements(){
		return this->allowPlayerMovements;
	}

	void menuInit();
	void drawMenu(Menu* menu, int opacity);
	void menuActions(std::string action);
	bool menu();

	bool menuPpal;
	bool menuGame;
	bool menuCharacter;
};

#endif /* MKGAME_H_ */
