/*
 * TextureManager.h
 *
 *  Created on: 31/3/2015
 *      Author: julian
 */

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <iostream>
#include <map>
#include <SDL.h>
using namespace std;

class TextureManager {
public:
	static TextureManager* Instance() {
		if (t_pInstance == 0) {
			t_pInstance = new TextureManager();
			return t_pInstance;
		}
		return t_pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// draw
	void draw(std::string id, int x, int y, int width, int height,
			SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int height,
			int currentRow, int currentFrame, SDL_Renderer* pRenderer,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	static TextureManager* t_pInstance;
	TextureManager();
	virtual ~TextureManager();
	std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif /* TEXTUREMANAGER_H_ */
