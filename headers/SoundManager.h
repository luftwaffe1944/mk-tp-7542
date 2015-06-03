/*
 * SoundManager.h
 *
 *  Created on: 2/6/2015
 *      Author: uje
 */


#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "Constants.h"
#include "SDL_mixer.h"
#include <map>
#include <iostream>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager {
public:
	static SoundManager* Instance();
	virtual ~SoundManager() {
		delete(cm_pInstance);
		cm_pInstance = 0;
	}
	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void clean();

private:
	SoundManager();
	static SoundManager* cm_pInstance;
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
};

#endif /* SOUNDMANAGER_H_ */
