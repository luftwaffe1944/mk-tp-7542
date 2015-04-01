/*
 * MessageError.h
 *
 *  Created on: 31/3/2015
 *      Author: mauro
 */

#ifndef MESSAGEERROR_H_
#define MESSAGEERROR_H_

#include <string>
using namespace std;

class MessageError{
private:
	string headMsg;
	string detailMsg;
	string logLevel;
public:
	MessageError();
	MessageError(string headMsg, string detailMsg, string logLevel);
	string getHeadMsg();
	string getDetailMsg();
	string getLogLevel();
	virtual ~MessageError(){

	};
};

#endif /* MESSAGEERROR_H_ */


