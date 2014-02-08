#pragma once

#include "common3d.h"

namespace Ngn3D
{

//#define CGEOMETRY_TEMPLATE_ARGS

template <class TVertex, class TIndex = GLushort>
class CGeometry
{
    GLuint m_VertexBuffer;
    GLuint m_IndexBuffer;
    GLenum m_PrimitiveMode;

    std::vector<TVertex> m_Vertices;
    std::vector<TIndex> m_Indices;

public:
    CGeometry() throw()
        :   m_VertexBuffer( 0 ),
            m_IndexBuffer( 0 ),
            m_PrimitiveMode( GL_POINTS )
    {
    }

    CGeometry( 
        const std::vector<TVertex>& vertices, 
        const std::vector<TIndex>& indices) throw()
        :   m_VertexBuffer( 0 ),
            m_IndexBuffer( 0 ),
            m_PrimitiveMode( GL_POINTS ),
            m_Vertices( vertices ), 
            m_Indices( indices )
    {
    }

    CGeometry( 
        const TVertex* pVertices, 
        const uint vertexCount, 
        const TIndex* pIndices,
        const uint indexCount )
        :   m_VertexBuffer( 0 ),
            m_IndexBuffer( 0 )
    {
        for( uint v = 0; v < vertexCount; v++ )
        {
            m_Vertices.push_back( pVertices[v] );
        }
        
        for( uint i = 0; i < indexCount; i++ )
        {
            m_Indices.push_back( pIndices[i] );
        }
    }

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
        int color_loc = glGetAttribLocation( program, "color" );
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glVertexAttribPointer( position_loc, 3, GL_FLOAT, GL_FALSE, sizeof( SColorVertex ), SColorVertex::GetPositionOffset() );
        glEnableVertexAttribArray( position_loc );
        glVertexAttribPointer( color_loc, 4, GL_FLOAT, GL_FALSE, sizeof( SColorVertex ), SColorVertex::GetColorOffset() );
        glEnableVertexAttribArray( color_loc );
    }

    void BindIndexBuffer() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
    }

    void Draw( CProgram& program ) const
    {
        program.Use();
        BindVertexBuffer( program.GetProgram() );
        BindIndexBuffer();
        glDrawArrays(
            m_PrimitiveMode, 
            0,
            m_Vertices.size() );
        // TODO: index type should be determined from TIndex
    }
    
    void DrawIndexed( CProgram& program ) const
    {
        program.Use();
        BindVertexBuffer( program.GetProgram() );
        BindIndexBuffer();
        glDrawElements(
            m_PrimitiveMode, 
            m_Indices.size(), 
            GLType<TIndex>::type, 
            (void*)(0) );
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
};

} //namespace Ngn3D
