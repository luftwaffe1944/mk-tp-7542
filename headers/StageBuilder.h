/*
 * StageBuilder.h
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#ifndef STAGEBUILDER_H_
#define STAGEBUILDER_H_
#include <fstream>
#include <json/value.h>
#include "Stage.h"

class StageBuilder {
public:
	StageBuilder();
	Stage create();
	virtual ~StageBuilder();
};

#endif /* STAGEBUILDER_H_ */
