/*
 * MessageError.h
 *
 *  Created on: 31/3/2015
 *      Author: mauro
 */

#ifndef MESSAGEERROR_H_
#define MESSAGEERROR_H_

using namespace std;
#include "Log.h"

class MessageError {
private:
	string headMsg;
	string detailMsg;
	TLogLevel logLevel;
public:
	MessageError();
	MessageError(string headMsg, string detailMsg, TLogLevel logLevel) {
		this->headMsg = headMsg;
		this->detailMsg = detailMsg;
		this->logLevel = logLevel;
	};
	string getHeadMsg();
	string getDetailMsg();
	TLogLevel getLogLevel();
	virtual ~MessageError(){

	};
};

#endif /* MESSAGEERROR_H_ */
