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

bool somePunchButtonPressed1(const Uint8* keyBoard);
bool someKickButtonPressed1(const Uint8* keyBoard);

bool somePunchButtonPressed2(const Uint8* keyBoard);
bool someKickButtonPressed2(const Uint8* keyBoard);


void InputControl::refreshInputs() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	//this->firstPlayerMove = NO_INPUT;
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
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(someKickButtonPressed(currentKeyStates))
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_A]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_S]) {
			this->secondPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_Z]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_X]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (currentKeyStates[SDL_SCANCODE_X]){
			this->secondPlayerMove = FIRST_PLAYER_SUPER_kICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_Z]){
			this->secondPlayerMove = FIRST_PLAYER_UNDER_KICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !currentKeyStates[SDL_SCANCODE_LCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		}
		else if (currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_S]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_HI_PUNCH;
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if((currentKeyStates[SDL_SCANCODE_DOWN])){
			this->secondPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_X]) {
		this->secondPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_Z]) {
		this->secondPlayerMove = FIRST_PLAYER_LOW_KICK;
	}

}
void InputControl::refreshInputs1() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	//this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_W]) {

		if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !somePunchButtonPressed1(currentKeyStates)
				&& !someKickButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& somePunchButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& somePunchButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& somePunchButtonPressed1(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& someKickButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& !(someKickButtonPressed1(currentKeyStates))
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& someKickButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& someKickButtonPressed1(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_S] && !currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_F]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_G]) {
			this->firstPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_V]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_B]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		if (currentKeyStates[SDL_SCANCODE_B]){
			this->firstPlayerMove = FIRST_PLAYER_SUPER_kICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_V]){
			this->firstPlayerMove = FIRST_PLAYER_UNDER_KICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_D]) {
		if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_S])
				&& !currentKeyStates[SDL_SCANCODE_LCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_A])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		}
		else if (currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_G]) {
		if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_HI_PUNCH;
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_F]) {
		if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_S])) {
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if((currentKeyStates[SDL_SCANCODE_S])){
			this->firstPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_B]) {
		this->firstPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_V]) {
		this->firstPlayerMove = FIRST_PLAYER_LOW_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_Q]) {
		this->firstPlayerMove = SUBZERO_SWEEP;
	}
	else if (currentKeyStates[SDL_SCANCODE_E]) {
		this->firstPlayerMove = FIRST_PLAYER_FIRE;
	}

}


void InputControl::refreshInputs2() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	//this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_UP]) {

		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !somePunchButtonPressed2(currentKeyStates)
				&& !someKickButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed2(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(someKickButtonPressed2(currentKeyStates))
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed2(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_RCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_J]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_K]) {
			this->secondPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_N]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_M]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (currentKeyStates[SDL_SCANCODE_M]){
			this->secondPlayerMove = FIRST_PLAYER_SUPER_kICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_N]){
			this->secondPlayerMove = FIRST_PLAYER_UNDER_KICK;
		}
		else if (currentKeyStates[SDL_SCANCODE_RCTRL]){
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !currentKeyStates[SDL_SCANCODE_RCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		}
		else if (currentKeyStates[SDL_SCANCODE_RCTRL]){
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_K]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_HI_PUNCH;
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_J]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_RCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		else if((currentKeyStates[SDL_SCANCODE_DOWN])){
			this->secondPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_M]) {
		this->secondPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_N]) {
		this->secondPlayerMove = FIRST_PLAYER_LOW_KICK;
	}

}


