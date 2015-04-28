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
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "Log.h"
using namespace std;

class TextureManager {
public:
	static TextureManager* Instance();

	void resetInstance();

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// draw
	void draw(std::string id, int x, int y, int width, int height,
			SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int height,
			int currentRow, int currentFrame, SDL_Renderer* pRenderer,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int height,
			int currentRow, int currentFrame, SDL_Renderer* pRenderer, float spriteWidth , float spriteHeight,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

	// query texure
	SDL_Rect queryTexture(std::string id) {
		SDL_Rect tRect;
		SDL_QueryTexture(m_textureMap[id], NULL, NULL, &tRect.w, &tRect.h);
		return tRect;
	}

	//Set color modulation
	void setColor(std::string id, Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode(std::string id, SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha(std::string id, Uint8 alpha );

	bool loadFromRenderedText( std::string id, std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer );

	bool unload( std::string id );

	float ratioWidth;
	float ratioHeight;
	virtual ~TextureManager() {
		map<std::string, SDL_Texture*>::iterator itr;
		for (itr = this->m_textureMap.begin(); itr != this->m_textureMap.end();
				++itr) {
			SDL_DestroyTexture(itr->second);
			itr->second = NULL;
		}
		this->m_textureMap.clear();
		delete(t_pInstance);
		t_pInstance = NULL;
	}
private:
	static TextureManager* t_pInstance;
	TextureManager();
	std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif /* TEXTUREMANAGER_H_ */
