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
	int offScene;
	float scrollingOffset;
	float bkgSpeed;


public:
	Layer(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual ~Layer();
};

#endif /* LAYER_H_ */
