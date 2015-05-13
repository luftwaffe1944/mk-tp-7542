/*
 * MKGame.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/MKGame.h"

using namespace std;


MKGame* MKGame::mk_pInstance = NULL;

MKGame* MKGame::Instance() {
	if (!mk_pInstance) {
		mk_pInstance = new MKGame();
		return mk_pInstance;
	} else {
		return mk_pInstance;
	}
}

bool MKGame::init(GameGUI* gameGui) {
	this->setOffReset();
	this->gameGui = gameGui;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		FILE_LOG(logDEBUG) << "SDL init success";


		InputControl::Instance()->initJoysticks();


		Window* gameWindow = this->gameGui->getWindow();
		m_pWindow = SDL_CreateWindow(gameWindow->title, gameWindow->xpos,
				gameWindow->ypos, gameWindow->widthPx, gameWindow->heightPx, 0);
		if (m_pWindow != 0) {
			FILE_LOG(logDEBUG) << "window creation success";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if (m_pRenderer != 0) {
				FILE_LOG(logDEBUG) << "renderer creation success";

				vector<SDLObjectGUI*> objects = getObjectList();
				for (unsigned int i = 0; i < objects.size(); i++) {
					objects[i]->load(m_pRenderer);
				}
			} else {
				FILE_LOG(logERROR) << "renderer init fail";
				return false;
			}
		} else {
			FILE_LOG(logERROR) << "window init fail";
			return false;
		}
	} else {
		FILE_LOG(logERROR) << "SDL init fail";
		return false;
	}

    if( TTF_Init() == -1 ) {
    	FILE_LOG(logERROR) << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
    }

	FILE_LOG(logDEBUG) << "init success";
	m_bRunning = true;
	return true;
}



bool compareSDLObjectGUI(SDLObjectGUI* a, SDLObjectGUI* b) {
	return (a->getZIndex() < b->getZIndex());
}

void MKGame::render() {
	SDL_RenderClear(m_pRenderer);
	vector<SDLObjectGUI*> objects = this->getObjectList();
	std::stable_sort (objects.begin(), objects.end(), compareSDLObjectGUI);

	for (std::vector<SDLObjectGUI*>::iterator it=objects.begin(); it!=objects.end(); ++it) {
		(*it)->draw();
		(*it)->setPositionY((*it)->getPositionY() - this->offSetPosY);
	}


	SDL_RenderPresent(m_pRenderer);
}


void MKGame::clean() {
	FILE_LOG(logDEBUG) << "cleaning game\n";
	GameGUI::getInstance()->clean();

	std::for_each(objectList.begin(),objectList.end(),delete_pointer_to<SDLObjectGUI>);
	objectList.clear();

	LayerManager::Instance()->clean();
	InputControl::Instance()->clean();

	TextureManager::Instance()->resetInstance();
	SDL_DestroyRenderer(this->m_pRenderer);
	SDL_DestroyWindow(this->m_pWindow);

	//SDL_JoystickClose( this->gGameController );
	//gGameController = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	this->m_bReset = false;
	this->shouldBeShaking = true;
	this->offSetPosY = 0;
}

void MKGame::draw() {
	for (std::vector<SDLObjectGUI*>::size_type i = 0; i != objectList.size();
			i++) {
		objectList[i]->draw();
	}
}

vector<Collitionable*> convertVector(vector<Character*> oldVec){
	vector<Collitionable*> newVec;
	for (std::vector<Character*>::size_type i = 0; i != oldVec.size(); i++) {
		newVec.push_back((Collitionable*) oldVec[i]);
		}
	return newVec;
}

void MKGame::update() {
	if (shouldBeShaking) {
		this->offSetPosY = (rand() % shakeIntensity) - 0.5f;
		shakeLength--;
		if (shakeLength <= 0) {
			shouldBeShaking = false;
			shakeLength = 10;
			shakeIntensity = 5;
			this->offSetPosY = 0;
		}
	}
	for (std::vector<SDLObjectGUI*>::size_type i = 0; i != objectList.size();
			i++) {
		objectList[i]->update();
		LayerManager::Instance()->refresh();
		objectList[i]->setPositionY(objectList[i]->getPositionY() + this->offSetPosY);
	}

	GameGUI* pgamegui = this->getGameGUI();
	vector<Collitionable*> collObjects = convertVector(this->getGameGUI()->getCharacters());
	CollitionManager::Instance()->solveCollitions(collObjects);

}



void MKGame::handleEvents() {
	SDL_Event event;
	bool reset = false;
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			MKGame::Instance()->quit();
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r && event.key.repeat == 0) {
			reset = true;
		}
		if (event.type == SDL_JOYBUTTONDOWN ) {
			//std::cout << "asd";
			InputControl::Instance()->joysticksButtonStates[event.jaxis.which][event.jbutton.button] = true;
		}
		if (event.type == SDL_JOYBUTTONUP ) {
			InputControl::Instance()->joysticksButtonStates[event.jaxis.which][event.jbutton.button] = false;
		}
		if (event.type == SDL_JOYAXISMOTION ){

			int num_joy = event.jaxis.which;

			//derecha e izquierda
			if (event.jaxis.axis == 0) {

				if (event.jaxis.value > MAX_XAXIS || event.jaxis.value < MIN_XAXIS) {
					InputControl::Instance()->joystickAxisStates[num_joy].first = event.jaxis.value;
				} else {
					InputControl::Instance()->joystickAxisStates[num_joy].first = 0;
				}

			}

			//arriba y abajo
			if (event.jaxis.axis == 1) {

				if (event.jaxis.value > MAX_YAXIS || event.jaxis.value < MIN_YAXIS){
					InputControl::Instance()->joystickAxisStates[num_joy].second = event.jaxis.value;
				} else {
					InputControl::Instance()->joystickAxisStates[num_joy].second = 0;
				}

			}

		}
	}
	//InputControl::Instance()->refreshInputs();

	if (InputControl::Instance()->joysticks.size() > 0 && SDL_NumJoysticks() > 0)
		InputControl::Instance()->refreshJoystickInputs();
	//InputControl::Instance()->update();
	InputControl::Instance()->refreshInputs();
	if (reset == true){
		MKGame::Instance()->setOnReset();
	}
}

void MKGame::quit(){
	this->m_bRunning = false;
}

vector<SDLObjectGUI*>& MKGame::getObjectList() {
	return objectList;
}

GameGUI* MKGame::getGameGUI(){
	return gameGui;
}

void MKGame::setShaking(bool shaking) {
	this->shouldBeShaking = shaking;
}
