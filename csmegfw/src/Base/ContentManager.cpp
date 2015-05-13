#include "ContentManager.h"
#include "CSmegException.h"

#include <Texture2D.h>
#include <boost/filesystem.hpp>
#include <SOIL.h>

using namespace csmeg;
using namespace csmeg::renderer;
namespace fs = boost::filesystem;

ContentManager::ContentManager()
    : m_textures(),
      m_basePath(fs::initial_path<fs::path()>()),
      m_texturePath(m_basePath),
      m_shaderPath(m_basePath)
{
}

ContentManager::~ContentManager()
{
}

void ContentManager::contentDir(const std::string& base)
{
    fs::path p(base);
    if(!fs::exists(p)) {
        std::string err("Base content directory does not exist: ");
        err += p.string();
        throw CSmegException(err);
    }
    m_basePath = p;
}

void ContentManager::textureFolder(const std::string& folder)
{
    fs::path p(m_basePath);
    p /= folder;
    if(!fs::exists(p)) {
        std::string err("Texture content folder does not exist: ");
        err += p.string();
        throw CSmegException(err);
    }
    m_texturePath = p;
}

std::shared_ptr<renderer::Texture2D> ContentManager::getTexture(const std::string& name)
{
    return m_textures[name];
}

void ContentManager::loadTexture(const std::string& file, bool transparent, const std::string& name)
{
    if(!file.length()) {
        throw CSmegException("ContentManager::loadTexture() called with no filename");
    }

    fs::path fp = m_texturePath;
    fp /= file;
    if(!fs::exists(fp)) {
        std::string err("Texture file does not exist: ");
        err += fp.string();
        throw CSmegException(err);
    }

    // If no indexing name given, use the filename
    std::string indexName = name.length() ? name : file;
    GLuint format = transparent ? GL_RGBA : GL_RGB;
    renderer::Texture2D* newTexture = new Texture2D(format, format);
    int width;
    int height;
    unsigned char* image = SOIL_load_image(fp.string().c_str(), &width, &height, 0,
        transparent ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    newTexture->generate(width, height, image);
    SOIL_free_image_data(image);

    /*
    // Black/white checkerboard
    float pixels[] = {
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    renderer::Texture2D* newTexture = new Texture2D();
    newTexture->generate(2, 2, pixels);
*/
//    newTexture->generate(width, height, imgData);
    m_textures[indexName] = std::shared_ptr<Texture2D>(newTexture);
}
