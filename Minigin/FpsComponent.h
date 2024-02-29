#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
    class FpsComponent final :
        public Component
    {
    public:
        FpsComponent(GameObject* pParentObject);
        ~FpsComponent() override;

        void Update(float deltaTime) override;
        void Render() const override {}

        FpsComponent(const FpsComponent& other) = delete;
        FpsComponent(FpsComponent&& other) = delete;
        FpsComponent& operator=(const FpsComponent& other);
        FpsComponent& operator=(FpsComponent&& other) = delete;
    private:
        float m_fps;
        float m_frameCount;
        float m_accumulatedTime;
        float m_updateInterval;


        TextComponent* textComponent;
    };
}


