#pragma once
#include <Component.h>
#include <vector>

#include "ObjectPreset.h"

class ObjectPoolingComponent : public bew::Component
{
public:
    ObjectPoolingComponent(bew::GameObject* pParentObject, std::unique_ptr<ObjectPreset> object, int amount, glm::vec3 posOfset = {0,0,0});

    void SetNextObjectActive();
    void SetNextObjectActive(glm::vec3 pos);

    std::vector<bew::GameObject*>* GetObjectList() { return &m_Objects; }
    
    ObjectPoolingComponent(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent(ObjectPoolingComponent&& other) = delete;
    ObjectPoolingComponent& operator=(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent& operator=(ObjectPoolingComponent&& other) = delete;
private:
    std::unique_ptr<ObjectPreset> m_BaseObject;
    std::vector<bew::GameObject*> m_Objects;

	int m_Currentobj{ 0 };
    int m_POOLSIZE;
    glm::vec3 m_PosOfset;

    void CreateObjects(int amout);
};

