/*
 * LayerManager.h
 *
 *  Created on: 9/4/2015
 *      Author: julian
 */

#ifndef LAYERMANAGER_H_
#define LAYERMANAGER_H_

//#define FRONTAL_LAYER_SPEED 3

#include "Layer.h"
#include "Character.h"
#include "ThrowableObject.h"
#include "GameGUI.h"
#include "Log.h"
#include "Constants.h"
#include "Stage.h"
#include "Window.h"
class LayerManager {
public:
	static LayerManager* Instance();
	void init();
	void refresh();
	virtual ~LayerManager() {
		if (lm_pInstance != NULL) delete lm_pInstance;
		lm_pInstance = NULL;
	}

	void clean();

private:
	static LayerManager* lm_pInstance;
	vector<Layer*> layers;
	vector<Character*> characters;
	Window* window;
	Stage* stage;
	float speedFirstLayer;
	float offSceneFrontalLayer;

	LayerManager();
	void updateSpeedLayers(Layer* layer);
	void updateOffScene(Layer* layer);
	void setSpeedFrontalLayer();
	void setOffSceneFrontalLayer();
	void centerFrontalLayer();
	void centerLayers( Layer* layer);
	bool layerReachedStageLimit(int windowWidth, bool border);
};

#endif /* LAYERMANAGER_H_ */
