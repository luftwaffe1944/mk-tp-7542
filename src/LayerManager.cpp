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
	this->characters = GameGUI::getInstance()->getCharacters();
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

void LayerManager::setOffSceneFrontalLayer() {
	Layer* layer;
	unsigned int size = this->layers.size();
	layer = this->layers[size - 1];
	FILE_LOG(logDEBUG) << "layer id: " << layer->getTextureID() << " " << layer->getImagePath();
	float windowSize = GameGUI::getInstance()->getWindow().getWidthPx();
	layer->setLayerOffScene(windowSize);
	this->offSceneFirstLayer = layer->getLayerOffScene();
}

void LayerManager::setSpeedFrontalLayer() {
	Layer* layer;
	unsigned int size = this->layers.size();
	layer = this->layers[size - 1];
	layer->setLayerSpeed(LAYER_SPEED, this->offSceneFirstLayer);
	this->speedFirstLayer = layer->getLayerSpeed();
}

void LayerManager::init() {

	setOffSceneFrontalLayer();
	setSpeedFrontalLayer();

	Layer* layerAux;
	int numberOfLayers = this->layers.size();
	std::cout << numberOfLayers << endl;
	for(int i = numberOfLayers - 2 ; i >= 0  ; i--) {
		layerAux = this->layers[i];
		updateOffScene(layerAux);
		updateSpeedLayers(layerAux);
	}
}

void LayerManager::refresh() {
	Stage stage = GameGUI::getInstance()->getStage();
	Window window = GameGUI::getInstance()->getWindow();
	vector<Character*> characters = GameGUI::getInstance()->getCharacters();

	int stageWidth = stage.getWidth();
	int posXWindow = window.xpos;
	int posXCharacter = characters[0]->getPosX();
	int windowWidth = window.widthPx;
	int characterWidth = characters[0]->getWidth();
	int margin = 200;
	bool refresh = false;
	if(((windowWidth + posXWindow) - (posXCharacter + characterWidth)) < margin) {
		refresh = true;
	}
	for(unsigned int index=0; index < this->layers.size(); ++index) {
		this->layers[index]->setNeedRefresh(refresh);
	}


}
