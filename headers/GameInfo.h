/*
 * GameInfo.h
 *
 *  Created on: 23/4/2015
 *      Author: julian
 */

#ifndef GAMEINFO_H_
#define GAMEINFO_H_
#include <iostream>
#include <vector>
#include "Log.h"
#include "Constants.h"
#include "SDLObjectGUI.h"
#include "MKGame.h"
#include "Timer.h"
#include <algorithm>
using namespace std;

class GameInfo : public SDLObjectGUI {
public:
	GameInfo(const LoaderParams* pParams, vector<Character*> characters);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void init();
	void refresh();
	virtual ~GameInfo() {
		delete this->pParams;
		this->timer.stop();
		TTF_Quit();
	}
	virtual bool load();
	virtual bool load(SDL_Renderer* r);
private:
	vector<Character*> characters;
	float barWidth;
	SDL_Color frontColor;
	SDL_Color bgColor;
	float percent;
	bool initAnimation;
	Timer timer;
	float msTime;
	std::string idTimer;
	void HealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* pRender, int player);
	void animation();
	void time();
	void loadTextTimer();

};

#endif /* GAMEINFO_H_ */
