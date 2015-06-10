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
#include "TextureManager.h"
#include "MKGame.h"
#include "GameGUI.h"
#include "Window.h"

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

	std::string specialSecuenceOne;
	std::string specialSecuenceTwo;
	bool specialSecuenceOneActive;
	bool specialSecuenceTwoActive;

private:
	static SecuenceInputManager* dm_pInstance;
	SecuenceInputManager();

	std::vector<std::string> currentSpecialSecuences;
	std::string textureID;

};

#endif /* SECUENCEINPUTMANAGER_H_ */
