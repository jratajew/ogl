#pragma once

#include "sceneobject.h"
#include "camera.h"
#include "light.h"

namespace Ngn3D
{

class Scene
{
	std::vector<shared_ptr<DrawableObject>> m_Drawables;
	Camera m_Camera;

	// Lights:
	//Light m_AmbientLight;
	DirectionalLight m_DirLight;

public:
	Scene() : m_Camera() 
	{
		m_Camera.LookAt(
        	glm::vec3(0.0f, 10.0f, 5.0f), // eye
        	glm::vec3(0.0f),				// look-at
        	glm::vec3(0.0f, 1.0f, 0.0f) );	// up

		//m_AmbientLight.SetColor(float3(0.3f, 0.3f, 0.3f));

		//m_DirLight.SetColor(float3(1.0f, 0.3f, 0.3f));
		//m_DirLight.
	}

	Camera& GetCamera() { return m_Camera; }

	void AddDrawable(shared_ptr<DrawableObject> obj)
	{
		m_Drawables.push_back(obj);
	}

	void Draw(CProgram& program)
	{
		//m_Camera.Move(float3(0.01f, 0, 0));
		//m_Camera.RotateY(0.0001f);

		glm::mat4 mView = m_Camera.GetTransformMatrix();
		glm::mat4 mProj = m_Camera.GetProjectionMatrix();
		
		// Compute and set Projection:
		const int locProjection		= glGetUniformLocation(program.GetProgram(), "g_ProjectionMatrix");
		const int locModelView		= glGetUniformLocation(program.GetProgram(), "g_ModelViewMatrix");

		glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(mProj));
		
		m_DirLight.SetInProgram(program, mView);

		for(auto drawable : m_Drawables)
		{
			drawable->RotateY(0.001f);
			drawable->RotateZ(0.0005f);

			CustomGeometry& geom = drawable->GetGeometry();
			
			// Compute and set ModelView:
			glm::mat4 mModelView = mView * drawable->GetTransformMatrix();
			glUniformMatrix4fv(locModelView, 1, GL_FALSE, glm::value_ptr(mModelView));

			geom.Draw(program);
		}
	}
};

}