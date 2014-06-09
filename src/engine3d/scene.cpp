#include "scene.h"


namespace Ngn3D
{


Scene::Scene() : m_Camera()
{
    m_Camera.LookAt(
        glm::vec3(0.0f, 10.0f, 5.0f), // eye
        glm::vec3(0.0f),				// look-at
        glm::vec3(0.0f, 1.0f, 0.0f));	// up

    memset(m_KeyState, 0, sizeof(m_KeyState));

    //m_AmbientLight.SetColor(float3(0.3f, 0.3f, 0.3f));

    //m_DirLight.SetColor(float3(1.0f, 0.3f, 0.3f));
    //m_DirLight.
}

void Scene::KeyDown(unsigned char key, int x, int y)
{
    if(!m_KeyState[key])
    {
        switch(key)
        {
        case 'w':
            m_Camera.AddVelocity(float3(0.0f, 0.0f, -1.0f));
            break;
        case 's':
            m_Camera.AddVelocity(float3(0.0f, 0.0f, 1.0f));
            break;
        case 'a':
            m_Camera.AddVelocity(float3(-1.0f, 0.0f, 0.0f));
            break;
        case 'd':
            m_Camera.AddVelocity(float3(1.0f, 0.0f, 0.0f));
            break;
        default:
            break;
        }
    }

    m_KeyState[key] = true;
}

void Scene::SpecialKeyDown(int key, int x, int y)
{
}

void Scene::KeyUp(unsigned char key, int x, int y)
{
    if(m_KeyState[key])
    {
        switch(key)
        {
        case 'w':
            m_Camera.AddVelocity(-float3(0.0f, 0.0f, -1.0f));
            break;
        case 's':
            m_Camera.AddVelocity(-float3(0.0f, 0.0f, 1.0f));
            break;
        case 'a':
            m_Camera.AddVelocity(-float3(-1.0f, 0.0f, 0.0f));
            break;
        case 'd':
            m_Camera.AddVelocity(-float3(1.0f, 0.0f, 0.0f));
            break;
        default:
            break;
        }
    }

    m_KeyState[key] = false;
}

void Scene::SpecialKeyUp(int key, int x, int y)
{
}

}