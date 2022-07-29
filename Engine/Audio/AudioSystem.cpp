#include "AudioSystem.h"
#include <fmod.hpp>

namespace JREngine {

	void AudioSystem::Initialize(){
		FMOD::System_Create(&m_fmodSystem);

		void* extraDriverData = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);
	}

	void AudioSystem::Shutdown(){
		// !! use range based for-loop to iterate through m_sounds, call release on each element 
		 // !! call clear() on m_sounds to remove all elements 
		// !! call close() on the fmod system 
		// !! call release() on the fmod system 
		for (auto sounds : m_sounds) {
			sounds.second->release();
		}
		m_sounds.clear();
		m_fmodSystem->close();
		m_fmodSystem->release();
	}

	void AudioSystem::Update(){
		m_fmodSystem->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename){
		auto soundFind = m_sounds.find(name);
		if (soundFind == m_sounds.end()) {
			FMOD::Sound* sound = nullptr;
			m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			m_sounds[name] = sound;
		}
	}

	void AudioSystem::PlayAudio(const std::string& name, bool loop){
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end()) {
			FMOD::Sound* sound = iter->second;
			if (loop) {
				sound->setMode(FMOD_LOOP_NORMAL);
			} else {
				sound->setMode(FMOD_LOOP_OFF);
			}

			FMOD::Channel* channel;
			m_fmodSystem->playSound(sound, 0, false, &channel);
		}
	}
}