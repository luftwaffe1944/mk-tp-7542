/*
 * SoundManager.cpp
 *
 *  Created on: 2/6/2015
 *      Author: uje
 */

#include "../headers/SoundManager.h"

SoundManager* SoundManager::cm_pInstance = 0;


void SoundManager::init() {
	//default: Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	Mix_OpenAudio(22050, AUDIO_S16, 2, 128);
	loadBattleSounds();
}

SoundManager::SoundManager() {
	// TODO Auto-generated constructor stub
	//Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager* SoundManager::Instance() {
	if (!cm_pInstance) {
		cm_pInstance = new SoundManager();
		return cm_pInstance;
	} else {
		return cm_pInstance;
	}
}

void SoundManager::clean() {
	Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type) {

	if(type == SOUND_MUSIC) {
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if(pMusic == 0)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = pMusic;
		return true;
	}
	else if(type == SOUND_SFX) {
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if(pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

void SoundManager::playMusic(std::string id, int loop) {
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop) {
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}


void SoundManager::loadBattleSounds() {
	for (std::map<std::string, std::vector<std::string>>::iterator iter = situationalSounds.begin() ; iter  != situationalSounds.end() ; ++iter)
	{
		std::vector<std::string> situationSounds = iter->second;
		for (unsigned int i = 0; i < situationSounds.size() ; ++i) {
			load("sounds/sfx/" + situationSounds[i] + ".ogg", situationSounds[i] ,SOUND_SFX);
		}
	}
}

void SoundManager::playSoundByAction(std::string action, int loop) {
	int randPos = rand() % situationalSounds.at(action).size();
	std::string idSound = situationalSounds.at(action)[randPos];
	playSound(idSound,loop);
}
