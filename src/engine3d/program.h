#pragma once

#include "common3d.h"

#include "shader.h"

namespace Ngn3D
{

class CProgram
{
    GLuint                  m_Program;
    std::vector<CShader*>   m_Shaders;

public:
    CProgram()
    {
        m_Program = glCreateProgram();
        if( !glIsProgram(m_Program) )
        {
            throw "Failed to create program!";
        }
    }

    ~CProgram()
    {
        assert( glIsProgram(m_Program) );

        for(CShader* shader : m_Shaders)
        {
            glDetachShader( m_Program, shader->GetId() );
        }

        glDeleteProgram(m_Program);
    }

    GLuint GetProgram() const   { return m_Program; }

    void Attach( CShader* shader )
    {
        glAttachShader(m_Program, shader->GetId());
        m_Shaders.push_back(shader);
    }

    void Link()
    {
        glLinkProgram(m_Program);
        
        // Check for errors:
        GLint success = GL_TRUE;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &success );
        if( success == GL_FALSE )
        {
            // Get compilation log:
            GLint logSize = 0;
            glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &logSize );
            if( logSize > 0 )
            {
                char* infoLog = new char[logSize];
                glGetProgramInfoLog(m_Program, logSize, NULL, infoLog);
                std::string infoLogStr(infoLog);
                delete [] infoLog;
                throw infoLogStr.c_str();   // TODO: This might be wrong! Implement own exception for it!
            }
        }
    }

    void Use()
    {
        glUseProgram(m_Program);
    }

    template <class T>
    void SetAttributePointer( char* name, T value )
    {
        int loc = glGetAttribLocation( m_Program, name );
        // TODO!
    }
};

} //namespace Ngn3D
