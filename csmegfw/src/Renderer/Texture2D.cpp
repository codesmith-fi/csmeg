#include "Texture2D.h"
#include "CSmegException.h"
#include "CDebug.h"

#include <boost/filesystem.hpp>
#include <ostream>

using namespace csmeg::renderer;
namespace fs = boost::filesystem;

// Anonymous namespace for locals
namespace
{
    int resolveFilter(Texture2D::TextureFilterMode m) 
    {
        int res = GL_LINEAR;
        switch(m) {
            case Texture2D::TextureFilterMode::NEAREST:
            {
                res = GL_NEAREST;
                break;
            }
            case Texture2D::TextureFilterMode::NEAREST_MIPMAP_NEAREST:
            {
                res = GL_NEAREST_MIPMAP_NEAREST;
                break;
            }
            case Texture2D::TextureFilterMode::LINEAR_MIPMAP_NEAREST:
            {
                res = GL_LINEAR_MIPMAP_NEAREST;
                break;
            }
            case Texture2D::TextureFilterMode::NEAREST_MIPMAP_LINEAR:
            {
                res = GL_NEAREST_MIPMAP_LINEAR;
                break;
            }
            case Texture2D::TextureFilterMode::LINEAR_MIPMAP_LINEAR:
            {
                res = GL_LINEAR_MIPMAP_LINEAR;
                break;
            }
            case Texture2D::TextureFilterMode::LINEAR:
            {
                res = GL_LINEAR;
                break;
            }
            default:
            {
                res = GL_LINEAR;
                break;
            }
        }
        return res;
    }

    int resolveWrapping(Texture2D::TextureWrapMode m)
    {
        int res = GL_CLAMP_TO_EDGE;
        switch(m) {
            case Texture2D::TextureWrapMode::REPEAT:
            {
                res = GL_REPEAT;
                break;
            }
            case Texture2D::TextureWrapMode::MIRRORED_REPEAT:
            {
                res = GL_MIRRORED_REPEAT;
                break;
            }
            case Texture2D::TextureWrapMode::CLAMP_TO_EDGE:
            {
                res = GL_CLAMP_TO_EDGE;
                break;
            }
            case Texture2D::TextureWrapMode::CLAMP_TO_BORDER:
            {
                res = GL_CLAMP_TO_BORDER;
                break;
            }
            default:
            {
                res = GL_CLAMP_TO_EDGE;
                break;
            }
        }
        return res;
    }

    int resolveFormat(Texture2D::TextureFormat f)
    {
        int res = GL_RGB;
        if(f == Texture2D::TextureFormat::RGBA) {
            res = GL_RGBA;
        }
        return res;
    }

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

Texture2D::Texture2D() : 
    m_glTextureId(0), m_width(0), m_height(0), 
    m_filter_min(TextureFilterMode::LINEAR), 
    m_filter_max(TextureFilterMode::LINEAR),
    m_wrap_s(TextureWrapMode::CLAMP_TO_EDGE),
    m_wrap_t(TextureWrapMode::CLAMP_TO_EDGE),
    m_internalFormat(TextureFormat::RGB),
    m_externalFormat(TextureFormat::RGB),
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

void Texture2D::load(const std::string& file)
{
    if(!file.length()) {
        throw CSmegException("Supplied texture filename is nil");
    }
    fs::path fn(fs::initial_path<fs::path()>());
    fn /= "textures";
    fn /= file;
    LOG_INFO() << "Texture2D::load : " << fn;

    // Black/white checkerboard
    float pixels[] = {
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
    };
    glGenTextures(1, &m_glTextureId);
    glBindTexture(GL_TEXTURE_2D, m_glTextureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBindTexture(GL_TEXTURE_2D, 0);
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
        resolveFormat(m_internalFormat),
        w, h,
        0,
        resolveFormat(m_externalFormat),
        GL_UNSIGNED_BYTE, data);

    verifyGLsuccess(*this, "failed creating texture image, glTexImage2D()");

    init();
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
        resolveFormat(m_internalFormat), 
        w, h, 
        0, 
        resolveFormat(m_externalFormat), 
        GL_FLOAT, data);

    verifyGLsuccess(*this, "failed creating texture image, glTexImage2D()");

    init();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::init()
{
    if(glIsTexture(m_glTextureId)) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, resolveFilter(m_filter_min));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, resolveFilter(m_filter_max));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, resolveWrapping(m_wrap_s));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, resolveWrapping(m_wrap_t));

        if(m_mipmapEnabled) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
}
