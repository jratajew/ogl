#include "scene.h"

// TODO: remove later
#include "geometrybuilder.h"

namespace Ngn3D
{


Scene::Scene() : m_Camera()
{
    m_Camera = shared_ptr<Camera>(new Camera());
    m_Camera->LookAt(
        glm::vec3(0.0f, 10.0f, 5.0f), // eye
        glm::vec3(0.0f),				// look-at
        glm::vec3(0.0f, 1.0f, 0.0f));	// up

    // TODO: Doesn't seem right...
    m_Terrain = shared_ptr<SceneObject>(new SceneObject());
    m_Terrain->Attributes.Geometry = shared_ptr<CustomGeometry>(new CustomGeometry());
    CGeometryBuiler::BuildTerrainQuad(*m_Terrain->Attributes.Geometry, 10.0f, 10.0f);
    m_Terrain->Attributes.Geometry->CreateBuffers();

    m_Objects.push_back(m_Camera);
    m_Objects.push_back(m_Terrain);

    //m_AmbientLight.SetColor(float3(0.3f, 0.3f, 0.3f));

    //m_DirLight.SetColor(float3(1.0f, 0.3f, 0.3f));
    //m_DirLight.
}

void Scene::KeyDownImpl(unsigned char key)
{
    switch(key)
    {
    case 'w':
        m_Camera->AddVelocity(float3(0.0f, 0.0f, -1.0f));
        break;
    case 's':
        m_Camera->AddVelocity(float3(0.0f, 0.0f, 1.0f));
        break;
    case 'a':
        m_Camera->AddVelocity(float3(-1.0f, 0.0f, 0.0f));
        break;
    case 'd':
        m_Camera->AddVelocity(float3(1.0f, 0.0f, 0.0f));
        break;
    default:
        break;
    }
}

void Scene::SpecialKeyDownImpl(int key)
{
}

void Scene::KeyUpImpl(unsigned char key)
{
    switch(key)
    {
    case 'w':
        m_Camera->AddVelocity(-float3(0.0f, 0.0f, -1.0f));
        break;
    case 's':
        m_Camera->AddVelocity(-float3(0.0f, 0.0f, 1.0f));
        break;
    case 'a':
        m_Camera->AddVelocity(-float3(-1.0f, 0.0f, 0.0f));
        break;
    case 'd':
        m_Camera->AddVelocity(-float3(1.0f, 0.0f, 0.0f));
        break;
    default:
        break;
    }
}

void Scene::SpecialKeyUpImpl(int key)
{
}

void Scene::MouseMoved()
{
    static const float cMouseSpeed = 0.002f;

    int dX = MouseX_delta();
    int dY = MouseY_delta();

    if(MouseButtonState(MOUSE_BUTTON_LEFT))
    {
        m_Camera->RotateY(cMouseSpeed * dX);
        m_Camera->RotateX(cMouseSpeed * dY);
    }
}

void Scene::MouseButtonDownImpl(MouseButton b)
{

}

void Scene::MouseButtonUpImpl(MouseButton b)
{

}

}