void InputControl::refreshJoystickInputs() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	int character = 0;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else {
		for (int joystick = 0; joystick < SDL_NumJoysticks() ; joystick ++) {

			if (isAxisUp(joystick)) {

				if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& !someJoyPunchButtonPressed( joystick )
						&& !someJoyKickButtonPressed( joystick )
						&& !(isAxisRight(joystick))
						&& !getActionButtonState( joystick, FIRE)) {
					setPlayerMove( joystick, FIRST_PLAYER_MOVE_UP);
				} else if (	!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& !someJoyPunchButtonPressed( joystick )
						&& !someJoyKickButtonPressed( joystick )
						&& !(isAxisRight(joystick))
						&& getActionButtonState( joystick, FIRE)) {
					setPlayerMove( joystick, FIRST_PLAYER_FIRE);
				} else if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& someJoyPunchButtonPressed( joystick )
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_AIR_PUNCH);
				} else if (!(isAxisDown(joystick))
						&& (isAxisLeft(joystick))
						&& someJoyPunchButtonPressed( joystick )
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_AIR_PUNCH_L);
				} else if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& someJoyPunchButtonPressed( joystick )
						&& (isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_AIR_PUNCH_R);
				} else if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& someJoyKickButtonPressed( joystick )
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_AIR_HIGH_kICK);
				} else if (!(isAxisDown(joystick))
						&& (isAxisLeft(joystick))
						&& !(someJoyKickButtonPressed( joystick ))
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_MOVE_UP_LEFT);
				} else if (!(isAxisDown(joystick))
						&& (isAxisLeft(joystick))
						&& someJoyKickButtonPressed( joystick )
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_AIR_LOW_kICK_L);
				} else if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& someJoyKickButtonPressed( joystick )
						&& (isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_AIR_LOW_kICK_R);
				} else if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& (isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_MOVE_UP_RIGHT);
				}

					//COMBINATION WITH DOWN
			} else if (isAxisDown(joystick) && !getActionButtonState(joystick, BLOCK)) {

				if (getActionButtonState(joystick, LOW_PUNCH)) {
					setPlayerMove( joystick,  FIRST_PLAYER_DUCK_PUNCH);
					setActionButtonStateFalse(joystick,LOW_PUNCH);
				} else if ( getActionButtonState( joystick, FIRE) ) {
					setPlayerMove( joystick, FIRST_PLAYER_DUCK_FIRE);
				} else if (getActionButtonState(joystick,HIGH_PUNCH)) {
					setPlayerMove( joystick,  FIRST_PLAYER_UPPERCUT);
					setActionButtonStateFalse(joystick,HIGH_PUNCH);
				} else if (getActionButtonState(joystick,LOW_KICK)) {
					setPlayerMove( joystick,  FIRST_PLAYER_DUCK_LOW_kICK);
					setActionButtonStateFalse(joystick,LOW_KICK);
				} else if (getActionButtonState(joystick,HIGH_KICK)) {
					setPlayerMove( joystick,  FIRST_PLAYER_DUCK_HIGH_kICK);
					setActionButtonStateFalse(joystick,HIGH_KICK);
				} else if (!(isAxisUp( joystick ))
						&& !(isAxisLeft( joystick ))
						&& (isAxisRight( joystick ))) {
					setPlayerMove( joystick,  FIRST_PLAYER_MOVE_DOWN_RIGHT);
				} else if (!(isAxisUp( joystick ))
						&& (isAxisLeft( joystick ))
						&& !(isAxisRight( joystick ))) {
					setPlayerMove( joystick,  FIRST_PLAYER_MOVE_DOWN_LEFT);
				} else if (!(isAxisUp( joystick ))
						&& !(isAxisLeft( joystick ))
						&& !(isAxisRight( joystick ))) {
					setPlayerMove( joystick,  FIRST_PLAYER_MOVE_DOWN);

				}
					//COMBINATION WITH LEFT
			} else if (isAxisLeft(joystick)) {
				if (getActionButtonState(joystick,HIGH_KICK)){
					if ( GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented() ) {
						this->setPlayerMove( joystick,  FIRST_PLAYER_SUPER_kICK);
					} else {
						this->setPlayerMove( joystick,  FIRST_PLAYER_HIGH_KICK);
					}
				}
				else if (getActionButtonState(joystick,BLOCK)){
					setPlayerMove( joystick, FIRST_PLAYER_BLOCK);
				}
				else if (this->getActionButtonState(joystick,LOW_KICK)){
					if ( GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented() ) {
						this->setPlayerMove( joystick,  FIRST_PLAYER_UNDER_KICK);
					} else {
						this->setPlayerMove( joystick,  FIRST_PLAYER_LOW_KICK);
					}
				}
				else if (this->getActionButtonState(joystick,LOW_PUNCH)){
					this->setPlayerMove( joystick,  FIRST_PLAYER_LO_PUNCH);
					this->setActionButtonStateFalse(joystick,LOW_PUNCH);
				}
				else if (this->getActionButtonState(joystick,HIGH_PUNCH)){
					this->setPlayerMove( joystick,  FIRST_PLAYER_HI_PUNCH);
					this->setActionButtonStateFalse(joystick,HIGH_PUNCH);
				}
				else if (!(isAxisUp(joystick))
						&& !(isAxisDown(joystick))
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_MOVE_LEFT);
				}
					//COMBINATION WITH RIGHT
			} else if (isAxisRight(joystick)) {
				if (getActionButtonState(joystick,HIGH_KICK)){
					if ( !GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented() ) {
						this->setPlayerMove( joystick,  FIRST_PLAYER_SUPER_kICK);
					} else {
						this->setPlayerMove( joystick,  FIRST_PLAYER_HIGH_KICK);
					}
					this->setActionButtonStateFalse(joystick,HIGH_KICK);

				}
				else if (this->getActionButtonState(joystick,LOW_KICK)){
					if ( !GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented() ) {
						this->setPlayerMove( joystick,  FIRST_PLAYER_UNDER_KICK);
					} else {
						this->setPlayerMove( joystick,  FIRST_PLAYER_LOW_KICK);
					}
				}
				else if (this->getActionButtonState(joystick,LOW_PUNCH)){
					this->setPlayerMove( joystick,  FIRST_PLAYER_LO_PUNCH);
					this->setActionButtonStateFalse(joystick,LOW_PUNCH);
				}
				else if (this->getActionButtonState(joystick,HIGH_PUNCH)){
					this->setPlayerMove( joystick,  FIRST_PLAYER_HI_PUNCH);
					this->setActionButtonStateFalse(joystick,HIGH_PUNCH);
				}
				else if (!(isAxisUp(joystick))
						&& !(isAxisDown(joystick))
						&& !getActionButtonState(joystick,BLOCK)
						&& !(isAxisLeft(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_MOVE_RIGHT);
				}
				else if (getActionButtonState(joystick,BLOCK)){
					setPlayerMove( joystick, FIRST_PLAYER_BLOCK);
				}
				//COMBINATION WITH S
			} else if (getActionButtonState(joystick,HIGH_PUNCH)) {
				if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_HI_PUNCH);
				}
					//COMBINATION WITH A
			} else if (getActionButtonState(joystick,LOW_PUNCH)) {
				if (!(isAxisDown(joystick))
						&& !(isAxisLeft(joystick))
						&& !(isAxisRight(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_LO_PUNCH);
				}

				//COMBINATION WITH LEFT CTRL
			} else if (getActionButtonState(joystick,BLOCK)) {
				if (!(isAxisDown(joystick))) {
					setPlayerMove( joystick, FIRST_PLAYER_BLOCK);
				}
				else if((isAxisDown(joystick))){
					setPlayerMove( joystick, FIRST_PLAYER_DUCK_BLOCK);
				}

			} else if (getActionButtonState(joystick,HIGH_KICK)) {
				setPlayerMove( joystick, FIRST_PLAYER_HIGH_KICK);
			}

			else if (getActionButtonState(joystick,LOW_KICK)) {
				setPlayerMove( joystick, FIRST_PLAYER_LOW_KICK);
			}
			else if (getActionButtonState( joystick, FIRE)) {
				setPlayerMove( joystick, FIRST_PLAYER_FIRE);
			}
			this->setActionButtonStateFalse(joystick,HIGH_KICK);
			this->setActionButtonStateFalse(joystick,LOW_KICK);
			this->setActionButtonStateFalse(joystick,HIGH_PUNCH);
			this->setActionButtonStateFalse(joystick,LOW_PUNCH);
			this->setActionButtonStateFalse(joystick,FIRE);
		}
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

