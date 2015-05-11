/*
 * InputControl.h
 *
 *  Created on: 31/03/2015
 *      Author: Diego Serra
 *
 * llamar al metodo refreshInputs para obtener los nuevos estados de las entradas,
 * hacer la llamada luego del ciclo de vacia la lista de eventos de SDL, while (SDL_PollEvent(&event))
 *
 *
 */

#include "../headers/InputControl.h"
#include "SDL.h"
#include "../headers/MKGame.h"
#include <stddef.h>

bool somePunchButtonPressed(const Uint8* keyBoard);
bool someKickButtonPressed(const Uint8* keyBoard);

void InputControl::refreshInputs() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_UP]) {

		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !somePunchButtonPressed(currentKeyStates)
				&& !someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			cout << "GFAFASFAFA" << endl;
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_A]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_S]) {
			this->firstPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_Z]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_X]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (currentKeyStates[SDL_SCANCODE_X]){
			this->firstPlayerMove = FIRST_PLAYER_SUPER_kICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_Z]){
			this->firstPlayerMove = FIRST_PLAYER_UNDER_KICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !currentKeyStates[SDL_SCANCODE_LCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		}
		else if (currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_S]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_HI_PUNCH;
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if((currentKeyStates[SDL_SCANCODE_DOWN])){
			this->firstPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_X]) {
		this->firstPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_Z]) {
		this->firstPlayerMove = FIRST_PLAYER_LOW_KICK;
	}

}

void InputControl::refreshJoystickInputs(){

	this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	int joystick = 0;


	if ( (this->isAxisUp( joystick ) )
			&& !(this->isAxisDown( joystick ))
			&& (this->isAxisLeft( joystick ))
			&& !(this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
	} else if ((this->isAxisUp( joystick ))
			&& !(this->isAxisDown( joystick ))
			&& !(this->isAxisLeft( joystick ))
			&& (this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
	} else if (!(this->isAxisUp( joystick ))
			&& (this->isAxisDown( joystick ))
			&& !(this->isAxisLeft( joystick ))
			&& (this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
	} else if (!(this->isAxisUp( joystick ))
			&& (this->isAxisDown( joystick ))
			&& (this->isAxisLeft( joystick ))
			&& !(this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
	} else if ((this->isAxisUp( joystick ))
			&& !(this->isAxisDown( joystick ))
			&& !(this->isAxisLeft( joystick ))
			&& !(this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_UP;
	} else if (!(this->isAxisUp( joystick ))
			&& (this->isAxisDown( joystick ))
			&& !(this->isAxisLeft( joystick ))
			&& !(this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN;
	} else if (!(this->isAxisUp( joystick ))
			&& !(this->isAxisDown( joystick ))
			&& (this->isAxisLeft( joystick ))
			&& !(this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_LEFT;
	} else if (!(this->isAxisUp( joystick ))
			&& !(this->isAxisDown( joystick ))
			&& !(this->isAxisLeft( joystick ))
			&& (this->isAxisRight( joystick ))) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_RIGHT;

	}
}

bool InputControl::isAxisRight(int joystick) {
	return this->joystickAxisStates[joystick].first > 0;
}

bool InputControl::isAxisLeft(int joystick) {
	return this->joystickAxisStates[joystick].first < 0;
}

bool InputControl::isAxisUp(int joystick) {
	return this->joystickAxisStates[joystick].second < 0;
}

bool InputControl::isAxisDown(int joystick) {
	return this->joystickAxisStates[joystick].second > 0;
}

InputCommand InputControl::getFirstPlayerMove() {
	return this->firstPlayerMove;
}

InputCommand InputControl::getSecondPlayerMove() {
	return this->secondPlayerMove;
}

InputCommand InputControl::getControlOption() {
	return this->controlOption;
}

void InputControl::initJoysticks() {

	FILE_LOG(logDEBUG) << "Number of Joysticks connected: " << SDL_NumJoysticks();

	//Check for joysticks
	if( SDL_NumJoysticks() < 1 ) {

		FILE_LOG(logERROR) << "Error: No joysticks connected!";

	} else {

		SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1"); //Linea magica que hace que funcione el input del joystick

		//Load joysticks
		for (int i = 0; i < SDL_NumJoysticks(); i++) {

			SDL_Joystick* joystick = SDL_JoystickOpen(i);

			if (joystick == NULL) {

				FILE_LOG(logERROR) << "Failed to open joystick " << i << SDL_GetError();

			} else {

				int buttonCount = SDL_JoystickNumButtons(joystick);

				FILE_LOG(logDEBUG) << "Joystick " << i << " button count " << buttonCount;

				std::vector<bool> buttonStates;

				for ( int j = 0; j < buttonCount; j++) {
					buttonStates.push_back(false);
				}

				this->joysticksButtonStates.push_back(buttonStates);
				this->joysticks.push_back(joystick);

				this->joystickAxisStates.push_back({0,0});
				FILE_LOG(logDEBUG) << "Joystick " << i << " initialized";
			}
		}
	}
}


void InputControl::update() {
}



void InputControl::clean() {

	for (unsigned int i = 0; i < this->joysticks.size(); i++){
		SDL_JoystickClose(this->joysticks[i]);
	}
	this->joysticks.clear();


}

bool someKickButtonPressed(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_Z]) || (keyBoard[SDL_SCANCODE_X]);
}

bool somePunchButtonPressed(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_A]) || (keyBoard[SDL_SCANCODE_S]);
}
