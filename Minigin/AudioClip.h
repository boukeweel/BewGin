#pragma once
#include <memory>
#include <SDL_mixer.h>

namespace bew {
    /**
     * Simple RAII wrapper for an SDL_mixer audio chunk
     */
    class AudioClip final {
    public:
        Mix_Chunk* GetMixChunk() const;
        explicit AudioClip(std::unique_ptr<Mix_Chunk> chunk);
        ~AudioClip();

        void Play(int volume);

        AudioClip(const AudioClip&) = delete;
        AudioClip(AudioClip&&) = delete;
        AudioClip& operator=(const AudioClip&) = delete;
        AudioClip& operator=(const AudioClip&&) = delete;

    private:
        std::unique_ptr<Mix_Chunk> m_chunk;
    };
}


