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

    // path - path to wavefront obj file
    shared_ptr<CustomGeometry> LoadGeometryFromObj(const char* path, const char* name)
    {
        CustomGeometry* pGeom = new CGeometry<CustomVertex>;
        CGeometryBuiler::BuildFormObj(path, *pGeom);
        pGeom->CreateBuffers();

        auto shPtr = shared_ptr<CustomGeometry>(pGeom);
        m_Geometries[name] = shPtr;
        return shPtr;
    }

    ~GfxContext();

    inline Scene& GetCurrentScene()
    {
        return m_Scene;
    }

    inline const Scene& GetCurrentScene() const
    {
        return m_Scene;
    }

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

    void Update(double dt) 
    { 
        m_Dt = dt; 
        m_Scene.Update(static_cast<float>(dt));
    }

private:
    typedef Ngn3D::CGeometry<Ngn3D::CustomVertex> CSimpleGeometry;

    CProgram* m_TriangleProgram;
	Scene m_Scene;
    map<string, GLuint> m_Textures;
    map<string, shared_ptr<CustomGeometry>> m_Geometries;    

    double m_Dt;
};

} //namespace Ngn3D