void InputControl::validateButtonsRange(int joyNum, int butCount) {

	int lk = joystickActionButton[joyNum][LOW_KICK];
	int hk = joystickActionButton[joyNum][HIGH_KICK];
	int lp = joystickActionButton[joyNum][LOW_PUNCH];
	int hp = joystickActionButton[joyNum][HIGH_PUNCH];
	int bl = joystickActionButton[joyNum][BLOCK];
	int fr = joystickActionButton[joyNum][FIRE];

	if ( lk > butCount || hk > butCount || lp > butCount || hp > butCount || bl > butCount || fr > butCount ) {
		FILE_LOG(logERROR) << "Setted button in joystick " << joyNum << " is higher than buttons in joystick (" << butCount << ")";
		FILE_LOG(logERROR) << "Bad buttons configuration in joystick " << joyNum << ", default configuration loaded";
		this->loadDefaultButtons(joyNum);
	}
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

				validateButtonsRange(i, buttonCount);

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

void InputControl::setActionButton(int joy, string action, int button) {

//	std::cout << SDL_JoystickNumButtons(this->joysticks[joy]) << std::endl;
	std::vector< std::map <std::string, int > > joysticks;
	std::map<std::string, int> actionButton;
	joysticks.push_back(actionButton);

	this->joystickActionButton.push_back(joysticks[0]);

	this->joystickActionButton.at(joy)[action] = button;


}

int InputControl::getActionButton(int joy, string action) {
	return this->joystickActionButton[joy][action];
}

bool InputControl::getActionButtonState(int joyNum, string action) {
	int buttonNumber = this->getActionButton(joyNum, action);
	return this->joysticksButtonStates[joyNum][ buttonNumber];
}

void InputControl::setActionButtonStateFalse(int joy, string action) {
	int button = this->getActionButton(joy,action);
	this->joysticksButtonStates[joy][button] = false;
}


bool someKickButtonPressed(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_Z]) || (keyBoard[SDL_SCANCODE_X]);
}

