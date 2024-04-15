#pragma once
#include <Component.h>
#include <vector>

#include "ObjectPreset.h"

class ObjectPoolingComponent : public bew::Component
{
public:
    ObjectPoolingComponent(bew::GameObject* pParentObject, ObjectPreset* object, int amount);

    ObjectPoolingComponent(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent(ObjectPoolingComponent&& other) = delete;
    ObjectPoolingComponent& operator=(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent& operator=(ObjectPoolingComponent&& other) = delete;
private:
    ObjectPreset* m_BaseObject;
    std::vector<bew::GameObject*> m_Objects;

    int m_Currentobj{ 0 };
    int m_MaxCurrentObjects;

    void CreateObjects(int amout);
};

