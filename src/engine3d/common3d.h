#pragma once

#include "../common.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glext.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Face
{
	enum { NOT_SET = 0xffff };

	struct Vertex
	{
		ushort VertexId;
		ushort CoordId;
		ushort NormalId;

		Vertex() : VertexId(NOT_SET), CoordId(NOT_SET), NormalId(NOT_SET) {}
	};
	std::vector<Vertex> Vertices;
};
