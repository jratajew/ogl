#pragma once

#include "sceneobject.h"
#include "camera.h"
#include "light.h"

namespace Ngn3D
{

class Scene : public InputListener
{
	std::vector<shared_ptr<SceneObject>>    m_Objects;
	shared_ptr<Camera>                      m_Camera;
    shared_ptr<SceneObject>                 m_Terrain;

	// Lights:
	//Light m_AmbientLight;
	DirectionalLight m_DirLight;

public:
	Scene();

    virtual void KeyDownImpl(unsigned char key);
    virtual void SpecialKeyDownImpl(int key);
    virtual void KeyUpImpl(unsigned char key);
    virtual void SpecialKeyUpImpl(int key);
    virtual void MouseButtonDownImpl(MouseButton b);
    virtual void MouseButtonUpImpl(MouseButton b);
    virtual void MouseMoved();

	Camera& GetCamera() { return *m_Camera; }

	void Add(shared_ptr<SceneObject> obj)
	{
		m_Objects.push_back(obj);
	}
    
    void Update(float dt)
    {
        for(auto obj : m_Objects)
        {
            obj->Update(dt);
        }
    }

	void Draw(CProgram& program)
	{
		//m_Camera.Move(float3(0.01f, 0, 0));
		//m_Camera.RotateY(0.0001f);

		glm::mat4 mView = m_Camera->GetTransformMatrix();
		glm::mat4 mProj = m_Camera->GetProjectionMatrix();
		
		// Compute and set Projection:
		const int locProjection		= glGetUniformLocation(program.GetProgram(), "g_ProjectionMatrix");
		const int locModelView		= glGetUniformLocation(program.GetProgram(), "g_ModelViewMatrix");

		glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(mProj));
		
		m_DirLight.SetInProgram(program, mView);

		for(auto obj : m_Objects)
		{
            if(obj->Attributes.Geometry)
            {
                // Compute and set ModelView:
                glm::mat4 mModelView = mView * obj->GetTransformMatrix();
                glUniformMatrix4fv(locModelView, 1, GL_FALSE, glm::value_ptr(mModelView));

                obj->Attributes.Geometry->Draw(program);
            }
		}
	}
};

}