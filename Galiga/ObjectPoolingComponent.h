#pragma once
#include <Component.h>
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
    std::vector<bew::GameObject*> objects;
};

