#pragma once
#include <string>
#include <GL/glew.h>
#include <stdint.h>

namespace csmeg
{
    namespace renderer
    {
        class Texture2D
        {
        public:
            Texture2D();
            Texture2D(GLuint internalFormat, GLuint externalFormat);
            Texture2D(int width, int height, GLuint filterMin, GLuint filterMax, GLuint wrapS, GLuint wrapT, GLuint internalFormat, GLuint externalFormat);
            virtual ~Texture2D();

            void mipmap(bool enabled) { m_mipmapEnabled = enabled; }
            bool mipmap() const { return m_mipmapEnabled; }
            uint16_t width() const { return m_width; }
            uint16_t height() const { return m_height; }

            void generate(uint16_t w, uint16_t h, uint8_t* data);
            void generate(uint16_t w, uint16_t h, float* data);
            void bind();        

        private:
            /**
             * Initialize texture parameters
             */
            void init();
            Texture2D(const Texture2D& other); // not implemented
            Texture2D& operator=(const Texture2D& other); // not implemented

        private:
            GLuint m_glTextureId;
            uint16_t m_width;
            uint16_t m_height;
            GLuint m_filter_min;
            GLuint m_filter_max;
            GLuint m_wrap_s;
            GLuint m_wrap_t;
            GLuint m_internalFormat;
            GLuint m_externalFormat;
            bool m_mipmapEnabled;
        };
    }
}
