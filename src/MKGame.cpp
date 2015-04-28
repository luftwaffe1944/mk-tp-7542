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
	}

	SDL_RenderPresent(m_pRenderer);
}


void MKGame::clean() {
	FILE_LOG(logDEBUG) << "cleaning game\n";
	GameGUI::getInstance()->clean();

	std::for_each(objectList.begin(),objectList.end(),delete_pointer_to<SDLObjectGUI>);
	objectList.clear();

	LayerManager::Instance()->clean();

	TextureManager::Instance()->resetInstance();
	SDL_DestroyRenderer(this->m_pRenderer);
	SDL_DestroyWindow(this->m_pWindow);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	this->m_bReset = false;
}

void MKGame::draw() {
	for (std::vector<ObjectGUI*>::size_type i = 0; i != objectList.size();
			i++) {
		objectList[i]->draw();
	}
}

void MKGame::update() {
	for (std::vector<ObjectGUI*>::size_type i = 0; i != objectList.size();
			i++) {
		objectList[i]->update();
		LayerManager::Instance()->refresh();
	}
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
	}
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
