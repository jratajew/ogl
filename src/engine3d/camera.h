#pragma once

#include "common3d.h"
#include "sceneobject.h"

namespace Ngn3D
{

class Camera : public SceneObject
{
public:
	Camera();

	//Camera(float3 position, float3 lookAt)
	//	: AbstractSceneObject(position), m_LookAt(lookAt)
	//{
	//}

	inline void LookAt(float3 eye, float3 lookat, float3 up)
	{
		m_TransformMatrix = glm::lookAt(eye, lookat, up);
	}

	inline const glm::mat4& GetProjectionMatrix() const 
    { 
        return m_ProjectionMatrix; 
    }
	
	virtual void Move(const float3& dPos);	
	virtual void RotateX(const float angle);	
	virtual void RotateY(const float angle);
	virtual void RotateZ(const float angle);

protected:
	glm::mat4 m_ProjectionMatrix;
};

}