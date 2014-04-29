#pragma once

#include "common3d.h"
#include "sceneobject.h"

namespace Ngn3D
{

class Light
{
public:
	Light() : 
		m_Ambient(0.2f),
		m_Diffuse(0.5f),
		m_Specular(0.8f)
	{
	}

	Light(float4 ambient, float4 diffuse, float4 specular) : 
		m_Ambient(ambient),
		m_Diffuse(diffuse),
		m_Specular(specular)
	{
	}

	virtual void SetInProgram(CProgram& program, const glm::mat4& /*mView*/) const
	{
		int loc = glGetUniformLocation(program.GetProgram(), "g_DirLight.Ambient");
		glUniform4fv(loc, 1,  &m_Ambient[0]);

		loc = glGetUniformLocation(program.GetProgram(), "g_DirLight.Diffuse");
		glUniform4fv(loc, 1,  &m_Diffuse[0]);

		loc = glGetUniformLocation(program.GetProgram(), "g_DirLight.Specular");
		glUniform4fv(loc, 1,  &m_Specular[0]);
	}

	void	SetAmbient(float4 color)	{ m_Ambient = color; }
	float4	GetAmbient() const			{ return m_Ambient; }
	void	SetDiffuse(float4 color)	{ m_Diffuse = color; }
	float4	GetDiffuse() const			{ return m_Diffuse; }
	void	SetSpecular(float4 color)	{ m_Specular = color; }
	float4	GetSpecular() const			{ return m_Specular; }


protected:
	float4 m_Ambient;
	float4 m_Diffuse;
	float4 m_Specular;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight() :
		m_Direction(-1.0f, 0.0f, 0.0f)
	{
	}
	
	DirectionalLight(float3 dir) :
		m_Direction(dir)
	{
	}

	DirectionalLight(float4 ambient, float4 diffuse, float4 specular, float3 dir) :
		Light(ambient, diffuse, specular),
		m_Direction(dir)
	{
	}
	
	virtual void SetInProgram(CProgram& program, const glm::mat4& mView) const
	{
		int loc = glGetUniformLocation(program.GetProgram(), "g_DirLight.Direction");
		float4 mvDir = mView * float4(m_Direction, 0.0f);
		glUniform3fv(loc, 1,  &mvDir[0]);

		Light::SetInProgram(program, mView);
	}

	void SetDirection(float x, float y, float z)
	{
		m_Direction = float3(x, y, z);
	}

	const float3& GetDirection() const
	{
		return m_Direction;
	}

protected:
	float3 m_Direction;
};

//class PointLight : public Light, public AbstractSceneObject
//{
//public:
//	PointLight(float3 color, float3 pos = float3(0.0f)) :
//		Light(color)
//	{
//		if(pos != float3(0.0f))
//			Move(pos);
//	}
//};

}