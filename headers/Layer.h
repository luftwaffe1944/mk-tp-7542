/*
 * Layer.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef LAYER_H_
#define LAYER_H_
#include <string>
using namespace std;

class Layer {
private:
	string backgroundImage;
	int width;

public:
	Layer();
	Layer(string image, int width);
	virtual ~Layer();
};

#endif /* LAYER_H_ */
