#include "AudioClip.h"

namespace bew {
    AudioClip::AudioClip(std::unique_ptr<Mix_Chunk> chunk) : m_chunk(std::move(chunk)) {}

    AudioClip::~AudioClip() {
        Mix_FreeChunk(m_chunk.get());
    }

    Mix_Chunk* AudioClip::GetMixChunk() const {
        return m_chunk.get();
    }
}