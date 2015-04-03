/*
 * MKGame.h
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef MKGAME_H_
#define MKGAME_H_
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>
#include "../headers/GameGUI.h"
using namespace std;

class MKGame {

	private:
		bool m_bRunning;
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
		SDL_Texture* m_pTexture; // the new SDL_Texture variable
		SDL_Rect m_sourceRectangle; // the first rectangle
		SDL_Rect m_destinationRectangle; // another rectangle
		GameGUI* gameGui;

	public:
		MKGame() {}
		~MKGame() {}
		// simply set the running variable to true
		void init() { m_bRunning = true; }
		bool init(GameGUI* gameGui);
		bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
		void render();
		void update(){}
		void handleEvents();
		void clean();
		// a function to access the private running variable
		bool running() {
			return m_bRunning;
		}
	};

#endif /* MKGAME_H_ */
