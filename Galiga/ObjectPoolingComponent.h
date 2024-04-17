#pragma once
#include <Component.h>
#include <vector>

#include "ObjectPreset.h"

class ObjectPoolingComponent : public bew::Component
{
public:
    ObjectPoolingComponent(bew::GameObject* pParentObject, std::unique_ptr<ObjectPreset> object, int amount);

    void SetNextObjectActive();
    void SetNextObjectActive(glm::vec3 pos);
    
    ObjectPoolingComponent(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent(ObjectPoolingComponent&& other) = delete;
    ObjectPoolingComponent& operator=(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent& operator=(ObjectPoolingComponent&& other) = delete;
private:
    std::unique_ptr<ObjectPreset> m_BaseObject;
    std::vector<bew::GameObject*> m_Objects;

    int m_Currentobj{ 0 };
    int m_POOLSIZE;

    void CreateObjects(int amout);
};

