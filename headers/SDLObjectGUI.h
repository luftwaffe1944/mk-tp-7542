/*
 * SDLObjectGUI.h
 *
 *  Created on: 2/4/2015
 *      Author: mauro
 */

#ifndef SDLOBJECTGUI_H_
#define SDLOBJECTGUI_H_
#include "InputControl.h"
#include "TextureManager.h"
#include "ObjectGUI.h"
#include <sstream>
#include <string>
#include "LoaderParams.h"

class SDLObjectGUI : public ObjectGUI {
public:
	SDLObjectGUI();
	SDLObjectGUI(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	int unitToPixel(float units);
	virtual bool load();
	virtual bool load(SDL_Renderer* render);
	void setImagePath(string imagePath);
protected:
	string imagePath;
	float positionX;
	float positionY;
	int width;
	int height;
	int zIndex;
	float drawRatio;
	int currentRow;
	int currentFrame;
	std::string textureID;
};
#endif /* SDLOBJECTGUI_H_ */
