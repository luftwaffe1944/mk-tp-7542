/*
 * MKGame.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/MKGame.h"
#include "../headers/Log.h"
#include <algorithm>

using namespace std;


MKGame::MKGame() {
}

MKGame* MKGame::Instance() {
	static MKGame s_pInstance;
	return &s_pInstance;
}

bool MKGame::init(GameGUI* gameGui) {
	this->setOffReset();
	this->gameGui = gameGui;
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		FILE_LOG(logDEBUG) << "SDL init success";
		// init the window
		Window* gameWindow = this->gameGui->getWindow();
		m_pWindow = SDL_CreateWindow(gameWindow->title, gameWindow->xpos,
				gameWindow->ypos, gameWindow->widthPx, gameWindow->heightPx, 0);
		if (m_pWindow != 0) {
			FILE_LOG(logDEBUG) << "window creation success";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
			if (m_pRenderer != 0) {
				FILE_LOG(logDEBUG) << "renderer creation success";

				/* TODO calcular el alto y el ancho, estos valores vienen en el json
				 * en teoria no se deberia calcular con el query
				 * SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
				 */

				vector<SDLObjectGUI*> objects = getObjectList();
				for (int i = 0; i < objects.size(); i++) {
					objects[i]->load(m_pRenderer);
				}

				/*for (int i = 0; i < objects.size(); i++) {
					objects[i]->draw();
				}*/



			} else {
				FILE_LOG(logERROR) << "renderer init fail";
				return false; // renderer init fail
			}
		} else {
			FILE_LOG(logERROR) << "window init fail";
			return false; // window init fail
		}
	} else {
		FILE_LOG(logERROR) << "SDL init fail";
		return false; // SDL init fail
	}
	FILE_LOG(logDEBUG) << "init success";
	m_bRunning = true; // everything inited successfully,
	return true;
}



bool compareSDLObjectGUI(SDLObjectGUI* a, SDLObjectGUI* b) {
	return (a->getZIndex() < b->getZIndex());
}

void MKGame::render() {
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	vector<SDLObjectGUI*> objects = this->getObjectList();
	std::stable_sort (objects.begin(), objects.end(), compareSDLObjectGUI);

	for (std::vector<SDLObjectGUI*>::iterator it=objects.begin(); it!=objects.end(); ++it) {
		(*it)->draw();
	}

	//TextureManager::Instance()->draw("scorpion", 0, 0, m_destinationRectangle.w, m_destinationRectangle.h, m_pRenderer, SDL_FLIP_NONE);
	SDL_RenderPresent(m_pRenderer); // draw to the screen

}

template <typename T>
void delete_pointer_to(T* const ptr)  {
	delete ptr;
}



void MKGame::clean() {
	FILE_LOG(logDEBUG) << "cleaning game\n";
	TextureManager::Instance()->resetInstance();
	GameGUI::getInstance()->clean();
	std::for_each(objectList.begin(),objectList.end(),delete_pointer_to<SDLObjectGUI>);
	objectList.clear();

	LayerManager::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
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
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			MKGame::Instance()->quit();
		}
	}
	InputControl::Instance()->refreshInputs();
	InputCommand option = InputControl::Instance()->getControlOption();
	if (option==RESET){
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
