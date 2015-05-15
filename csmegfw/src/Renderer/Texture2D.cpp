#include "Texture2D.h"
#include "CSmegException.h"
#include "CDebug.h"

#include <boost/filesystem.hpp>
#include <sstream>

using namespace csmeg::renderer;
namespace fs = boost::filesystem;

// Anonymous namespace for locals
namespace
{
    void verifyGLsuccess(const Texture2D& t, const std::string& msg)
    {
        GLenum glError = glGetError();
        if(glError != GL_NO_ERROR) {
            std::ostringstream err;
            err << msg << " : glError: " << glError << ", w:" << t.width() << " h:" << t.height();
            throw csmeg::CSmegException(err.str());
        }

    }
}

Texture2D::Texture2D()
    : Texture2D(0, 0, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_RGB, GL_RGB)
{
}

Texture2D::Texture2D(GLuint internalFormat, GLuint externalFormat)
    : Texture2D(0, 0, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, internalFormat, externalFormat)
{
}

Texture2D::Texture2D(int width, int height, GLuint filterMin, GLuint filterMax, GLuint wrapS, GLuint wrapT, GLuint internalFormat, GLuint externalFormat)
    : m_glTextureId(0), m_width(width), m_height(height),
      m_filter_min(filterMin),
      m_filter_max(filterMax),
      m_wrap_s(wrapS),
      m_wrap_t(wrapT),
      m_internalFormat(internalFormat),
      m_externalFormat(externalFormat),
      m_mipmapEnabled(false)
{

}

Texture2D::~Texture2D()
{
    // 0 is not a valid texture id (see doc for glIsTexture)
    if(m_glTextureId > 0) {
        glDeleteTextures(1, &m_glTextureId);
    }
}

void Texture2D::bind()
{
    // 0 is not a valid texture id (see doc for glIsTexture)
    if(m_glTextureId > 0 && glIsTexture(m_glTextureId)) {
        glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    }
    else {
        throw CSmegException("Texture2D::bind() trying to bind to invalid texture");
    }
}

void Texture2D::generate(uint16_t w, uint16_t h, uint8_t* data)
{
    if(glIsTexture(m_glTextureId)) {
        glDeleteTextures(1, &m_glTextureId);
    }

    m_width = w;
    m_height = h;

    glGenTextures(1, &m_glTextureId);
    verifyGLsuccess(*this, "failed generating texture id, glGenTextures()");

    glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0,
        m_internalFormat,
        w, h,
        0,
        m_externalFormat,
        GL_UNSIGNED_BYTE, data);
    init();

    verifyGLsuccess(*this, "failed creating texture image, glTexImage2D()");

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::generate(uint16_t w, uint16_t h, float* data)
{
    if(glIsTexture(m_glTextureId)) {
        glDeleteTextures(1, &m_glTextureId);
    }

    m_width = w;
    m_height = h;

    glGenTextures(1, &m_glTextureId);
    verifyGLsuccess(*this, "failed generating texture id, glGenTextures()");

    glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, 
        m_internalFormat, 
        w, h, 
        0, 
        m_externalFormat, 
        GL_FLOAT, data);

    init();

    verifyGLsuccess(*this, "failed creating texture image, glTexImage2D()");

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::init()
{
    if(glIsTexture(m_glTextureId)) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
    }
}
