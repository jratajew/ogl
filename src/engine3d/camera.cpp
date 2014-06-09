#include "camera.h"


namespace Ngn3D
{


Camera::Camera() 
    : m_ProjectionMatrix(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f))
{

}

void Camera::Move(const float3& dPos)
{
    auto mTranslate = glm::translate(glm::mat4(), -dPos);
    m_TransformMatrix = mTranslate * m_TransformMatrix;
}

void Camera::RotateX(const float angle)
{
    auto mRotate = glm::rotate(glm::mat4(), angle, float3(1.0f, 0.0f, 0.0f));
    m_TransformMatrix = mRotate * m_TransformMatrix;
}

void Camera::RotateY(const float angle)
{
    auto mRotate = glm::rotate(glm::mat4(), angle, float3(0.0f, 1.0f, 0.0f));
    m_TransformMatrix = mRotate * m_TransformMatrix;
}

void Camera::RotateZ(const float angle)
{
    auto mRotate = glm::rotate(glm::mat4(), angle, float3(0.0f, 1.0f, 0.0f));
    m_TransformMatrix = mRotate * m_TransformMatrix;
}

}