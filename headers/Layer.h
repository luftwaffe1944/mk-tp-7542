/*
 * Layer.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef LAYER_H_
#define LAYER_H_
#include <string>
#include "SDL.h"
#include "SDLObjectGUI.h"
#include "TextureManager.h"
using namespace std;

class Layer: public SDLObjectGUI {
private:
	/*Scrolling Factor*/
	float scrollingFactor;


public:
	Layer(const LoaderParams* pParams);
	Layer(string image, int width, int zIndex);

	bool render(SDL_Renderer* render);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void setScrollingFactor(float sFactor);
	float getScrollingFactor();
	void render(SDL_Renderer* render, int height);
	virtual ~Layer();
};

#endif /* LAYER_H_ */
