#pragma once
#include "Component.h"

class PoolComponent final : public bew::Component
{
public:
	PoolComponent(bew::GameObject* pParentObject) : Component{pParentObject}{}

    bool InUse() { return m_InUse; }
    void SetInUse(bool used) { m_InUse = used; }

    virtual ~PoolComponent() = default;
    PoolComponent(const PoolComponent& other) = delete;
    PoolComponent(PoolComponent&& other) = delete;
    PoolComponent& operator=(const PoolComponent& other) = delete;
    PoolComponent& operator=(PoolComponent&& other) = delete;
private:
    bool m_InUse;
};

