/*
 * MKGame.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/MKGame.h"
#include "../headers/Log.h"
#include "../headers/TextureManager.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;


bool MKGame::init(GameGUI* gameGui) {

	this->gameGui = gameGui;
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		FILE_LOG(logDEBUG) << "SDL init success";
		// init the window
		Window gameWindow = this->gameGui->getWindow();
		m_pWindow = SDL_CreateWindow(gameWindow.title, gameWindow.xpos, gameWindow.ypos, gameWindow.widthPx, gameWindow.heightPx, 0);
		if(m_pWindow != 0) {
			FILE_LOG(logDEBUG) << "window creation success";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer != 0) {
				FILE_LOG(logDEBUG) << "renderer creation success";
				//SDL_SetRenderDrawColor(m_pRenderer, 255,255,255,255);


				vector<Layer> vLayers = this->gameGui->getLayers();
			    for(int i = 0; i < vLayers.size(); i++)
			    {
					if (!vLayers[i].load(m_pRenderer)){
						FILE_LOG(logDEBUG) << "Error al cargar capa n:" << i++;
					}
			    }

				std::string path_img_sc = "images/scorpion_fighting_stance/sfsGIF.gif";
				if (!TextureManager::Instance()->load(path_img_sc, "scorpion", m_pRenderer)) {
					cout << "error con el load";
				}

				/* TODO calcular el alto y el ancho, estos valores vienen en el json
				 * en teoria no se deberia calcular con el query
				 * SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
				 */

				m_sourceRectangle.w = TextureManager::Instance()->queryTexture("scorpion").w;
				m_sourceRectangle.h = TextureManager::Instance()->queryTexture("scorpion").h;


				m_destinationRectangle.x = m_sourceRectangle.x = 0;
				m_destinationRectangle.y = m_sourceRectangle.y = 0;
				m_destinationRectangle.w = m_sourceRectangle.w;
				m_destinationRectangle.h = m_sourceRectangle.h;

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

	vector<Layer> vLayers = this->gameGui->getLayers();
    for(int i = 0; i < vLayers.size(); i++)
    {
		vLayers[i].render(m_pRenderer,500);

    }
	TextureManager::Instance()->draw("scorpion", 0, 0, m_destinationRectangle.w, m_destinationRectangle.h, m_pRenderer, SDL_FLIP_NONE);
	SDL_RenderPresent(m_pRenderer); // draw to the screen

}

void MKGame::clean() {
	FILE_LOG(logDEBUG) << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void MKGame::handleEvents() {
	SDL_Event event;
	if(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_bRunning = false;
				break;
			default:
				break;
		}
	}
}
