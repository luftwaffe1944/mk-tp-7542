/*
 * SoundManager.cpp
 *
 *  Created on: 2/6/2015
 *      Author: uje
 */

#include "../headers/SoundManager.h"

//SoundManager* SoundManager::cm_pInstance = NULL;
SoundManager* SoundManager::s_pInstance = 0;


void SoundManager::init() {
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	//loadBattleSounds();
	//load("sounds/music/fightMusic64.ogg","fightMusic64",SOUND_MUSIC);
	//Mix_OpenAudio(22050, AUDIO_S16, 2, 128);
	createSituationalSoundsMap(situationalSounds);
	loadBattleSounds();
}

SoundManager::SoundManager() {
	// TODO Auto-generated constructor stub
	//Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	//init();
	//Mix_OpenAudio(22050, AUDIO_S16, 2, 128);

}

SoundManager::~SoundManager()
{
//	Mix_CloseAudio();
}
/*
SoundManager* SoundManager::Instance() {
	if (!cm_pInstance) {
		cm_pInstance = new SoundManager();
		return cm_pInstance;
	} else {
		return cm_pInstance;
	}
}
*/
void SoundManager::clean() {
	//
	Mix_CloseAudio();
	if (this->s_pInstance) {
		delete this->s_pInstance;
		this->s_pInstance = 0;

	}
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

void SoundManager::playSoundOnce(std::string id, int loop) {
	int containKey = soundsPlayed.count(id);
	if (containKey == 0) {
		Mix_PlayChannel(-1, m_sfxs[id], loop);
	}
	incrementSound(id);

}


void SoundManager::loadBattleSounds() {
	for (std::map<std::string, std::vector<std::string> >::iterator iter = situationalSounds.begin() ; iter  != situationalSounds.end() ; ++iter)
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

void SoundManager::incrementSound(std::string id) {
	int value = 1;
	int containKey = soundsPlayed.count(id);
	if (containKey == 1) {
		value = soundsPlayed.at(id);
		soundsPlayed.erase(id);
		value++;
	}
	soundsPlayed.insert( { id, value });
}
