#pragma once

#include "types.h"
#include "geometry.h"

namespace Ngn3D
{

class CGeometryBuiler
{
public:
    static void BuildFormObj( const std::string& path, CGeometry<CustomVertex>& object );
    static void BuildTerrainQuad( CustomGeometry& terrain, float width, float length );

	//static void BuildTriangle( CGeometry<CustomVertex>& triangle )
 //   {
 //       // Vertices:
 //       triangle << CustomVertex( float3( 0.0f, 0.0f, 0.0f ), float4( 1.0f, 0.0f, 0.0f, 1.0f ) )
 //                << CustomVertex( float3( 1.0f, 0.0f, 0.0f ), float4( 1.0f, 1.0f, 0.0f, 1.0f ) )
 //                << CustomVertex( float3( 0.0f, 1.0f, 0.0f ), float4( 0.0f, 0.0f, 1.0f, 1.0f ) );
 //       // Indices:
 //       triangle << 0 << 1 << 2;
 //       triangle << 0 << 2 << 1;

 //       triangle.SetPrimitiveMode( GL_TRIANGLES );
 //   }

 //   static void BuildPyramid( CGeometry<CustomVertex>& pyramid )
 //   {
 //       // Vertices:
 //   	pyramid << CustomVertex( float3( 0.0f, 5.0f, 0.0f ), float4( 1.0f, 0.0f, 0.0f, 1.0f ) )
 //                << CustomVertex( float3( 1.0f, 0.0f, 1.0f ), float4( 0.0f, 1.0f, 0.0f, 1.0f ) )
 //                << CustomVertex( float3( 1.0f, 0.0f, -1.0f ), float4( 0.0f, 0.0f, 1.0f, 1.0f ) )
 //                << CustomVertex( float3( -1.0f, 0.0f, -1.0f ), float4( 1.0f, 1.0f, 0.0f, 1.0f ) )
 //                << CustomVertex( float3( -1.0f, 0.0f, 1.0f ), float4( 1.0f, 0.0f, 1.0f, 1.0f ) );
 //       // Indices:
 //   	pyramid << 0 << 1 << 2;
 //   	pyramid << 0 << 2 << 3;
 //   	pyramid << 0 << 3 << 4;
 //   	pyramid << 0 << 4 << 1;
 //   	pyramid << 2 << 1 << 3;
 //   	pyramid << 2 << 3 << 4;

 //   	pyramid.SetPrimitiveMode( GL_TRIANGLES );
 //   }
};

} //namespace Ngn3D

