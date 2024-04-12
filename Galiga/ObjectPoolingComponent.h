#pragma once
#include <Component.h>
#include <memory>
#include <vector>

class ObjectPoolingComponent : public bew::Component
{
public:
    ObjectPoolingComponent(bew::GameObject* pParentObject, bew::GameObject* object, int amount);

    ObjectPoolingComponent(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent(ObjectPoolingComponent&& other) = delete;
    ObjectPoolingComponent& operator=(const ObjectPoolingComponent& other) = delete;
    ObjectPoolingComponent& operator=(ObjectPoolingComponent&& other) = delete;
private:
    std::unique_ptr<bew::GameObject> m_BaseObject;
    std::vector<bew::GameObject*> m_Objects;
    int m_Currentobj{ 0 };
    int m_MaxCurrentObjects;

    void CreateObjects(int amout);
};

