#include "AudioClip.h"

#include <iostream>

namespace bew {
    AudioClip::AudioClip(Mix_Chunk* chunk) : m_pChunk(chunk) {}

    AudioClip::~AudioClip()
	{
        Mix_FreeChunk(m_pChunk);
    }

    void AudioClip::Play()
    {
        Mix_VolumeChunk(m_pChunk, m_Volume);
        Mix_PlayChannel(-1, m_pChunk, 0);
    }

    Mix_Chunk* AudioClip::GetMixChunk() const {
        return m_pChunk;
    }
}
