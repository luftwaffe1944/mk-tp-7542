/*
 * Layer.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Layer.h"

Layer::Layer() {

}

Layer::Layer(string image, int width) {
	this->backgroundImage = image;
	this->width = width;
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

