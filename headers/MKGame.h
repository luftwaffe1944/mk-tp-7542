/*
 * MKGame.h
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef MKGAME_H_
#define MKGAME_H_
#include "SDL.h"
#include "SDLObjectGUI.h"
#include "ObjectGUI.h"
#include "Character.h"
#include "GameGUI.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;

class MKGame {

private:
	MKGame();
	// create the s_pInstance member variable
	static MKGame* s_pInstance;
//	SDLObjectGUI* playerOne;
	vector<SDLObjectGUI*> objectList;
	GameGUI* gameGui;
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture; // the new SDL_Texture variable
	SDL_Rect m_sourceRectangle; // the first rectangle
	SDL_Rect m_destinationRectangle; // another rectangle

public:
	// create the public instance function
	static MKGame* Instance();
	// make the constructor private
	~MKGame() {
	}
	// simply set the running variable to true
	bool init(GameGUI* gameGui);
	bool init(const char* title, int xpos, int ypos, int width, int height,
			int flags);

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	vector<SDLObjectGUI*> getObjectList();
	void draw();
	void render();
	void update();
	void handleEvents();
	void clean();
	// a function to access the private running variable
	bool running() {
		return m_bRunning;
	}
};

#endif /* MKGAME_H_ */
