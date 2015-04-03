/*
 * SDLObjectGUI.cpp
 *
 *  Created on: 2/4/2015
 *      Author: mauro
 */

#include "../headers/SDLObjectGUI.h"
#include "../headers/MKGame.h"

SDLObjectGUI::SDLObjectGUI(const LoaderParams* pParams) : ObjectGUI(pParams) {
	m_x = pParams->getX();
	m_y = pParams->getY();
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLObjectGUI::draw() {
	TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width,
			m_height, m_currentRow, m_currentFrame,
			MKGame::Instance()->getRenderer());
}

void SDLObjectGUI::update(){

}

void SDLObjectGUI::clean(){

}
