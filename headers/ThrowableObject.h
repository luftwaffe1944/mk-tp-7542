/*
 * ThrowableObject.h
 *
 *  Created on: 11/5/2015
 *      Author: julian
 */

#ifndef THROWABLEOBJECT_H_
#define THROWABLEOBJECT_H_

#include "Constants.h"
#include <string>
#include "SDLObjectGUI.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Collitionable.h"
#include "DamageObject.h"
#include "Character.h"

#define OBJECT_SPEED 4

class ThrowableObject : public SDLObjectGUI, public Collitionable {
public:
	ThrowableObject(const LoaderParams* pParams, float widthWindow);
	virtual ~ThrowableObject();
	void update();
	void draw();
	void clean();
	void setReleaser(Character* character);
	void setReceiver(Character* character);
	void getCNextPosition(float* nextPositionX, float* nextPositionY);

private:
	Character* releaser;
	Character* receiver;
	bool playerIsRightOriented;
	bool posXSetReleaser;
	bool posYsetReleaser;

	float widthWindow;
};

#endif /* THROWABLEOBJECT_H_ */
