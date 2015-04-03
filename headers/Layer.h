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
#include "TextureManager.h"
using namespace std;

class Layer {
private:
	string backgroundImage;
	int width;
	int zIndex;
	/*Scrolling Factor*/
	float scrollingFactor;


public:
	Layer();
	Layer(string image, int width, int zIndex);
	bool load(SDL_Renderer* render);
	void render(SDL_Renderer* render, int height);
	void setScrollingFactor(float sFactor);
	float getScrollingFactor();
	virtual ~Layer();
};

#endif /* LAYER_H_ */
