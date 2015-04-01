/*
 * InputControl.h
 *
 *  Created on: 31/03/2015
 *      Author: Diego Serra
 */

#ifndef INPUTCONTROL_H_
#define INPUTCONTROL_H_

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
	RESET
};

class InputControl {
private:
	InputCommand firstPlayerMove;
	InputCommand secondPlayerMove;
	InputCommand controlOption;
public:
	InputControl();
	void refreshInputs();
	InputCommand getFirstPlayerMove();
	InputCommand getSecondPlayerMove();
	InputCommand getControlOption();
};

#endif /* INPUTCONTROL_H_ */
