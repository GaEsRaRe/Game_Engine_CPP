#pragma once
#include <SDL/SDL_mixer.h>
#include <string>
#include <map>

class SoundEffect {
	public :
		friend class AudioEngine;
		void play(int loops = 1);
		Mix_Chunk* _chunk = nullptr;
};

class Music {
public:
	friend class AudioEngine;
	void play(int loops = 1);
	static void pause();
	static void stop();
	static void resume();
private:
	Mix_Music* _music = nullptr;
};

class AudioEngine {
	public:
		AudioEngine();
		~AudioEngine();
		void init();
		void destroy();
		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);
	private:
		std::map<std::string, Mix_Chunk*> _effectMap;
		std::map<std::string, Mix_Music*> _musicMap;
		bool _isInitialized = false;
};

