/*
 * LayerManager.cpp
 *
 *  Created on: 9/4/2015
 *      Author: julian
 */

#include "../headers/LayerManager.h"

LayerManager::LayerManager() {
	this->offSceneFirstLayer = 0;
	this->speedFirstLayer = 0;
	this->layers = GameGUI::getInstance()->getLayers();

}

LayerManager::~LayerManager() {
	// TODO Auto-generated destructor stub
}

void LayerManager::updateSpeedLayers(Layer* layer) {
	layer->setLayerSpeed(this->speedFirstLayer, this->offSceneFirstLayer);
}

void LayerManager::updateOffScene(Layer* layer) {
	float windowSize = GameGUI::getInstance()->getWindow().getWidthPx();
	layer->setLayerOffScene(windowSize);
}

void LayerManager::setOffSceneFirstLayer() {
	Layer* layer;
	layer = this->layers[0];
	float windowSize = GameGUI::getInstance()->getWindow().getWidthPx();
	layer->setLayerOffScene(windowSize);

	this->offSceneFirstLayer = layer->getLayerOffScene();
}

void LayerManager::setSpeedFirstLayer() {
	Layer* layer;
	layer = this->layers[0];
	layer->setLayerSpeed(LAYER_SPEED, this->offSceneFirstLayer);

	this->speedFirstLayer = layer->getLayerSpeed();
}


