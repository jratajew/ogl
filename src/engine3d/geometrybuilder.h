#pragma once

#include "geometry.h"
#include "types.h"

#include <fstream>
#include <regex>

namespace Ngn3D
{

class CGeometryBuiler
{
public:
    static void BuildFormObj( const std::string& path, CGeometry<SColorVertex>& object )
    {
    	std::ifstream file(path, std::ifstream::in);

    	regex vertexEx("^v [:d:] [:d:] [:d:] [:d:]");


    	const int cLineSize = 1024;
    	char line[cLineSize];

    	while(!file.eof())
    	{
    		file.getline(line, cLineSize);
			vector<string> elems = split(std::string(line), ' ');
    	}
    }

	static void BuildTriangle( CGeometry<SColorVertex>& triangle )
    {
        // Vertices:
        triangle << SColorVertex( float3( 0.0f, 0.0f, 0.0f ), float4( 1.0f, 0.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( 1.0f, 0.0f, 0.0f ), float4( 1.0f, 1.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( 0.0f, 1.0f, 0.0f ), float4( 0.0f, 0.0f, 1.0f, 1.0f ) );
        // Indices:
        triangle << 0 << 1 << 2;
        triangle << 0 << 2 << 1;

        triangle.SetPrimitiveMode( GL_TRIANGLES );
    }

    static void BuildPyramid( CGeometry<SColorVertex>& pyramid )
    {
        // Vertices:
    	pyramid << SColorVertex( float3( 0.0f, 5.0f, 0.0f ), float4( 1.0f, 0.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( 1.0f, 0.0f, 1.0f ), float4( 0.0f, 1.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( 1.0f, 0.0f, -1.0f ), float4( 0.0f, 0.0f, 1.0f, 1.0f ) )
                 << SColorVertex( float3( -1.0f, 0.0f, -1.0f ), float4( 1.0f, 1.0f, 0.0f, 1.0f ) )
                 << SColorVertex( float3( -1.0f, 0.0f, 1.0f ), float4( 1.0f, 0.0f, 1.0f, 1.0f ) );
        // Indices:
    	pyramid << 0 << 1 << 2;
    	pyramid << 0 << 2 << 3;
    	pyramid << 0 << 3 << 4;
    	pyramid << 0 << 4 << 1;
    	pyramid << 2 << 1 << 3;
    	pyramid << 2 << 3 << 4;

    	pyramid.SetPrimitiveMode( GL_TRIANGLES );
    }
};

} //namespace Ngn3D

