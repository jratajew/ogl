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
InputListener* g_pInputListener = nullptr;

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
    if(g_pInputListener)
        g_pInputListener->KeyDown(key, x, y);
}

void processSpeciaKeys(int key, int x, int y)
{
    if(g_pInputListener)
        g_pInputListener->SpecialKeyDown(key, x, y);
}

void processNormalKeysUp(unsigned char key, int x, int y)
{
    if(g_pInputListener)
        g_pInputListener->KeyUp(key, x, y);
}

void processSpeciaKeysUp(int key, int x, int y)
{
    if(g_pInputListener)
        g_pInputListener->SpecialKeyUp(key, x, y);
}

void renderFunction()
{
	if(g_pGfxContext)
    {
        g_pGfxContext->Update(g_Timer.GetElapsedTime());
		g_pGfxContext->Paint();
    }
}

void processMouseButtons(int button, int state, int x, int y)
{
    InputListener::MouseButton mb = InputListener::MOUSE_BUTTON_COUNT;
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        mb = InputListener::MOUSE_BUTTON_LEFT;
        break;
    case GLUT_RIGHT_BUTTON:
        mb = InputListener::MOUSE_BUTTON_RIGHT;
        break;
    case GLUT_MIDDLE_BUTTON:
        mb = InputListener::MOUSE_BUTTON_MIDDLE;
        break;
    default:
        return;
    }

    if(g_pInputListener)
    {
        if(state == GLUT_UP)
            g_pInputListener->MouseButtonUp(mb, x, y);
        else if(state == GLUT_DOWN)
            g_pInputListener->MouseButtonDown(mb, x, y);
    }
}

void processActiveMouseMotion(int x, int y)
{
    if(g_pInputListener)
        g_pInputListener->MouseMotionActive(x, y);
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
        g_pInputListener = &g_pGfxContext->GetCurrentScene();

        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(processSpeciaKeys);
        glutKeyboardUpFunc(processNormalKeysUp);
        glutSpecialUpFunc(processSpeciaKeysUp);

        glutMouseFunc(processMouseButtons);
        glutMotionFunc(processActiveMouseMotion);

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
