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

hsv convertRGBToHSV(rgb RGB) {
    hsv HSV;
    double minRGBValue;
    double maxRGBValue;
    double deltaRGBValue;


    //Taking the min value of r, g and b
    if ((RGB.r <= RGB.g) && (RGB.r <= RGB.b)){
    	minRGBValue = RGB.r;
    } else if ((RGB.g <= RGB.r) && (RGB.g <= RGB.b)){
    	minRGBValue = RGB.g;
    } else if ((RGB.b <= RGB.r) && (RGB.b <= RGB.g)){
    	minRGBValue = RGB.b;
    }

    //Taking the max value of r, g and b
    if ((RGB.r >= RGB.g) && (RGB.r >= RGB.b)) {
    	maxRGBValue = RGB.r;
    } else if ((RGB.g >= RGB.r) && (RGB.g >= RGB.b)) {
    	maxRGBValue = RGB.g;
    } else if ((RGB.b >= RGB.r) && (RGB.b >= RGB.g)) {
    	maxRGBValue = RGB.b;
}

    HSV.v = maxRGBValue;
    deltaRGBValue = maxRGBValue - minRGBValue;
    if( maxRGBValue > 0.0 ) {
        HSV.s = (deltaRGBValue / maxRGBValue);
    } else {
        HSV.s = 0.0;
        HSV.h = NAN;
        return HSV;
    }
    if( RGB.r >= maxRGBValue ) {
        HSV.h = ( RGB.g - RGB.b ) / deltaRGBValue;
    } else {
    	if( RGB.g >= maxRGBValue ){
    		HSV.h = 2.0 + ( RGB.b - RGB.r ) / deltaRGBValue;
    	} else {
    		HSV.h = 4.0 + ( RGB.r - RGB.g ) / deltaRGBValue;
    	}
    }
    HSV.h *= 60.0;

    if( HSV.h < 0.0 ) {
        HSV.h += 360.0;
    }

    return HSV;
}


rgb convertHSVToRGB(hsv HSV)
{
    double hueValue;
    double p;
    double q;
    double t;
    double ff;
    long i;
    rgb RGB;

    if(HSV.s <= 0.0) {
        RGB.r = HSV.v;
        RGB.g = HSV.v;
        RGB.b = HSV.v;
        return RGB;
    }
    hueValue = HSV.h;

    if(hueValue >= 360.0) {
    	hueValue = (int)hueValue % (int)360.0;
    }
    if(hueValue < 0.0) {
    	hueValue = (int)hueValue % (int)360.0;
    	hueValue = 360.0 + hueValue;
    }

    hueValue /= 60.0;
    i = (long)hueValue;
    ff = hueValue - i;
    p = HSV.v * (1.0 - HSV.s);
    q = HSV.v * (1.0 - (HSV.s * ff));
    t = HSV.v * (1.0 - (HSV.s * (1.0 - ff)));

    if (i == 0) {
        RGB.r = HSV.v;
        RGB.g = t;
        RGB.b = p;
    } else if (i == 1) {
        RGB.r = q;
        RGB.g = HSV.v;
        RGB.b = p;
    } else if (i == 2) {
        RGB.r = p;
        RGB.g = HSV.v;
        RGB.b = t;
    } else if (i == 3) {
        RGB.r = p;
        RGB.g = q;
        RGB.b = HSV.v;
    } else if (i == 4) {
        RGB.r = t;
        RGB.g = p;
        RGB.b = HSV.v;
    } else {
        RGB.r = HSV.v;
        RGB.g = p;
        RGB.b = q;
    }

    return RGB;
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
            if (a != 0) {
				newHsv = convertRGBToHSV(rgb);
				if ((altColor->getInitialH() <= newHsv.h) && (newHsv.h <= altColor->getFinalH())) {
					newHsv.h += altColor->getShift();
				}
				rgb = convertHSVToRGB(newHsv);
				putpixel(pTempSurface, i, j, SDL_MapRGB(pTempSurface->format, rgb.r, rgb.g, rgb.b));
            }
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
	std::map<std::string, SDL_Texture*>::iterator it;
	it = m_textureMap.find(id);
	if (it != m_textureMap.end()) {
		cout << "No encuentro el id " << id << endl;
	}
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
		cout << id + textureText << endl;
		m_textureMap[id + textureText] = mTexture;
		return true;
	}
	else {
		cout << "error";
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
