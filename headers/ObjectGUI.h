/*
 * ObjectGUI.h
 *
 *  Created on: 2/4/2015
 *      Author: mauro
 */

#ifndef OBJECTGUI_H_
#define OBJECTGUI_H_
#include <iostream>
#include "TextureManager.h"
#include "LoaderParams.h"
#include "SDL.h"
using namespace std;

class ObjectGUI {
public:
	virtual void draw()=0;
	virtual void update()=0;
	virtual void clean()=0;
protected:
	ObjectGUI(){}
	ObjectGUI(const LoaderParams* pParams) {}
	virtual ~ObjectGUI() {}
};

#endif /* OBJECTGUI_H_ */
