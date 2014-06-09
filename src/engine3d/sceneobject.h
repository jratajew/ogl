#pragma once

#include "common3d.h"

#include "geometry.h"
#include "types.h"

namespace Ngn3D
{

typedef CGeometry<CustomVertex> CustomGeometry;

class Camera;
class Light;
class SceneObserver;

class SceneObject
{
public:
    struct SAttributes
    {
        shared_ptr<CustomGeometry>  Geometry;
        shared_ptr<Camera>          Camera;
        shared_ptr<Light>           Light;

    } Attributes;

	SceneObject();

    // Cannot copy or assign:
    SceneObject(const SceneObject&) = delete;
    SceneObject& operator=(const SceneObject&) = delete;

    void RegisterObserver(SceneObserver* observer);
    void UnregisterObserver(SceneObserver* observer);
    void NotifyObservers() const;
	
	const glm::mat4& GetTransformMatrix() const 
    { 
        return m_TransformMatrix; 
    }

	virtual void Move(const float3& dPos);	
	virtual void RotateX(const float angle);	
	virtual void RotateY(const float angle);
	virtual void RotateZ(const float angle);

    void SetVelocity( const float3& v )
    {
        m_Velocity = v;
    }

    void AddVelocity(const float3& v)
    {
        m_Velocity += v;
    }

    float3 GetVelocity() const
    {
        return m_Velocity;
    }

    void Update(float dt)
    {
        Move(m_Velocity * dt * 5.0f);
    }

protected:
	glm::mat4 m_TransformMatrix;
    float3 m_Velocity;
    
private:
    std::list<SceneObserver*> m_Observers;
};

class SceneObserver
{
public:
    virtual bool Notify(SceneObject& subject) = 0;
};


class DrawableObject : public SceneObject
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