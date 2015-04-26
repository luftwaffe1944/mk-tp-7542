/*
 * TextureManager.cpp
 *
 *  Created on: 31/3/2015
 *      Author: julian
 */

#include "../headers/TextureManager.h"

TextureManager* TextureManager::t_pInstance = NULL;
TextureManager* TextureManager::Instance() {
	if (!t_pInstance) {
		t_pInstance = new TextureManager();
		return t_pInstance;
	} else {
		return t_pInstance;
	}
}

TextureManager::TextureManager() {
	this->ratioHeight = 0;
	this->ratioWidth = 0;

}

void TextureManager::resetInstance() {
	map<std::string, SDL_Texture*>::iterator itr;

	for (itr = this->m_textureMap.begin(); itr != this->m_textureMap.end();
			++itr) {
		SDL_DestroyTexture(itr->second);
		itr->second = NULL;
	}
	this->m_textureMap.clear();
}

bool TextureManager::load(std::string fileName, std::string id,
		SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) {
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,
			pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = this->queryTexture(id).w;
	srcRect.h = this->queryTexture(id).h;

	destRect.w = width * this->ratioWidth;
	destRect.h = height * this->ratioHeight;
	destRect.x = x * this->ratioWidth;
	destRect.y = y * this->ratioHeight;

	//flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,
			flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width,
		int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer,
		SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = 100;
	destRect.w = width;
	srcRect.h = 135;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,
			flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width,
		int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, float spriteWidth, float spriteHeight,
		SDL_RendererFlip flip) {

	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = spriteWidth * currentFrame;
	srcRect.y = spriteHeight * (currentRow - 1);
	srcRect.w = spriteWidth;
	destRect.w = width;
	srcRect.h = spriteHeight;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,
			flip);

}

void TextureManager::setColor(std::string id, Uint8 red, Uint8 green,
		Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(m_textureMap[id], red, green, blue);
}

void TextureManager::setBlendMode(std::string id, SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(m_textureMap[id], blending);
}

void TextureManager::setAlpha(std::string id, Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
}

bool TextureManager::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer )
{
    SDL_Texture* mTexture = NULL;
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        SDL_FreeSurface( textSurface );
    }

	if (mTexture != 0) {
		m_textureMap["name"+textureText] = mTexture;
		return true;
	}

	return false;
}

