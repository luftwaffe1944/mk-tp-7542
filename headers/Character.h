/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Constants.h"
#include "Sprite.h"
#include "InputControl.h"
#include <string>
#include "SDLObjectGUI.h"
#include <SDL.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include "AlternativeColor.h"
#include "Collitionable.h"
#include "DamageObject.h"
using namespace std;


class Character : public SDLObjectGUI, public Collitionable {
private:
	Sprite* currentSprite;
	std::string name;
	int zindex;
	bool isRightOriented;
	float yGround;
	std::string movement;
	std::map<std::string,Sprite*> characterSprites;
	SDL_Renderer* renderer; //TODO: review
	bool isJumping;
	bool isWalkingRight;
	bool isWalkingLeft;
	bool isJumpingRight;
	bool isJumpingLeft;
	bool isDucking;
	std::string playerNumber;
	AlternativeColor* altColor;
	bool isAltPlayer;
	bool isDuckingSingle;
	bool isPunchingHigh;
	bool isPunchingLow;
	bool isPunchingDuck;
	bool isPunchingAnUppercut;
	bool isKickingLow;
	bool isKickingHigh;
	bool isKickingDuckHigh;
	bool isKickingDuckLow;
	bool isKickingSuper;
	bool isKickingAirHigh;
	bool isKickingAirLowRight;
	bool isKickingAirLowLeft;
	bool isBlocking;
	bool isDuckBlocking;
	bool isUnderKick;
	bool isAirPunchingRight;
	bool isAirPunching;
	bool isAirPunchingLeft;

public:
	static std::map<std::string,int> movesCounter;
	Character();
	virtual bool load(SDL_Renderer* );
	void render(SDL_Renderer* render);
	virtual ~Character();
	Character(const LoaderParams* pParams, bool isRightOriented);
	Character(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	int getWidth();
	int getPosX();
	float getYGround();
	bool reachedWindowLeftLimit();
	bool reachedWindowRightLimit();
	std::string getPlayerNumber();
	void setPlayerNumber(std::string playerNumber);
	float getPosXUL();
	//Movement & position methods
	void jump();
	void jumpRight();
	void jumpLeft();
	void walkRight();
	void walkLeft();
	void refreshFrames();
	std::string getMovement();
	void setMovement(std::string movement);
	bool isTouchingGround(float positionY);
	bool shouldMoveForward();
	void clearMovementsFlags();
	bool isMovingRight();
	bool isMovingLeft();

	virtual void getCNextPosition(float* nextPositionX, float* nextPositionY); //redefinir virtual

	string getName();
	AlternativeColor* getAlternativeColor();
	void setAlternativeColor(AlternativeColor*);
	bool getIsAlternativePlayer();
	void setIsAlternativePlayer(bool isAltPlayer);
	bool getIsRightOriented();
	void incrementCounter(string moveKey);
	void setCurrentSprite();
	void resetCounter(string moveKey);
	void completeMovement();
	void setMoveFlag(bool trueOrFalse);
	void airHighKick();
	void airLowKickLeft();
	void airLowKickRight();
	void airPunch();
	void airPunchRight();
	void airPunchLeft();
	void setIsRightOriented(bool isRightOriented);
	Character* getCopyInstance();
	void updateShapesOnStatus();
};

#endif /* CHARACTER_H_ */
