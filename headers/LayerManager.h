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
#include "Character.h"
#include "GameGUI.h"

class LayerManager {
public:
	static LayerManager* Instance() {
		static LayerManager lm_pInstance;
		return &lm_pInstance;
	}

	void init();
	void refresh();

private:
	LayerManager();
	virtual ~LayerManager();
	vector<Layer*> layers;
	vector<Character*> characters;
	float speedFirstLayer;
	float offSceneFirstLayer;
	void updateSpeedLayers(Layer* layer);
	void updateOffScene(Layer* layer);
	void setSpeedFirstLayer();
	void setOffSceneFirstLayer();
};

#endif /* LAYERMANAGER_H_ */
