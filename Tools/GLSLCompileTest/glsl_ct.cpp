#include "common3d.h"
#include "shader.h"
#include <iostream>

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    if(GLEW_ARB_vertex_program)
        std::cout << "Status: ARB vertex programs available.\n";

    if(glewGetExtension("GL_ARB_fragment_program"))
        std::cout << "Status: ARB fragment programs available.\n";

    if(glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
        std::cout << "Status: ARB point sprites available.\n";

    using namespace std;
    using namespace Ngn3D;

    GLenum shaderType = 0;

    for(int i = 1; i < argc; ++i)
    {
        string arg(argv[i]);

        if(shaderType == 0)
        {
            if(arg == "-fs")
                shaderType = GL_FRAGMENT_SHADER;
            else if(arg == "-vs")
                shaderType == GL_VERTEX_SHADER;
            else if(arg == "-gs")
                shaderType == GL_GEOMETRY_SHADER;
            // TODO ...

            continue;
        }
        
        cout << arg << ":";

        try
        {
            CShader shader(shaderType, arg.c_str());
            if(shader.Compile())
            {
                cout << " ok\n";
            }
            else
            {
                cout << " failed!\n";
                cout << shader.GetErrorStr() << endl;
            }
        }
        catch(std::exception& ex)
        {
            std::cout << ex.what() << endl;
        }

    }
}