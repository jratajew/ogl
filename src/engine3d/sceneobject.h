#pragma once

#include "common3d.h"

namespace Ngn3D
{

class AbstractSceneObject
{
	float3 m_Position;
	float3 m_Rotation;
};


class DrawableObject : public AbstractSceneObject
{
	const CGeometry<SColorVertex>* m_pGeometry;
};

}