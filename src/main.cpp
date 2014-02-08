//============================================================================
// Name        : main.cpp
// Author      : Jacek R
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include <memory>



#include "common.h"
#include "engine3d/engine3d.h"
//#include <list>

class GfxContext
{
public:
	GfxContext() :
		m_Triangle(),
		m_TriangleProgram(NULL)
	{
	    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );

	    using namespace Ngn3D;

	    CGeometryBuiler::BuildTriangle( m_Triangle );
	    m_Triangle.CreateBuffers();

	    CShader* fShader = new CShader( GL_FRAGMENT_SHADER, "resources/shaders/basic.fsh" );
	    CShader* vShader = new CShader( GL_VERTEX_SHADER, "resources/shaders/basic.vsh" );

	    fShader->Compile();
	    vShader->Compile();

	    m_TriangleProgram = new CProgram();
	    m_TriangleProgram->Attach( fShader );
	    m_TriangleProgram->Attach( vShader );
	    m_TriangleProgram->Link();
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

	    //m_TriangleProgram->Use();
	    m_Triangle.Draw( *m_TriangleProgram );

	    //glDrawArrays(GL_TRIANGLES, 0, 3 );
	    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(0) );

	    glutSwapBuffers();
	}

private:
    typedef Ngn3D::CGeometry<Ngn3D::SColorVertex> CSimpleGeometry;
    CSimpleGeometry m_Triangle;
    Ngn3D::CProgram* m_TriangleProgram;
};

GfxContext* g_pGfxContext = nullptr;

/*
static void error_callback(int error, const char* desc)
{
	std::cout << "Error " << error << ": " << desc << std::endl;
}

static void key_callback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods)
{
	if(key == GLFW_KEY_ESCAPE && action==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
*/

void renderFunction()
{
	if(g_pGfxContext)
		g_pGfxContext->Paint();
}

int main(int argc, char** argv) {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
    	std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    if (GLEW_ARB_vertex_program)
        std::cout << "Status: ARB vertex programs available.\n";

    if (glewGetExtension("GL_ARB_fragment_program"))
    	std::cout << "Status: ARB fragment programs available.\n";

    if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
    	std::cout << "Status: ARB point sprites available.\n";

    g_pGfxContext = new GfxContext; // TODO: try catch

    glutDisplayFunc(renderFunction);
    glutMainLoop();

	return 0;
}
