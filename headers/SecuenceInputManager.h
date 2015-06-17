/*
 * SecuenceInputManager.h
 *
 *
 *      Author: diego
 */

#ifndef SECUENCEINPUTMANAGER_H_
#define SECUENCEINPUTMANAGER_H_

#include <iostream>
#include <map>
#include <vector>
#include "SDL.h"
#include "Timer.h"
#include "TextureManager.h"
#include "MKGame.h"
#include "GameGUI.h"
#include "Window.h"
#include "Constants.h"

using namespace std;

class SecuenceInputManager {
public:

	static SecuenceInputManager* Instance();
	virtual ~SecuenceInputManager() {
			delete(dm_pInstance);
			dm_pInstance = NULL;
	}

	bool load();
	void draw();
	void update();
	void clean();
	void init();
	void refresh();
	void reset(int secNum);
	int detectSpecialSecuence(int playerNum);
	bool getIsSetMove(int num);

	std::string specialSecuenceOne;
	std::string specialSecuenceOnePreview;
	std::string specialSecuenceTwo;
	std::string specialSecuenceTwoPreview;
	bool specialSecuenceOneActive;
	bool specialSecuenceTwoActive;

	Timer timerOne;
	Timer timerTwo;
	float elapsedTimeOne;
	float elapsedTimeTwo;

	bool joy1DownPressOnce;
	bool joy1UpPressOnce;
	bool joy1LeftPressOnce;
	bool joy1RightPressOnce;
	bool joy1BlockPressOnce;
	bool joy2DownPressOnce;
	bool joy2UpPressOnce;
	bool joy2LeftPressOnce;
	bool joy2RightPressOnce;
	bool joy2BlockPressOnce;
	bool fatalityTime;
	bool drawSecuenceOne;
	bool drawSecuenceTwo;

private:
	static SecuenceInputManager* dm_pInstance;
	SecuenceInputManager();
	std::string getCleanSecuence();
	void loadSpecialMoves();
	void cleanVectorColorChar(int num);
	void setColorChar(int index,int num);
	void setColorPhrase(int index,int num);


	std::vector<std::string> specialMoves;
	std::string textureID;

	bool isMatchOne;
	bool isMatchTwo;
	float elapsedTimeToShowMatchOne;
	float elapsedTimeToShowMatchTwo;
	bool isSetMoveOne;
	bool isSetMoveTwo;
	std::vector<bool> colorCharOne;
	std::vector<bool> colorCharTwo;



};

#endif /* SECUENCEINPUTMANAGER_H_ */
