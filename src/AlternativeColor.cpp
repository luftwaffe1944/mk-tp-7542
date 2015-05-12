/*
 * AlternativeColor.cpp
 *
 *  Created on: May 9, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/AlternativeColor.h"

AlternativeColor::AlternativeColor(double initialh, double finalH, double shift) {
	this->initial_h = initialh;
	this->final_h = finalH;
	this->shift = shift;
}


double AlternativeColor::getInitialH() {
	return this->initial_h;
}

double AlternativeColor::getFinalH() {
	return this->final_h;
}

double AlternativeColor::getShift() {
	return this->shift;
}

void AlternativeColor::setInitialH(double initialH) {
	this->initial_h = initialH;
}

void AlternativeColor::setFinalH(double finalH) {
	this->initial_h = finalH;
}

void AlternativeColor::setShift(double shift) {
	this->shift = shift;
}


AlternativeColor::AlternativeColor() {
	// TODO Auto-generated constructor stub

}

AlternativeColor::~AlternativeColor() {
	// TODO Auto-generated destructor stub
}
