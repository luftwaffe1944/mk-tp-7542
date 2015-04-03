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
#include "LoaderParams.h"

class SDLObjectGUI : public ObjectGUI {
public:
	SDLObjectGUI(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;
};
#endif /* SDLOBJECTGUI_H_ */
