#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
    class FpsComponent final :
        public Component
    {
    public:
        //I feel like this is not the best way even tho the book said this was one of the options
        FpsComponent(Transform&, TextComponent* textComponent);
        virtual ~FpsComponent();

        void Update(float deltaTime) override;
        void Render() const override {};

    private:
        float m_fps;

        TextComponent* textComponent;
    };
}


