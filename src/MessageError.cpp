/*
 * MessageError.cpp
 *
 *  Created on: 31/3/2015
 *      Author: mauro
 */

#include "../headers/MessageError.h"

MessageError::MessageError(string headMsg, string detailMsg,
		string logLevel) {
	this->headMsg = headMsg;
	this->detailMsg = detailMsg;
	this->logLevel = logLevel;
}

string MessageError::getLogLevel() {
	return this->logLevel;
}

string MessageError::getHeadMsg() {
	return this->headMsg;
}

string MessageError::getDetailMsg() {
	return this->detailMsg;
}
