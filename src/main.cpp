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
KeyboardListener* g_pKeyboardListener = nullptr;

class Timer
{
public:
    Timer()
    {
        ResetFrequency();
        m_LastCount = CurrentCount();
    }

    double GetElapsedTime()
    {
        double currentCount = CurrentCount();
        double elapsedTime = (currentCount - m_LastCount)/m_Freq;
        m_LastCount = currentCount;
        return elapsedTime;
    }

    void ResetFrequency()
    {
        LARGE_INTEGER liFreq;
        QueryPerformanceFrequency(&liFreq);
        m_Freq = double(liFreq.QuadPart);// / 1000.0;
    }

private:
    double CurrentCount() 
    {
        LARGE_INTEGER liFreq;
        QueryPerformanceCounter(&liFreq);
        return static_cast<double>(liFreq.QuadPart);
    }
    double m_LastCount;
    double m_Freq;
};

Timer g_Timer;

void processNormalKeys(unsigned char key, int x, int y)
{
    if(g_pKeyboardListener)
        g_pKeyboardListener->KeyDown(key, x, y);
}

void processSpeciaKeys(int key, int x, int y)
{
    if(g_pKeyboardListener)
        g_pKeyboardListener->SpecialKeyDown(key, x, y);
}

void processNormalKeysUp(unsigned char key, int x, int y)
{
    if(g_pKeyboardListener)
        g_pKeyboardListener->KeyUp(key, x, y);
}

void processSpeciaKeysUp(int key, int x, int y)
{
    if(g_pKeyboardListener)
        g_pKeyboardListener->SpecialKeyUp(key, x, y);
}

void renderFunction()
{
	if(g_pGfxContext)
    {
        g_pGfxContext->Update(g_Timer.GetElapsedTime());
		g_pGfxContext->Paint();
    }
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800,600);
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
        g_pKeyboardListener = &g_pGfxContext->GetCurrentScene();

        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(processSpeciaKeys);
        glutKeyboardUpFunc(processNormalKeysUp);
        glutSpecialUpFunc(processSpeciaKeysUp);

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
