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
		if(s_pInstance == 0) {
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
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
	//static SoundManager* cm_pInstance;
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
	//Esta estructura tiene los sonidos pertenecientes a cada acción.
	//Toma los archivos de la carpeta sound/sfx con extension .ogg
	std::map<std::string, std::vector<std::string> >  situationalSounds =
		{
			{"punchHit",
				{
					"punch1",
					"punch2",
					"punch3",
					"punch4"
				}
			},
			{"missPunch",
				{
					"missPunch1",
					"missPunch2"
				}
			},
			{"uppercut",
				{
					"gancho"
				}
			},
			{"missKick",
					{
							"highKick1",
							"highKick2"
					}
			},
			{"fire",
					{
							"fire1",
							//"fire2"
					}

			},
			{"fireHit",
					{
							"fireHit1",
							"fireHit3"
					}
			},
			{"jump",
					{
							"jump1",
							"jump2"
					}
			},
			{"toasty",
					{
							"toasty"
					}
			},
			{"scorpionWins",
					{
							"scorpionWins"
					}
			},
			{"subzeroWins",
					{
							"subzeroWins"
					}
			},
			{"fatality",
					{
							"fatality"
					}
			},
			{"applause",
					{
							"applause"
					}
			},
			{"fatalityDeath",
					{
							"fatalityDeath"
					}
			},
			{"gong",
					{
							"gong"
					}
			},
			{"fight",
					{
							"fight"
					}
			},
			{"roundOne",
					{
							"roundOne"
					}
			},
			{"roundTwo",
					{
							"roundTwo"
					}
			},
			{"roundThree",
					{
							"roundThree"
					}
			},
			{"finishHim",
					{
							"finishHim"
					}
			},
			{"scream",
					{
							"scream"
					}
			},
			{"gong",
					{
							"gong"
					}
			},
			{"fight",
					{
							"fight"
					}
			},
			{"friendship",
					{
							"friendship"
					}
			},
			{"pre_fatality",
					{
							"pre_fatality"
					}
			},
			{"pre_friendship",
					{
							"pre_friendship"
					}
			},
			{"pre_babality",
					{
							"pre_babality"
					}
				},
			{"baby_cry",
					{
							"baby_cry"
					}
			},
			{"babality_voice",
					{
							"babality_voice"
					}
			},
			{"headless_blood",
			{
					"headless_blood"
			}
			}
		};
	};

#endif /* SOUNDMANAGER_H_ */

