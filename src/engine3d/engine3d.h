#pragma once

#include "common3d.h"

//#include "GLES2\gl2.h"

#include "types.h"
#include "program.h"
#include "shader.h"
#include "geometry.h"
#include "geometrybuilder.h"
#include "scene.h"

namespace Ngn3D
{

class TextureWrapper
{
public:    
    TextureWrapper(GLuint name) : m_Name(name) 
    {

    }

    ~TextureWrapper() 
    { 
        
    }

private:
    GLuint m_Name;
};

class GfxContext
{
public:
	GfxContext();    
	~GfxContext();

    static GLuint GenTexture() 
    {
        GLuint texName = 0;
        glGenTextures(1, &texName);
        return texName;
    }

    static void DeleteTexture(GLuint name)
    {
        if(glIsTexture(name))
            glDeleteTextures(1, &name);
        name = 0;
    }

    //Scene& Scene() { return m_Scene; }

    static GLuint LoadTextureDDS(const char* filePath);

	void Paint();

private:
    typedef Ngn3D::CGeometry<Ngn3D::CustomVertex> CSimpleGeometry;
    CProgram* m_TriangleProgram;
	Scene m_Scene;
    vector<GLuint> m_Textures;
};

} //namespace Ngn3D
