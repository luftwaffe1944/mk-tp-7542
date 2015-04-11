/*
 * LayerManager.h
 *
 *  Created on: 9/4/2015
 *      Author: julian
 */

#ifndef LAYERMANAGER_H_
#define LAYERMANAGER_H_

#define LAYER_SPEED 3

#include "Layer.h"
#include "Character.h"
#include "GameGUI.h"
#include "Log.h"

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
	void setSpeedFrontalLayer();
	void setOffSceneFrontalLayer();
	void centerFrontalLayer();
	void centerLayers( Layer* layer);
	bool layerReachedStageLimit(int windowWidth);
};

#endif /* LAYERMANAGER_H_ */
