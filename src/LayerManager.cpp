/*
 * LayerManager.cpp
 *
 *  Created on: 9/4/2015
 *      Author: julian
 */

#include "../headers/LayerManager.h"

LayerManager::LayerManager() {
	this->offSceneFrontalLayer = 0;
	this->speedFirstLayer = 0;
	this->layers = GameGUI::getInstance()->getLayers();
	this->characters = GameGUI::getInstance()->getCharacters();
	this->stage = GameGUI::getInstance()->getStage();
	this->window = GameGUI::getInstance()->getWindow();

}

LayerManager::~LayerManager() {
	// TODO Auto-generated destructor stub
}

void LayerManager::updateSpeedLayers(Layer* layer) {
	layer->setLayerSpeed(this->speedFirstLayer, this->offSceneFrontalLayer);
}

void LayerManager::updateOffScene(Layer* layer) {
	float windowSize = GameGUI::getInstance()->getWindow().getWidthPx();
	layer->setLayerOffScene(windowSize);
}

void LayerManager::setOffSceneFrontalLayer() {
	float windowSize = this->window.getWidthPx();
	Layer* layer;
	unsigned int size = this->layers.size();

	layer = this->layers[size - 1];
	layer->setLayerOffScene(windowSize);
	this->offSceneFrontalLayer = layer->getLayerOffScene();
}

void LayerManager::setSpeedFrontalLayer() {
	Layer* layer;
	unsigned int size = this->layers.size();
	layer = this->layers[size - 1];
	layer->setLayerSpeed(LAYER_SPEED, this->offSceneFrontalLayer);
	this->speedFirstLayer = layer->getLayerSpeed();
}

void LayerManager::centerFrontalLayer() {
	Layer* layer;
	unsigned int size = this->layers.size();
	layer = this->layers[size - 1];
	layer->setPositionX( - layer->getLayerOffScene());

}

void LayerManager::centerLayers( Layer* layer) {
	layer->setPositionX( - layer->getLayerOffScene());
}

void LayerManager::init() {

	setOffSceneFrontalLayer();
	setSpeedFrontalLayer();
	centerFrontalLayer();

	Layer* layerAux;
	int numberOfLayers = this->layers.size();
	std::cout << numberOfLayers << endl;
	for(int i = numberOfLayers - 2 ; i >= 0  ; i--) {
		layerAux = this->layers[i];
		updateOffScene(layerAux);
		updateSpeedLayers(layerAux);
		centerLayers(layerAux);
	}
}

bool LayerManager::layerReachedStageLimit(int windowWidth) {
	Layer* frontalLayer = this->layers[this->layers.size() - 1 ];
	float frontalLayerOffset = frontalLayer->getScrollingOffset();
	if (( frontalLayerOffset < ( - frontalLayer->getWidth() / 2 + windowWidth / 2 )) ||
			( frontalLayerOffset > (  frontalLayer->getWidth() / 2 - windowWidth / 2 ))  ){
		return true;
	}
	return false;
}

void LayerManager::refresh() {
	int stageWidth = this->stage.getWidth();
	int posXWindow = this->window.xpos;
	int posXCharacter = this->characters[0]->getPosX();
	int windowWidth = this->window.widthPx;
	int characterWidth = this->characters[0]->getWidth();
	int margin = 10;
	bool refresh = false;
	int orientation;


	if ( ( (windowWidth - (posXCharacter + characterWidth)) < margin) && !layerReachedStageLimit( windowWidth) ) {
		refresh = true;
		orientation = 1;
	}
	if  (( posXCharacter < margin ) && !layerReachedStageLimit( windowWidth)) {
		refresh = true;
		orientation = -1;
	}

	for(unsigned int index=0; index < this->layers.size(); ++index) {
		this->layers[index]->setNeedRefresh(refresh);
		this->layers[index]->setOrientation(orientation);
	}
}
