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
#include <vector>
#include <iostream>


enum sound_type {
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager {
public:
	static SoundManager* Instance() {
		if(s_pInstance == NULL)
			s_pInstance = new SoundManager();
		return s_pInstance;
	}
	/*virtual ~SoundManager() {
		delete(cm_pInstance);
		cm_pInstance = 0;
	}*/
	std::map<std::string, int >  soundsPlayed;
	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playSoundOnce(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void clean();
	void loadBattleSounds();
	void playSoundByAction(std::string action, int loop = 0);
	int hitSoundCounter1 = 0;
	int hitSoundCounter2 = 0;
	void init();
	void incrementSound(std::string id);

private:
	static SoundManager* s_pInstance;
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager&);
	SoundManager &operator=(const SoundManager&);
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
	//Esta estructura tiene los sonidos pertenecientes a cada acción.
	//Toma los archivos de la carpeta sound/sfx con extension .ogg
	std::map<std::string, std::vector<std::string> >  situationalSounds;
	bool createSituationalSoundsMap(std::map<std::string, std::vector<std::string> >  &situationalSounds) {

		situationalSounds["punchHit"].push_back("punch1");
		situationalSounds["punchHit"].push_back("punch2");
		situationalSounds["punchHit"].push_back("punch3");
		situationalSounds["punchHit"].push_back("punch4");

		situationalSounds["missPunch"].push_back("missPunch1");
		situationalSounds["missPunch"].push_back("missPunch2");
		situationalSounds["uppercut"].push_back("gancho");
		situationalSounds["missKick"].push_back("highKick1");
		situationalSounds["missKick"].push_back("highKick2");
		situationalSounds["fire"].push_back("fire1");
		situationalSounds["fireHit"].push_back("fireHit1");
		situationalSounds["fireHit"].push_back("fireHit3");
		situationalSounds["jump"].push_back("jump1");
		situationalSounds["jump"].push_back("jump2");
		situationalSounds["toasty"].push_back("toasty");
		situationalSounds["scorpionWins"].push_back("scorpionWins");
		situationalSounds["subzeroWins"].push_back("subzeroWins");
		situationalSounds["fatality"].push_back("fatality");
		situationalSounds["applause"].push_back("applause");
		situationalSounds["fatality_voice"].push_back("fatality_voice");
		situationalSounds["gong"].push_back("gong");
		situationalSounds["fight"].push_back("fight");
		situationalSounds["roundOne"].push_back("roundOne");
		situationalSounds["roundTwo"].push_back("roundTwo");
		situationalSounds["roundThree"].push_back("roundThree");
		situationalSounds["scream"].push_back("scream");
		situationalSounds["friendship"].push_back("friendship");
		situationalSounds["finishHim"].push_back("finishHim");
		situationalSounds["friendship_voice"].push_back("friendship_voice");
		situationalSounds["pre_fatality"].push_back("pre_fatality");
		situationalSounds["pre_friendship"].push_back("pre_friendship");
		situationalSounds["pre_babality"].push_back("pre_babality");
		situationalSounds["baby_cry"].push_back("baby_cry");
		situationalSounds["babality_voice"].push_back("babality_voice");
		situationalSounds["post_babality"].push_back("post_babality");
		situationalSounds["headless_blood"].push_back("headless_blood");
		return true;
	}
};

#endif /* SOUNDMANAGER_H_ */

