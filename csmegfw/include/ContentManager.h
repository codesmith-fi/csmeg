#pragma once

#include <string>
#include <map>
#include <memory>

namespace csmeg
{
    namespace renderer
    {
        class Texture2D;
    }

    class ContentManager
    {
    public:
        static ContentManager& instance()
        {
            static ContentManager me;
            return me;
        }
        virtual ~ContentManager();

    public: // environment methods
        void contentDir(const std::string& base);
        void textureFolder(const std::string& folder); // relative
        void shaderFolder(const std::string& folder); // relative

    public: // Content loaders
        std::shared_ptr<renderer::Texture2D> getTexture(const std::string& name);
        void loadTexture(const std::string& file, bool transparent, const std::string& name = "");

    private: // methods
        ContentManager();
        ContentManager(const ContentManager&); // not implemented
        ContentManager& operator=(const ContentManager&); // not implemented

    private: // data
        std::map<std::string, std::shared_ptr<renderer::Texture2D>> m_textures;
    };
}
