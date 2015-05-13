#pragma once
#include <string>
#include <GL\glew.h>

struct SDL_Surface;

namespace csmeg
{
    namespace renderer
    {
        class Texture2D
        {
        public:
            Texture2D();
            virtual ~Texture2D();

            void load(const std::string& file);
            void bind();
        private:
            GLuint m_glTextureId;
        };
    }
}
