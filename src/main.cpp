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

Ngn3D::GfxContext* g_pGfxContext = nullptr;

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
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL");

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

    try
    {
		g_pGfxContext = new Ngn3D::GfxContext; // TODO: try catch

		glutDisplayFunc(renderFunction);
		glutIdleFunc(renderFunction);
		glutMainLoop();
    }
    catch(std::exception& ex)
    {
    	std::cout << ex.what() << endl;
    }

	return 0;
}
