#pragma once

//#include "GLES2\gl2.h"
#include "common3d.h"

#include <fstream>  // TODO: Move to cpp later
#include <list>
//#include <unique_ptr>

namespace Ngn3D
{

class CShader
{
public:
    CShader(GLenum type, const char* path);

    ~CShader();
    
    inline GLuint GetId() const
    {
        return m_Shader;
    }

    bool Compile();

    const std::string& GetErrorStr() const { return m_ErrorStr; }

private:
    static const int cMaxPath = 1024;
/*
    struct SUniform
    {
    	//static const GLuint scUndefinedLoc = 0xfefefefe;
    	std::string Name;
    	GLuint 		Location;
    };
    */
    std::string m_FilePath;

    GLuint  m_Shader;
    bool    m_IsCompiled;

    bool    m_CompilationError;
    string  m_ErrorStr;


};

} //namespace Ngn3D
