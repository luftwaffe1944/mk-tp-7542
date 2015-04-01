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
		static TextureManager t_pInstance;
		return &t_pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// draw
	void draw(std::string id, int x, int y, int width, int height,
			SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int height,
			int currentRow, int currentFrame, SDL_Renderer* pRenderer,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Rect queryTexture(std::string id) {
		SDL_Rect tRect;
		SDL_QueryTexture(m_textureMap[id], NULL, NULL, &tRect.w, &tRect.h);
		return tRect;
	}

private:
	TextureManager();
	std::map<std::string, SDL_Texture*> m_textureMap;
	virtual ~TextureManager();
};

#endif /* TEXTUREMANAGER_H_ */
