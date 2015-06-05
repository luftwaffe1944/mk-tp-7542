/*
 * MenuItem.h
 *
 *  Created on: 26/5/2015
 *      Author: julian
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_
#include "SDLObjectGUI.h"
#include "LoaderParams.h"
#include <iostream>
#include <vector>
#include "SDL_ttf.h"
#include "string"
#include <algorithm>
#include "TextureManager.h"

class MenuItem {
private:

	SDL_Color color;

public:
	int positionX, positionY;
	int width, height;
	MenuItem* next;
	MenuItem* previous;
	std::string text;

	MenuItem(int, int, int, int, std::string);
	virtual ~MenuItem();
	bool checkBounds(float posX, float posY);
	void setColor(int r, int g, int b);
	void show(SDL_Renderer*);
	void drawBox(SDL_Renderer*);
};

#endif /* MENUITEM_H_ */
