#pragma once
#include <Component.h>
#include <vector>

#include "ObjectPreset.h"

class BulletPool : public bew::Component
{
public:
    BulletPool(bew::GameObject* pParentObject, int amount, glm::vec3 posOfset = {0,0,0});

    void SetNextObjectActive();
    void SetNextObjectActive(glm::vec3 pos);

    std::vector<bew::GameObject*>* GetObjectList() { return &m_Objects; }
    
    BulletPool(const BulletPool& other) = delete;
    BulletPool(BulletPool&& other) = delete;
    BulletPool& operator=(const BulletPool& other) = delete;
    BulletPool& operator=(BulletPool&& other) = delete;
private:
    std::unique_ptr<ObjectPreset> m_BaseObject;
    std::vector<bew::GameObject*> m_Objects;

	int m_Currentobj{ 0 };
    int m_POOLSIZE;
    glm::vec3 m_PosOfset;

    void CreateObjects(int amout);
};

