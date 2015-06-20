/*
 * VisualEffect.h
 *
 *  Created on: 20/6/2015
 *      Author: uje
 */

#ifndef VISUALEFFECT_H_
#define VISUALEFFECT_H_

#include "SDLObjectGUI.h"

class VisualEffect : public SDLObjectGUI{
public:
	VisualEffect(const LoaderParams* pParams);
	virtual ~VisualEffect();

	virtual void draw();
	virtual void update();
	virtual void clean();
	void setImagePath(std::string path);
	void animate();
	void endAnimation();
private:
	bool visible = false;
	unsigned int duration = 3000;
	unsigned int startTime = 0;
	//Sprite* currentSprite;
	//SDL_Renderer* renderer;
	//void render(SDL_Renderer* render);

};

#endif /* VISUALEFFECT_H_ */
