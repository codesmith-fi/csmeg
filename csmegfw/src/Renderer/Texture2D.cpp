#include "Texture2D.h"
#include "CSmegException.h"
#include "CDebug.h"

#include <boost/filesystem.hpp>

using namespace csmeg::renderer;
namespace fs = boost::filesystem;

Texture2D::Texture2D() : m_glTextureId(0)
{
}


Texture2D::~Texture2D()
{
    if(m_glTextureId > 0) {
        glDeleteTextures(1, &m_glTextureId);
    }
}

void Texture2D::bind()
{
    if(glIsTexture(m_glTextureId)) {
        glBindTexture(GL_TEXTURE_2D, m_glTextureId);
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
//    glBindTexture(GL_TEXTURE_2D, 0);
}
