#pragma once

#include "common3d.h"

namespace Ngn3D
{

typedef CGeometry<CustomVertex> CustomGeometry;

class AbstractSceneObject
{
public:
	AbstractSceneObject() : m_TransformMatrix(1.0f) {}
	
	const glm::mat4& GetTransformMatrix() const { return m_TransformMatrix; }

	virtual void Move(const float3& dPos)
	{
		m_TransformMatrix = glm::translate(m_TransformMatrix, dPos);
	}
	
	virtual void RotateX(const float angle)
	{
		m_TransformMatrix = glm::rotate(m_TransformMatrix, angle, float3(1.0f, 0.0f, 0.0f));
	}
	
	virtual void RotateY(const float angle)
	{
		m_TransformMatrix = glm::rotate(m_TransformMatrix, angle, float3(0.0f, 1.0f, 0.0f));
	}

	virtual void RotateZ(const float angle)
	{
		m_TransformMatrix = glm::rotate(m_TransformMatrix, angle, float3(0.0f, 0.0f, 1.0f));
	}

protected:
	glm::mat4 m_TransformMatrix;
};


class DrawableObject : public AbstractSceneObject
{
public:
	DrawableObject(shared_ptr<CustomGeometry> geometry)
		: m_pGeometry(geometry)
	{
	}

	CustomGeometry& GetGeometry() { return *m_pGeometry; }

	//void Draw();

protected:

	const shared_ptr<CustomGeometry> m_pGeometry;

private:
	DrawableObject(const DrawableObject&);
	DrawableObject& operator=(const DrawableObject&);
};

}