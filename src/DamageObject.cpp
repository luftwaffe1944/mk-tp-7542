/*
 * DamageObject.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/DamageObject.h"
#include <SDL.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

DamageObject::DamageObject(){
	this->isDestroy = false;
	this->energy = 1.0f;
}

DamageObject::~DamageObject(){}

float DamageObject::getEnergy(){
	return this->energy;
}
void DamageObject::setEnergy(float newEnergyValue){
	this->energy = newEnergyValue;
}
void DamageObject::setDamage(float damage){
	this->energy = (this->energy - damage);
	if (this->energy <= 0) {
		this->isDestroy = true;
	}
}
void DamageObject::setDOMovement(string movement){
	this->doMovement = movement;
}
string DamageObject::getDOMovement(){
	return this->doMovement;
}

void DamageObject::setIsWeapon(bool isWeapon){
	this->isWeapon = isWeapon;
}

bool DamageObject::isCharacter(){
	return !this->isWeapon;
}
