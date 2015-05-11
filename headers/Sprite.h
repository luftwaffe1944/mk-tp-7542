/*
 * Sprite.h
 *
 *  Created on: Apr 4, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include "Log.h"
#include "TextureManager.h"
#include "InputControl.h"
#include "AlternativeColor.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Sprite {
public:
	Sprite();
	virtual ~Sprite();
	Sprite(std::string id, std::string spritePath, SDL_Renderer* m_pRenderer, int w, int h, int framesAmount);
	Sprite(std::string id, std::string spritePath, SDL_Renderer* m_pRenderer, int w, int h, int framesAmount, bool isAltPlayer, AlternativeColor* altColor);
    //void runForward(int firstFrame, int lastFrame, float fpsSpeed);
    //void runBackward(int firstFrame, int lastFrame, float fpsSpeed);
    std::string getSpriteId();
    int getSpriteWidth();
    int getSpriteHeight();
    int getNextForwardingFrame();
    int getNextBackwardingFrame();
    int getNextFrameWithLimit();
    void refresh();
    int getCurrentFrame();
    int getFramesAmount();

private:
    std::string spriteId;
    int spriteWidth;
    int spriteHeight;
    int currentFrame;
    //int animationDelay;
    int framesAmount;
};

#endif /* SPRITE_H_ */
