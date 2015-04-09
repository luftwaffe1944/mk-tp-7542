/*
 * LayerManager.h
 *
 *  Created on: 9/4/2015
 *      Author: julian
 */

#ifndef LAYERMANAGER_H_
#define LAYERMANAGER_H_

#define LAYER_SPEED 0.5

#include "Layer.h"
#include "GameGUI.h"

class LayerManager {
public:
	LayerManager();
	virtual ~LayerManager();
	void update();

private:
	vector<Layer*> layers;
	float speedFirstLayer;
	float offSceneFirstLayer;
	void updateSpeedLayers(Layer* layer);
	void updateOffScene(Layer* layer);
	void setSpeedFirstLayer();
	void setOffSceneFirstLayer();
};

#endif /* LAYERMANAGER_H_ */
