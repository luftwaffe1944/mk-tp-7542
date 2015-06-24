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
#include "SoundManager.h"
#include "SecuenceInputManager.h"
#include <algorithm>
//#include "SDL_timer.h"
//#include "SDL.h"
using namespace std;

class GameInfo : public SDLObjectGUI {
public:
	GameInfo(const LoaderParams* pParams, vector<Character*> characters, std::string, std::string);
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
	void timerStart();
	void timerStop();
	void timerPause();
	bool isRoundTriggered();
	void prepareNewRound();
	void triggerSounds();
	bool roundCompleted;
	int currentRound;
private:
	vector<Character*> characters;
	float barWidth;
	SDL_Color frontColor;
	SDL_Color bgColor;
	float percent;
	int fightAnimationTimer;
	int winnerAnimationTimer;
	int finishHimAnimationTimer;
	int fatalityAnimationTimer;
	int babalityAnimationTimer;
	int friendshipAnimationTimer;
	int finishHimToleranceTimer;
	int characterOneWins;
	int characterTwoWins;
	bool lazyAnimationAlreadyTriggered;
	bool initAnimation;
	bool showFightAnimation;
	bool showWinnerAnimation;
	bool showFinishHimAnimation;
	bool showFatalityAnimation;
	bool showBabalityAnimation;
	bool showFriendshipAnimation;
	bool roundTriggered;
	bool roundOneCompleted;
	bool roundTwoCompleted;
	bool roundThreeCompleted;
	bool charOneWon;
	bool charTwoWon;
	bool charOneAlreadyDeath;
	bool charTwoAlreadyDeath;
	bool playingRoundSound;
	bool playingFightSound;
	bool playingCharacterWinsSound;
	bool playingFinishHimSound;
	bool isFinishHimTime;
	Timer timer;
	float msTime;
	std::string idTimer;
	void HealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* pRender, int player);
	void animation();
	void time();
	void loadTextTimer();
	std::string nameOne;
	std::string nameTwo;

	bool gameDraw;

};

#endif /* GAMEINFO_H_ */
