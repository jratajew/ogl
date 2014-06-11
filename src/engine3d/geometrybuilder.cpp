#include "geometrybuilder.h"

#include <fstream>
#include <regex>

namespace Ngn3D
{


void CGeometryBuiler::BuildFormObj(const std::string& path, CGeometry<CustomVertex>& object)
{
    const bool bVerbose = false;

    std::ifstream file(path, std::ifstream::in);

    vector<float4> vertices;
    vector<float3> normals;
    vector<float3> texCoords;
    bool smooth = false;

    // For simplicity (indices are numbered from 1 in obj)
    vertices.push_back(float4(0.0f));
    normals.push_back(float3(0.0f));
    texCoords.push_back(float3(0.0f));

    // Object declaration:
    regex regEx_Object("^o ([[:alnum:]]+)$");
    // Vertex declaration:
    regex regEx_Vertex("^v ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ?([-+]?[0-9]*\.?[0-9]+)?$");
    // Vertex normal declaration:
    regex regEx_Normal("^vn ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+)$");
    // Vertex texture coordinate declaration:
    regex regEx_TexCoord("^vt ([-+]?[0-9]*\.?[0-9]+) ([-+]?[0-9]*\.?[0-9]+) ?([-+]?[0-9]*\.?[0-9]+)?$");
    // Face declaration:
    regex regEx_Face("^f( ([0-9]+)/?([0-9]*)?/?([0-9]+)?)+$");

    object.SetPrimitiveMode(GL_TRIANGLES);
    object.SetDrawMode(CGeometry<CustomVertex>::DRAW_MODE_IMMEDIATE);

    string line;


    while(!file.eof())
    {
        getline(file, line);
        //file.getline(line, cLineSize);

        if(bVerbose) cout << "Parsing line: \"" << line << "\"\n";

        if(line[0] == '#')
            continue;

        smatch m;
        if(regex_match(line, m, regEx_Object))
        {
            // Object:
            string objName = m[1].str();
            if(bVerbose) cout << "    Object found: " << objName << endl;
        }
        else if(regex_match(line, m, regEx_Vertex))
        {
            // Vertex:
            float4 vec(0.0f, 0.0f, 0.0f, 1.0f);
            if(m[1].matched)
                vec.x = static_cast<float>(std::atof(m[1].str().c_str()));
            if(m[2].matched)
                vec.y = static_cast<float>(std::atof(m[2].str().c_str()));
            if(m[3].matched)
                vec.z = static_cast<float>(std::atof(m[3].str().c_str()));
            if(m[4].matched)
                vec.w = static_cast<float>(std::atof(m[4].str().c_str()));
            if(bVerbose) cout << "    Vertex found: "
                << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << "\n";

            //object << CustomVertex( float3(vec.x, vec.y, vec.z), float4( 1.0f, 0.2f, 0.2f, 1.0f ) );
            vertices.push_back(vec);
        }
        else if(regex_match(line, m, regEx_Normal))
        {
            // Normal:
            float3 vec(0.0f, 0.0f, 0.0f);
            if(m[1].matched)
                vec.x = static_cast<float>(std::atof(m[1].str().c_str()));
            if(m[2].matched)
                vec.y = static_cast<float>(std::atof(m[2].str().c_str()));
            if(m[3].matched)
                vec.z = static_cast<float>(std::atof(m[3].str().c_str()));
            if(bVerbose) cout << "    Normal found: "
                << vec.x << " " << vec.y << " " << vec.z << "\n";

            normals.push_back(vec);
        }
        else if(regex_match(line, m, regEx_TexCoord))
        {
            // Normal:
            float3 vec(0.0f, 0.0f, 0.0f);
            if(m[1].matched)
                vec.x = static_cast<float>(std::atof(m[1].str().c_str()));
            if(m[2].matched)
                vec.y = static_cast<float>(std::atof(m[2].str().c_str()));
            if(m[3].matched)
                vec.z = static_cast<float>(std::atof(m[3].str().c_str()));
            if(bVerbose) cout << "    TexCoord found: "
                << vec.x << " " << vec.y << " " << vec.z << "\n";

            texCoords.push_back(vec);
        }
        else if(regex_match(line, regEx_Face))
        {
            // Face:
            if(bVerbose) cout << "    Face:";
            Face face;
            regex regEx_FaceVertex("^[0-9]+/?[0-9]*?/?[0-9]*?$");
            vector<string> splittedFace = split(line, ' ');
            assert(splittedFace.size() > 0 && splittedFace[0] == "f");

            // All faces should be triangles!
            assert(splittedFace.size() == 4);

            for(size_t i = 1; i < splittedFace.size(); i++)
            {
                if(regex_match(splittedFace[i], regEx_FaceVertex))
                {
                    vector<string> splittedVertex = split(splittedFace[i], '/');
                    Face::Vertex fVertex;
                    assert(splittedVertex.size() > 0 && splittedVertex.size() <= 3);

                    fVertex.VertexId = static_cast<ushort>(std::stoi(splittedVertex[0]));

                    if(splittedVertex.size() == 2)
                    {
                        fVertex.CoordId = static_cast<ushort>(std::stoi(splittedVertex[1]));
                    }
                    else if(splittedVertex.size() == 3)
                    {
                        if(splittedVertex[1] != "")
                            fVertex.CoordId = static_cast<ushort>(std::stoi(splittedVertex[1]));
                        fVertex.NormalId = static_cast<ushort>(std::stoi(splittedVertex[2]));
                    }
                    if(bVerbose) cout << "         V: "
                        << fVertex.VertexId << "/"
                        << fVertex.CoordId << "/"
                        << fVertex.NormalId << endl;

                    float4 pos4 = vertices[fVertex.VertexId];
                    float3 pos = float3(pos4.x, pos4.y, pos4.z);
                    assert(fVertex.NormalId != Face::NOT_SET);
                    float3 normal = normals[fVertex.NormalId];
                    float2 texCoord = float2(texCoords[fVertex.CoordId]);
                    object << CustomVertex(pos, normal, texCoord);
                }
                else
                {
                    assert(0);
                }
            }
            if(bVerbose) cout << endl;
        }
        else if(line == "s on")
        {
            smooth = true;

            // No vertex duplication needed if smooth is enabled:

        }
        else if(line == "s off")
        {
            smooth = false;
        }
    }
}

void CGeometryBuiler::BuildTerrainQuad(CustomGeometry& terrain, float width, float length)
{
    float half_w = width / 2;
    float half_l = length / 2;

    terrain << CustomVertex(float3(-half_w, 0.0f, half_l), float3(0.0f, 1.0f, 0.0f), float2(0.0f, 0.0f))
        << CustomVertex(float3(-half_w, 0.0f, -half_l), float3(0.0f, 1.0f, 0.0f), float2(0.0f, 1.0f))
        << CustomVertex(float3(half_w, 0.0f, half_l), float3(0.0f, 1.0f, 0.0f), float2(1.0f, 0.0f))
        << CustomVertex(float3(half_w, 0.0f, -half_l), float3(0.0f, 1.0f, 0.0f), float2(1.0f, 1.0f));

    terrain.SetPrimitiveMode(GL_TRIANGLE_STRIP);
    terrain.SetDrawMode(CustomGeometry::DRAW_MODE_IMMEDIATE);
}

}