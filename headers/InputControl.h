/*
 * InputControl.h
 *
 *  Created on: 31/03/2015
 *      Author: Diego Serra
 */

#ifndef INPUTCONTROL_H_
#define INPUTCONTROL_H_

#include <vector>
#include <string>
#include <map>
#include "SDL.h"



enum InputCommand {
	NO_INPUT,
	FIRST_PLAYER_MOVE_UP,
	FIRST_PLAYER_MOVE_DOWN,
	FIRST_PLAYER_MOVE_LEFT,
	FIRST_PLAYER_MOVE_RIGHT,
	FIRST_PLAYER_MOVE_UP_RIGHT,
	FIRST_PLAYER_MOVE_UP_LEFT,
	FIRST_PLAYER_MOVE_DOWN_RIGHT,
	FIRST_PLAYER_MOVE_DOWN_LEFT,
	RESET,
	FIRST_PLAYER_CHANGE_ORIENTATION,
	FIRST_PLAYER_HI_PUNCH,
	FIRST_PLAYER_LO_PUNCH,
	FIRST_PLAYER_DUCK_PUNCH,
	FIRST_PLAYER_UPPERCUT,
	FIRST_PLAYER_LOW_KICK,
	FIRST_PLAYER_HIGH_KICK,
	FIRST_PLAYER_DUCK_LOW_kICK,
	FIRST_PLAYER_DUCK_HIGH_kICK,
	FIRST_PLAYER_SUPER_kICK,
	FIRST_PLAYER_AIR_HIGH_kICK,
	FIRST_PLAYER_AIR_LOW_kICK_R,
	FIRST_PLAYER_AIR_LOW_kICK_L,
	FIRST_PLAYER_BLOCK,
	FIRST_PLAYER_DUCK_BLOCK,
	FIRST_PLAYER_UNDER_KICK,
	FIRST_PLAYER_AIR_PUNCH_R,
	FIRST_PLAYER_AIR_PUNCH,
	FIRST_PLAYER_AIR_PUNCH_L

};

class InputControl {
private:
	InputCommand firstPlayerMove;
	InputCommand secondPlayerMove;
	InputCommand controlOption;

public:
	static InputControl* Instance() {
		static InputControl t_pInstance;
		return &t_pInstance;
	}
	void refreshInputs();
	void update();
	void clean();
	void initJoysticks();
	InputCommand getFirstPlayerMove();
	InputCommand getSecondPlayerMove();
	InputCommand getControlOption();
	std::vector<std::vector <bool> > joysticksButtonStates;
	std::vector<std::pair <int,int> > joystickAxisStates;
	void refreshJoystickInputs();
	bool isAxisRight(int joystick);
	bool isAxisLeft(int joystick);
	bool isAxisUp(int joystick);
	bool isAxisDown(int joystick);
	std::vector<SDL_Joystick*> joysticks;
	bool getActionButtonState(int joyNum, std::string action);
	void setActionButtonStateFalse(int joy, std::string action);
	std::vector< std::map <std::string, int > > joystickActionButton;
	void setActionButton(int joy, std::string action, int buttonNumber);
	int getActionButton(int joy, std::string action);
};

#endif /* INPUTCONTROL_H_ */
