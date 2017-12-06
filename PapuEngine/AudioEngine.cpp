#include "AudioEngine.h"
#include "Error.h"

void SoundEffect::play(int loops) {
	if (Mix_PlayChannel(-1, _chunk, loops) == -1) {
		if (Mix_PlayChannel(0, _chunk, loops) == -1) {
			fatalError("Mix_PlayChannel error :" 
						+ std::string(Mix_GetError()));
		}
	}
}

void Music::play(int loops) {
	Mix_PlayMusic(_music, loops);
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::stop() {
	Mix_HaltMusic();
}

void Music::resume() {
	Mix_ResumeMusic();
}

AudioEngine::AudioEngine()
{
}


AudioEngine::~AudioEngine()
{
	destroy();
}

void AudioEngine::init() {
	if (_isInitialized) {
		fatalError("AudioEngine ya inicializado");
	}
	//validamos si se puede cargar mp3 u ogg
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
		fatalError("Mix Error :" + std::string(Mix_GetError()));
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		fatalError("Mix Error: " + std::string(Mix_GetError()));
	}

	_isInitialized = true;

}

void AudioEngine::destroy() {
	if (_isInitialized) {
		_isInitialized = false;
		for (auto& it: _effectMap) {
			Mix_FreeChunk(it.second);
		}
		for (auto& it : _musicMap) {
			Mix_FreeMusic(it.second);
		}
		_effectMap.clear();
		_musicMap.clear();
		Mix_CloseAudio();
		Mix_Quit();
	}
}

SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
	auto it = _effectMap.find(filePath);
	SoundEffect effect;
	if (it == _effectMap.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
		if (chunk == nullptr) {
			fatalError("MixLoadWav error: " + std::string(Mix_GetError()));
		}
		effect._chunk = chunk;
		_effectMap[filePath] = chunk;
	}
	else {
		effect._chunk = it->second;
	}
	return effect;
}

Music AudioEngine::loadMusic(const std::string& filePath) {
	auto it = _musicMap.find(filePath);
	Music music;
	if (it == _musicMap.end()) {
		Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
		if (mixMusic == nullptr) {
			fatalError("Mix_LoadMUS error: "+std::string(Mix_GetError()));
		}

		music._music = mixMusic;
		_musicMap[filePath] = mixMusic;
	}
	else {
		music._music = it->second;
	}
	return music;
}