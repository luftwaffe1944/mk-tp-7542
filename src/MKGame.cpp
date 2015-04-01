/*
 * MKGame.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/MKGame.h"
#include "../headers/Log.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;


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
				//SDL_SetRenderDrawColor(m_pRenderer, 255,255,255,255);
				SDL_Surface* pTempSurface = IMG_Load("images/scorpion_fighting_stance/sfsGIF.gif");
				m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
				SDL_FreeSurface(pTempSurface);
				SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

				/*m_sourceRectangle.w = 50;
				m_sourceRectangle.h = 50;*/

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
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle,
	&m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer); // draw to the screen

}

void MKGame::clean() {
	std::cout << "cleaning game\n";
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
