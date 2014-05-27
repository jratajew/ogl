#pragma once

#include "common3d.h"

namespace Ngn3D
{
	
typedef glm::vec2 float2;
typedef glm::vec3 float3;
typedef glm::vec4 float4;

// Need non-aligned packing for this to work correctly for all types:
#pragma pack(push)
#pragma pack(1)

struct CustomVertex
{
    float3 Pos;
	float3 Normal;
	float2 TexCoord;

    CustomVertex() 
    {
    }

    CustomVertex( float3 pos, float3 normal, float2 texCoord )
        : Pos( pos ), Normal(normal), TexCoord(texCoord)
    {
    }

    static void* GetPositionOffset()
    {
        return static_cast<void*>( 0 );
    }
    static void* GetNormalOffset()
    {
        return reinterpret_cast<void*>( sizeof(float3) );
    }
    static void* GetTexCoordOffset()
    {
        return reinterpret_cast<void*>( sizeof(float3) + sizeof(float3) );
    }
};


// Leave it for later!
/*
template < class TPosType, int TPosDim, 
           class TNormType, int TNormDim, 
           class TCoordType, int TCoordDim >
struct SVertexNormTex
{
    static_assert(TPosDim <= 4, "SVertexNormTex maximum dimension is 4!");
    static_assert(TNormType <= 4, "SVertexNormTex maximum dimension is 4!");
    static_assert(TCoordType <= 4, "SVertexNormTex maximum dimension is 4!");

    enum { X = 0, Y = 1, Z = 2, W = 3 };

    TPosType    pos[TPosDim];
    TNormType   norm[TNormDim];
    TCoordType  texCoord[TCoordDim];
    
    static void GetPositionId()     { return 0; }
    static void GetNormId()         { return 1; }
    static void GetTexCoordId()     { return 2; }


    static void GetPositionType()
    {
        if( TPosType

    static void* GetPositionOffset()
    {
        return static_cast<void*>( 0 );
    }
    static void* GetNormalOffset()
    {
        return static_cast<void*>( sizeof(pos) );
    }
    static void* GetTexCoordOffset()
    {
        return static_cast<void*>( sizeof(pos) + sizeof(norm) );
    }
};

// Standard vertices:
typedef SVertexNormTex<GLfloat, 2, GLfloat, 3, GLfloat, 2> SVertex2D;
typedef SVertexNormTex<GLfloat, 3, GLfloat, 3, GLfloat, 2> SVertex3D;
*/
#pragma pack(pop)

template <class TGLType> struct GLType {};
template <> struct GLType<GLbyte> {
    static const GLenum type = GL_SHORT;
};
template <> struct GLType<GLubyte> {
    static const GLenum type = GL_UNSIGNED_SHORT;
};
template <> struct GLType<GLshort> {
    static const GLenum type = GL_SHORT;
};
template <> struct GLType<GLushort> {
    static const GLenum type = GL_UNSIGNED_SHORT;
};
template <> struct GLType<GLint> {
    static const GLenum type = GL_INT;
};
template <> struct GLType<GLuint> {
    static const GLenum type = GL_UNSIGNED_INT;
};
template <> struct GLType<GLfloat> {
    static const GLenum type = GL_FLOAT;
};

} // namespace Ngn3D