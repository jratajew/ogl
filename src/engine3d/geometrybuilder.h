#pragma once

#include "geometry.h"
#include "types.h"

namespace Ngn3D
{

class CGeometryBuiler
{
public:
    static void BuildTriangle( CGeometry<SColorVertex>& triangle )
    {
        // Vertices:
        triangle << SColorVertex( float3( 0.0f, 0.0f, 0.0f ), float4( 1.0f, 0.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( 1.0f, 0.0f, 0.0f ), float4( 1.0f, 1.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( 0.0f, 1.0f, 0.0f ), float4( 0.0f, 0.0f, 1.0f, 1.0f ) ); 
        // Indices:
        triangle << 0 << 1 << 2;

        triangle.SetPrimitiveMode( GL_TRIANGLES );
    }
};

} //namespace Ngn3D

