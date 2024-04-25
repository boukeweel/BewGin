#include "AudioClip.h"

namespace bew {
    AudioClip::AudioClip(std::unique_ptr<Mix_Chunk> chunk) : m_chunk(std::move(chunk)) {}

    AudioClip::~AudioClip() {
        Mix_FreeChunk(m_chunk.get());
    }

    void AudioClip::Play(int volume)
    {
        Mix_VolumeChunk(m_chunk.get(), volume);
        Mix_PlayChannel(-1, m_chunk.get(), 0);
    }

    Mix_Chunk* AudioClip::GetMixChunk() const {
        return m_chunk.get();
    }
}