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
	static SoundManager* Instance();
	virtual ~SoundManager() {
		delete(cm_pInstance);
		cm_pInstance = 0;
	}
	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void clean();
	void loadBattleSounds();
	void playSoundByAction(std::string action, int loop = 0);
	int hitSoundCounter1 = 0;
	int hitSoundCounter2 = 0;
	void init();

private:
	SoundManager();
	static SoundManager* cm_pInstance;
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
		}
	};
};

#endif /* SOUNDMANAGER_H_ */

