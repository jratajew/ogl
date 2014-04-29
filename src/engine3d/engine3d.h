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

class GfxContext
{
public:
	GfxContext()
		: m_TriangleProgram(nullptr)
	{
	    using namespace Ngn3D;

	    //try
	    {
	    	auto cubeGeom = shared_ptr<CustomGeometry>(new CGeometry<CustomVertex>);
			CGeometryBuiler::BuildFormObj("resources\\cube.obj", *cubeGeom);
	    	cubeGeom->CreateBuffers();
			auto cube = shared_ptr<DrawableObject>(new DrawableObject(cubeGeom));			
			auto cube2 = shared_ptr<DrawableObject>(new DrawableObject(cubeGeom));

			cube2->Move(float3(0.0f, 3.0f, 0.0f));

			m_Scene.AddDrawable(cube);
			m_Scene.AddDrawable(cube2);

	    	CShader* fShader = new CShader( GL_FRAGMENT_SHADER, "resources/shaders/mvp.frag" );
	    	CShader* vShader = new CShader( GL_VERTEX_SHADER, "resources/shaders/mvp.vert" );

	    	fShader->Compile();
	    	vShader->Compile();

	    	m_TriangleProgram = new CProgram();
	    	m_TriangleProgram->Attach( fShader );
	    	m_TriangleProgram->Attach( vShader );
	    	m_TriangleProgram->Link();
	    }
	    //catch(std::exception& ex)
	    //{
	    //	std::cerr << ex.what();
	    //}
	}

	~GfxContext()
	{
		if(m_TriangleProgram)
			delete m_TriangleProgram;
	}

	void Paint()
	{
	    glClearColor(0.5f, 0.1f, 0.2f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    m_TriangleProgram->Use();

		//glm::mat4 mModelView = glm::lookAt(
  //      		glm::vec3(10.0f, 10.0f, 10.0f), // eye
  //      		glm::vec3(0.0f),				// look-at
  //      		glm::vec3(0.0f, 1.0f, 0.0f) );	// up

		m_Scene.Draw(*m_TriangleProgram);
	    //m_Triangle.Draw( *m_TriangleProgram );

	    //glDrawArrays(GL_TRIANGLES, 0, 3 );
	    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(0) );

	    glutSwapBuffers();
	}

private:
    typedef Ngn3D::CGeometry<Ngn3D::CustomVertex> CSimpleGeometry;
    Ngn3D::CProgram* m_TriangleProgram;
	Scene m_Scene;
};

} //namespace Ngn3D
