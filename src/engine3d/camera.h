#pragma once

#include "common3d.h"
#include "sceneobject.h"

namespace Ngn3D
{

class Camera : public AbstractSceneObject
{
public:
	Camera()
		: m_ProjectionMatrix(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f))
	{
	}

	//Camera(float3 position, float3 lookAt)
	//	: AbstractSceneObject(position), m_LookAt(lookAt)
	//{
	//}

	void LookAt(float3 eye, float3 lookat, float3 up)
	{
		m_TransformMatrix = glm::lookAt(eye, lookat, up);
	}

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	
	virtual void Move(const float3& dPos)
	{
		m_TransformMatrix = glm::translate(m_TransformMatrix, -dPos);
	}
	
	virtual void RotateX(const float angle)
	{
		auto mRotate = glm::rotate(glm::mat4(), angle, float3(1.0f, 0.0f, 0.0f));
		m_TransformMatrix = mRotate * m_TransformMatrix;
	}
	
	virtual void RotateY(const float angle)
	{
		auto mRotate = glm::rotate(glm::mat4(), angle, float3(0.0f, 1.0f, 0.0f));
		m_TransformMatrix = mRotate * m_TransformMatrix;
	}

	virtual void RotateZ(const float angle)
	{
		auto mRotate = glm::rotate(glm::mat4(), angle, float3(0.0f, 1.0f, 0.0f));
		m_TransformMatrix = mRotate * m_TransformMatrix;
	}

protected:
	glm::mat4 m_ProjectionMatrix;
};

}