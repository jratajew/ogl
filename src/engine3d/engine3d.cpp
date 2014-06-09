#include "engine3d.h"

#pragma warning(push, 0)
#include "gli/gli.hpp"
#pragma warning(pop)

namespace Ngn3D
{

GfxContext::GfxContext() 
: m_TriangleProgram(nullptr)
{
    using namespace Ngn3D;

    // TODO: Shouldn't be done in here! Move to client's code!
    auto cubeGeom = shared_ptr<CustomGeometry>(new CGeometry<CustomVertex>);
    CGeometryBuiler::BuildFormObj("resources\\cube.obj", *cubeGeom);
    cubeGeom->CreateBuffers();
    auto cube = shared_ptr<DrawableObject>(new DrawableObject(cubeGeom));
    auto cube2 = shared_ptr<DrawableObject>(new DrawableObject(cubeGeom));

    cube2->Move(float3(0.0f, 3.0f, 0.0f));

    m_Scene.AddDrawable(cube);
    m_Scene.AddDrawable(cube2);

    CShader* fShader = new CShader(GL_FRAGMENT_SHADER, "resources/shaders/mvp.frag");
    CShader* vShader = new CShader(GL_VERTEX_SHADER, "resources/shaders/mvp.vert");

    fShader->Compile();
    vShader->Compile();

    m_TriangleProgram = new CProgram();
    m_TriangleProgram->Attach(fShader);
    m_TriangleProgram->Attach(vShader);
    m_TriangleProgram->Link();

    m_Textures.push_back(LoadTextureDDS("resources/textures/test-rgb8-256b.dds"));

    glEnable(GL_DEPTH_TEST);
}

GfxContext::~GfxContext()
{
    if(m_TriangleProgram)
        delete m_TriangleProgram;

    // Release textures:
    for(GLuint texName : m_Textures)
        DeleteTexture(texName);
    m_Textures.clear();
}

GLuint GfxContext::LoadTextureDDS(const char* filePath)
{
    GLuint texName = GenTexture();
    if(texName == 0)
    {
        return 0;
    }

    gli::texture2D tex(gli::load_dds(filePath));
    if(tex.empty())
    {
        DeleteTexture(texName);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLuint(tex.levels() - 1));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

    glTexStorage2D(
        GL_TEXTURE_2D,
        GLuint(tex.levels()),
        GLenum(gli::internalFormat(tex.format())),
        GLsizei(tex.dimensions().x),
        GLsizei(tex.dimensions().y));

    if(gli::is_compressed(tex.format()))
    {
        for(gli::texture2D::size_type level = 0; level < tex.levels(); ++level)
        {
            glCompressedTexSubImage2D(GL_TEXTURE_2D,
                GLint(level),
                0, 0,
                GLsizei(tex[level].dimensions().x),
                GLsizei(tex[level].dimensions().y),
                GLenum(gli::internal_format(tex.format())),
                GLsizei(tex[level].size()),
                tex[level].data());
        }
    }
    else
    {
        for(gli::texture2D::size_type level = 0; level < tex.levels(); ++level)
        {
            glTexSubImage2D(GL_TEXTURE_2D,
                GLint(level),
                0, 0,
                GLsizei(tex[level].dimensions().x),
                GLsizei(tex[level].dimensions().y),
                GLenum(gli::external_format(tex.format())),
                GLenum(gli::type_format(tex.format())),
                tex[level].data());
        }
    }

    return texName;
}

void GfxContext::Paint()
{
    glClearColor(0.5f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_TriangleProgram->Use();

    //glm::mat4 mModelView = glm::lookAt(
    //      		glm::vec3(10.0f, 10.0f, 10.0f), // eye
    //      		glm::vec3(0.0f),				// look-at
    //      		glm::vec3(0.0f, 1.0f, 0.0f) );	// up

    m_Scene.Draw(*m_TriangleProgram);
    //m_Triangle.Draw( *m_TriangleProgram );

    //glDrawArrays(GL_TRIANGLES, 0, 3 );
    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(0) );

    glutSwapBuffers();
}

}