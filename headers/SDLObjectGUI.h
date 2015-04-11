/*
 * SDLObjectGUI.h
 *
 *  Created on: 2/4/2015
 *      Author: mauro
 */

#ifndef SDLOBJECTGUI_H_
#define SDLOBJECTGUI_H_
#include "TextureManager.h"
#include "ObjectGUI.h"
#include <sstream>
#include "LoaderParams.h"

class SDLObjectGUI : public ObjectGUI {
public:
	SDLObjectGUI();
	SDLObjectGUI(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	int unitToPixel(float units);
	bool load();
	void setImagePath(string imagePath);
	string getImagePath();
	string getTextureID();
protected:
	string imagePath;
	int positionX;
	int positionY;
	int width;
	int height;
	int zIndex;
	float drawRatio;
	int currentRow;
	int currentFrame;
	std::string textureID;
};
#endif /* SDLOBJECTGUI_H_ */
