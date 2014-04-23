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

		// Object declaration:
		regex regEx_Object("^o ([[:alnum:]]+)$");
		// Vertex declaration:
    	regex regEx_Vertex("^v ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ?([-+]?[0-9]*\.?[0-9]+)?$");
		// Vertex normal declaration:
    	regex regEx_Normal("^vn ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+)");
		// Face declaration:
		regex regEx_Face("^f( ([0-9]+)/?([0-9]*)?/?([0-9]+)?)+$");

		//regex regEx_Edge(
		
		object.SetPrimitiveMode( GL_TRIANGLES );

    	//const int cLineSize = 1024;
    	//char line[cLineSize];
		string line;

    	while(!file.eof())
    	{
			getline(file, line);
    		//file.getline(line, cLineSize);

			cout << "Parsing line: \"" << line << "\"\n";

			if( line[0] == '#' )
				continue;
			
			smatch m;
			if( regex_match(line, m, regEx_Object) )
			{
				// Object:
				string objName = m[1].str();
				cout << "    Object found: " << objName << endl;
			}
			else if( regex_match(line, m, regEx_Vertex) )
			{
				// Vertex:
				glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
				if(m[1].matched)
					vec.x = atof(m[1].str().c_str());
				if(m[2].matched)
					vec.y = atof(m[2].str().c_str());
				if(m[3].matched)
					vec.z = atof(m[3].str().c_str());
				if(m[4].matched)
					vec.w = atof(m[4].str().c_str());
				cout << "    Vertex found: " 
					<< vec.x << " " << vec.y << " " << vec.z << " " << vec.w << "\n";

				object << SColorVertex( float3(vec.x, vec.y, vec.z), float4( 1.0f, 0.2f, 0.2f, 1.0f ) );
			}
			else if( regex_match(line, m, regEx_Normal) )
			{
				// Normal:
				glm::vec3 vec(0.0f, 0.0f, 0.0f);
				if(m[1].matched)
					vec.x = atof(m[1].str().c_str());
				if(m[2].matched)
					vec.y = atof(m[2].str().c_str());
				if(m[3].matched)
					vec.z = atof(m[3].str().c_str());
				cout << "    Normal found: " 
					<< vec.x << " " << vec.y << " " << vec.z << "\n";
			}
			else if( regex_match(line, regEx_Face) )
			{
				// Face:
				cout << "    Face:";
				Face face;
				regex regEx_FaceVertex("^[0-9]+/?[0-9]*?/?[0-9]*?$");
				vector<string> splittedFace = split(line, ' ');
				assert(splittedFace.size() > 0 && splittedFace[0] == "f");

				// All faces should be triangles!
				assert(splittedFace.size() == 4);

				for( int i = 1; i < splittedFace.size(); i++ )
				{
					if(regex_match(splittedFace[i], regEx_FaceVertex))
					{
						vector<string> splittedVertex = split(splittedFace[i], '/');
						Face::Vertex fVertex;
						assert(splittedVertex.size() > 0 && splittedVertex.size() <= 3);

						fVertex.VertexId = static_cast<ushort>( std::stoi(splittedVertex[0]) );	

						if( splittedVertex.size() == 2 )
						{
							fVertex.CoordId = static_cast<ushort>( std::stoi(splittedVertex[1]) );
						}
						else if( splittedVertex.size() == 3 )
						{
							if( splittedVertex[1] != "" )
								fVertex.CoordId = static_cast<ushort>( std::stoi(splittedVertex[1]) );
							fVertex.NormalId = static_cast<ushort>( std::stoi(splittedVertex[2]) );
						}
						cout << "         V: " 
							<< fVertex.VertexId << "/" 
							<< fVertex.CoordId << "/" 
							<< fVertex.NormalId << endl;

						object << fVertex.VertexId-1;
					}
					else
					{
						assert(0);
					}
				}
				cout << endl;
			}
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

