#include "sceneobject.h"

namespace Ngn3D
{

SceneObject::SceneObject() 
    : m_TransformMatrix(1.0f),
      m_Velocity(0.0f)
{
    memset(&Attributes, 0, sizeof(Attributes));
}

void SceneObject::RegisterObserver(SceneObserver* observer)
{
    m_Observers.push_back(observer);
}

void SceneObject::UnregisterObserver(SceneObserver* observer)
{
    m_Observers.remove(observer);
}

void SceneObject::NotifyObservers() const
{
//     for(auto it : m_Observers)
//     {
//         (*it)->Notify();
//     }
}

void SceneObject::Move(const float3& dPos)
{
    m_TransformMatrix = glm::translate(m_TransformMatrix, dPos);
}

void SceneObject::RotateX(const float angle)
{
    m_TransformMatrix = glm::rotate(m_TransformMatrix, angle, float3(1.0f, 0.0f, 0.0f));
}

void SceneObject::RotateY(const float angle)
{
    m_TransformMatrix = glm::rotate(m_TransformMatrix, angle, float3(0.0f, 1.0f, 0.0f));
}

void SceneObject::RotateZ(const float angle)
{
    m_TransformMatrix = glm::rotate(m_TransformMatrix, angle, float3(0.0f, 0.0f, 1.0f));
}

}