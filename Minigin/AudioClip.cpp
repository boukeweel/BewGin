#include "AudioClip.h"

#include <iostream>

namespace bew {
    AudioClip::AudioClip(Mix_Chunk* chunk) : m_chunk(chunk) {}

    AudioClip::~AudioClip()
	{
        Mix_FreeChunk(m_chunk);
    }

    void AudioClip::Play()
    {
        Mix_VolumeChunk(m_chunk, m_Volume);
        Mix_PlayChannel(-1, m_chunk, 0);
    }

    Mix_Chunk* AudioClip::GetMixChunk() const {
        return m_chunk;
    }
}
