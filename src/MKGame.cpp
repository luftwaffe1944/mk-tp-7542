/*
 * MKGame.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/MKGame.h"
#include "../headers/Log.h"
#include "../headers/TextureManager.h"
#include "../headers/InputControl.h"
#include "../headers/Constants.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

bool firstTimeRender=true;
int frame = 0;


bool MKGame::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		FILE_LOG(logDEBUG) << "SDL init success";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(m_pWindow != 0) {
			FILE_LOG(logDEBUG) << "window creation success";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer != 0) {
				FILE_LOG(logDEBUG) << "renderer creation success";
				SDL_SetRenderDrawColor(m_pRenderer, 255,0,0,255);

				Character subzero = Character(0, height - 132, 66, 132, 1);
				this->pCharacter = subzero;
				this->pCharacter.load(m_pRenderer);


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

void MKGame::render() {
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
	int row = 1;
	if (pCharacter.getMovement() == JUMPING_MOVEMENT){
		row = 3;
	}
	pCharacter.draw();
	//TextureManager::Instance()->drawFrame(pCharacter.getActiveSprite(), pCharacter.x(), pCharacter.y(), pCharacter.w(), pCharacter.h(),row,pCharacter.getNextFrame(), m_pRenderer,SDL_FLIP_NONE);

	SDL_RenderPresent(m_pRenderer); // draw to the screen

}

void MKGame::update(){
	InputControl keyboardControl = InputControl();
	keyboardControl.refreshInputs();

	InputCommand playerCommand = keyboardControl.getFirstPlayerMove();
	//InputCommand optionCommand = keyboardControl.getControlOption();
		switch(playerCommand){
		case FIRST_PLAYER_MOVE_RIGHT:
			this->pCharacter.setMovement(WALKING_RIGHT_MOVEMENT);
			//this->pCharacter.setActiveSprite("subzerowalk");
			break;
		case FIRST_PLAYER_MOVE_LEFT:
			this->pCharacter.setMovement(WALKING_LEFT_MOVEMENT);
			//this->pCharacter.setActiveSprite("subzerowalk");
			break;
		case FIRST_PLAYER_MOVE_UP:
			this->pCharacter.setMovement(JUMPING_MOVEMENT);
			//this->pCharacter.setActiveSprite("subzerojump");
			break;
		case NO_INPUT:
			//this->pCharacter.setMovement(STANCE);
			//this->pCharacter.setActiveSprite("subzerostand");
			break;
		}
		this->pCharacter.update();
		SDL_Delay( 75 );
}


void MKGame::clean() {
	FILE_LOG(logDEBUG) << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void MKGame::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_bRunning = false;
				break;
			default:
				break;
		}
	}
}
