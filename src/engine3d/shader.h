#pragma once

//#include "GLES2\gl2.h"
#include "common3d.h"

#include <fstream>  // TODO: Move to cpp later
//#include <unique_ptr>

namespace Ngn3D
{

class CShader
{
    enum { cMaxPath = 1024 };

    GLuint  m_Shader;
    bool    m_IsCompiled;

public:
    CShader(GLenum type, const char* path)
        :   m_Shader(0),
            m_IsCompiled(false)
    {
        // Check for path length:
        if( strnlen( path, cMaxPath ) == cMaxPath )
        {
            throw "Shader path too long!";
        }

        //if( type != GL_FRAGMENT_SHADER ||
        //    type != GL_VERTEX_SHADER )
        //{
        //    throw "Shader type not supported!";
        //}

        using namespace std;

        // Load shader source from file:
        string shaderStr;

        // Open and read file:
        ifstream sourceStream(path, ifstream::binary);
        sourceStream.seekg(0, std::ios::end);
        int fileLen = static_cast<int>( sourceStream.tellg() );
        sourceStream.seekg(0);
        
        shaderStr.resize(fileLen);
        sourceStream.read(&shaderStr[0], fileLen);
        sourceStream.close();
        
        // Create GL shader;
        m_Shader = glCreateShader(type);
        if( m_Shader == 0 )
        {
            throw "Failed to allocate shader.";
        }

        const char* pStr = shaderStr.c_str();

        // Read shader's source:
        glShaderSource(m_Shader, 1, &pStr, &fileLen);
    }

    ~CShader()
    {
        if( glIsShader(m_Shader) )
        {
            glDeleteShader(m_Shader);
        }
    }
    
    GLuint GetId() const
    {
        return m_Shader;
    }

    void Compile()  // TODO: throws(gl_compilation_fail)
    {
        assert( glIsShader(m_Shader) );

        // Compile:
        glCompileShader( m_Shader );

        // Check for errors:
        GLint success = GL_TRUE;
        glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success );
        if( success == GL_FALSE )
        {
            // Get compilation log:
            GLint logSize = 0;
            glGetShaderiv(m_Shader, GL_INFO_LOG_LENGTH, &logSize );
            if( logSize > 0 )
            {
                char* infoLog = new char[logSize];
                glGetShaderInfoLog(m_Shader, logSize, NULL, infoLog);
                std::string infoLogStr(infoLog);
                delete [] infoLog;
                throw infoLogStr.c_str();   // TODO: This might be wrong! Implement own exception for it!
            }
        }
    }

};

} //namespace Ngn3D