bool somePunchButtonPressed(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_A]) || (keyBoard[SDL_SCANCODE_S]);
}

bool someKickButtonPressed1(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_V]) || (keyBoard[SDL_SCANCODE_B]);
}

bool somePunchButtonPressed1(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_F]) || (keyBoard[SDL_SCANCODE_G]);
}

bool someKickButtonPressed2(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_N]) || (keyBoard[SDL_SCANCODE_M]);
}

bool somePunchButtonPressed2(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_J]) || (keyBoard[SDL_SCANCODE_K]);
}
bool InputControl::someJoyKickButtonPressed(int joy) {
	return (getActionButtonState(joy, LOW_KICK)) || (getActionButtonState(joy, HIGH_KICK) ) ;
}

bool InputControl::someJoyPunchButtonPressed(int joy) {
	return (getActionButtonState(joy, LOW_PUNCH)) || (getActionButtonState(joy, HIGH_PUNCH));
}

void InputControl::setPlayerMove(int joy, InputCommand action) {
	//this->playerMove[joy] = action;
	if (joy == 0) this->firstPlayerMove = action;
	else if (joy == 1) this->secondPlayerMove = action;
}

InputCommand InputControl::getPlayerMove(int joy) {
	return this->playerMove[joy];
}

void InputControl::loadDefaultButtons(int joyNum) {
	setActionButton(joyNum, LOW_PUNCH, 1 );
	setActionButton(joyNum, HIGH_PUNCH, 0 );
	setActionButton(joyNum, LOW_KICK, 2 );
	setActionButton(joyNum, HIGH_KICK, 3 );
	setActionButton(joyNum, BLOCK, 4 );
	setActionButton(joyNum, FIRE, 5 );
}

void InputControl::setSecondPlayerMove(InputCommand action) {
	this->secondPlayerMove = action;
}
