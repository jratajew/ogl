#pragma once

#include "common3d.h"
#include "program.h"

namespace Ngn3D
{

template <class TVertex, class TIndex = GLushort, class TNormal = float3>
class CGeometry
{
public:
	enum EDrawMode
	{
		DRAW_MODE_IMMEDIATE = 0,
		DRAW_MODE_INDEXED,

		DRAW_MODE_COUNT
	};

    CGeometry() throw()
        :   m_VertexBuffer( 0 ),
            m_IndexBuffer( 0 ),
            m_PrimitiveMode( GL_POINTS ),
			m_DrawMode(DRAW_MODE_IMMEDIATE)
    {
    }

    //CGeometry( 
    //    const std::vector<TVertex>& vertices, 
    //    const std::vector<TIndex>& indices) throw()
    //    :   m_VertexBuffer( 0 ),
    //        m_IndexBuffer( 0 ),
    //        m_PrimitiveMode( GL_POINTS ),
    //        m_Vertices( vertices ), 
    //        m_Indices( indices )
    //{
    //}

    //CGeometry( 
    //    const TVertex* pVertices, 
    //    const uint vertexCount, 
    //    const TIndex* pIndices,
    //    const uint indexCount )
    //    :   m_VertexBuffer( 0 ),
    //        m_IndexBuffer( 0 )
    //{
    //    for( uint v = 0; v < vertexCount; v++ )
    //    {
    //        m_Vertices.push_back( pVertices[v] );
    //    }
    //    
    //    for( uint i = 0; i < indexCount; i++ )
    //    {
    //        m_Indices.push_back( pIndices[i] );
    //    }
    //}

    ~CGeometry()
    {
        DeleteBuffers();
    }

    void CreateBuffers()
    {
        // TODO: Check for errors!

        // Create vertex array:
        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(TVertex) * GetVertexCount(), 
            m_Vertices.data(), 
            GL_STATIC_DRAW);

        // Create index array:
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            sizeof(TIndex) * GetIndexCount(), 
            m_Indices.data(), 
            GL_STATIC_DRAW);        
    }

    void DeleteBuffers()
    {
        if( glIsBuffer(m_VertexBuffer) )
        {
            glDeleteBuffers(1, &m_VertexBuffer);
        }

        if( glIsBuffer(m_IndexBuffer) )
        {
            glDeleteBuffers(1, &m_IndexBuffer);
        }
    }

    void BindBuffers();

    // TODO: Temp?
    void BindVertexBuffer( GLuint program ) const
    {
        int position_loc = glGetAttribLocation( program, "position" );
        int normal_loc = glGetAttribLocation( program, "color" );
        int texcoord_loc = glGetAttribLocation( program, "texCoord" );
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glVertexAttribPointer( position_loc, 3, GL_FLOAT, GL_FALSE, sizeof( CustomVertex ), CustomVertex::GetPositionOffset() );
        glEnableVertexAttribArray( position_loc );
        glVertexAttribPointer( normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof( CustomVertex ), CustomVertex::GetNormalOffset() );
        glEnableVertexAttribArray( normal_loc );
		glVertexAttribPointer( texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof( CustomVertex ), CustomVertex::GetTexCoordOffset() );
        glEnableVertexAttribArray( texcoord_loc );
    }

    void BindIndexBuffer() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
    }

    void Draw( CProgram& program/*, glm::mat4 mView, glm::mat4 mProj*/ ) const
    {
        BindVertexBuffer( program.GetProgram() );

		if(m_DrawMode == DRAW_MODE_INDEXED)
			BindIndexBuffer();

        //// Compute and set ModelView:
        //int locModelView = glGetUniformLocation(program.GetProgram(), "modelViewMatrix");

        //glm::mat4 mModelView = glm::lookAt(
        //		glm::vec3(10.0f, 10.0f, 10.0f), // eye
        //		glm::vec3(0.0f),				// look-at
        //		glm::vec3(0.0f, 1.0f, 0.0f) );	// up

        //static GLfloat sRotation = 0.0f;	// TODO: This is bad!
        //sRotation += 0.005f;
        //mModelView = glm::rotate(mModelView, sRotation, glm::vec3(0.0f, 1.0f, 0.0f));

        //glUniformMatrix4fv(locModelView, 1, GL_FALSE, glm::value_ptr(mModelView));

        //// Compute and set Projection:
        //int locProjection= glGetUniformLocation(program.GetProgram(), "projectionMatrix");

        //glm::mat4 mProjection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
        //glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(mProjection));

		if(m_DrawMode == DRAW_MODE_INDEXED)
		{
			glDrawElements(
				m_PrimitiveMode, 
				m_Indices.size(), 
				GLType<TIndex>::type,
				(void*)(0) );
		}
		else
		{
			glDrawArrays(
				m_PrimitiveMode,
				0,
				m_Vertices.size());
		}

        // TODO: index type should be determined from TIndex
    }
    
    CGeometry& operator<< ( const TVertex& vertex )
    {
        m_Vertices.push_back( vertex );
        return *this;
    }
    
    CGeometry& operator<< ( const TIndex& index )
    {
        m_Indices.push_back( index );
        return *this;
    }
    
    uint GetVertexCount() const { return m_Vertices.size(); }
    uint GetIndexCount() const  { return m_Indices.size(); }
    
    //GLenum  GetPrimitiveMode() const { return m_PrimitiveMode; }
    void    SetPrimitiveMode( GLenum mode ) { m_PrimitiveMode = mode; }

	void SetDrawMode(EDrawMode mode) { m_DrawMode = mode; }

protected:
    virtual void SetupUniforms()
    {
    	// Nothing to do...
    }
	
    GLuint m_VertexBuffer;
    GLuint m_IndexBuffer;
    GLenum m_PrimitiveMode;

    std::vector<TVertex>	m_Vertices;
    std::vector<TIndex>		m_Indices;
	std::vector<TNormal>	m_Normals;

	EDrawMode m_DrawMode;

};

} //namespace Ngn3D
