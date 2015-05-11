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

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
            // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
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

void changeToAltColor(SDL_Surface* pTempSurface, AlternativeColor* altColor) {
	Uint8 a;
	rgb rgb;
	hsv newHsv;
	for (int i = 0; i < pTempSurface->w; i++) {
		for (int j=0; j < pTempSurface->h; j++) {
			SDL_GetRGBA(getpixel(pTempSurface, i, j), pTempSurface->format, &rgb.r, &rgb.g, &rgb.b, &a);
            if (a == 0) {
                continue;
            }
			newHsv = rgb2hsv(rgb);
			if ((altColor->getInitialH() <= newHsv.h) && (newHsv.h <= altColor->getFinalH())) {
				newHsv.h += altColor->getShift();
			}
			rgb = hsv2rgb(newHsv);
			putpixel(pTempSurface, i, j, SDL_MapRGB(pTempSurface->format, rgb.r, rgb.g, rgb.b));
		}
	}
}

bool TextureManager::load(std::string fileName, std::string id,
		SDL_Renderer* pRenderer, bool isAltPlayer, AlternativeColor* altColor) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) {
		return false;
	}
	if (isAltPlayer) {
		SDL_LockSurface(pTempSurface);
		changeToAltColor(pTempSurface, altColor);
		SDL_UnlockSurface(pTempSurface);
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

bool TextureManager::loadFromRenderedText( std::string id, std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer )
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
		m_textureMap[id + textureText] = mTexture;
		return true;
	}

	return false;
}

bool TextureManager::unload( std::string id )
{
	SDL_Texture* mTexture = m_textureMap[id];

	if (mTexture != 0) {
		SDL_DestroyTexture(m_textureMap[id]);
		this->m_textureMap.erase(id);
		return true;
	}
	return false;
}
