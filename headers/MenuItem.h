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

class MenuItem : public SDLObjectGUI {
private:
	MenuItem* next; /* Lista de Items*/

public:
	MenuItem(const LoaderParams* params);
	virtual ~MenuItem();
	bool checkBounds(float posX, float posY);

	virtual bool load(SDL_Renderer* render);
	virtual void draw();
	virtual void update();
	virtual void clean();
};

#endif /* MENUITEM_H_ */
