#pragma once
#include <string>
#include <GL\glew.h>
#include <stdint.h>

namespace csmeg
{
    namespace renderer
    {
        class Texture2D
        {
        public:
            enum class TextureFilterMode
            {
                NEAREST,
                LINEAR,
                NEAREST_MIPMAP_NEAREST,
                LINEAR_MIPMAP_NEAREST,
                NEAREST_MIPMAP_LINEAR,
                LINEAR_MIPMAP_LINEAR
            };

            enum class TextureWrapMode
            {
                REPEAT,
                MIRRORED_REPEAT,
                CLAMP_TO_EDGE,
                CLAMP_TO_BORDER
            };

            enum class TextureFormat
            {
                RGB,
                RGBA
            };

        public:
            Texture2D();
            virtual ~Texture2D();

            void filter_min(TextureFilterMode mode) { m_filter_min = mode; }
            TextureFilterMode filter_min() const { return m_filter_min; }
            void filter_max(TextureFilterMode mode) { m_filter_max = mode; }
            TextureFilterMode filter_max() const { return m_filter_max; }
            void wrap_s(TextureWrapMode mode) { m_wrap_s = mode; }
            TextureWrapMode wrap__s() const { return m_wrap_s; }
            void wrap_t(TextureWrapMode mode) { m_wrap_t = mode; }
            TextureWrapMode wrap_t() const { return m_wrap_t; }
            void internalFormat(TextureFormat f) { m_internalFormat = f; }
            TextureFormat internalFormat() const { return m_internalFormat; }
            void externalFormat(TextureFormat f) { m_externalFormat = f; }
            TextureFormat externalFormat() const { return m_externalFormat; }
            void mipmap(bool enabled) { m_mipmapEnabled = enabled; }
            bool mipmap() const { return m_mipmapEnabled; }
            uint16_t width() const { return m_width; }
            uint16_t height() const { return m_height; }

            void generate(uint16_t w, uint16_t h, uint8_t* data);
            void generate(uint16_t w, uint16_t h, float* data);
            void load(const std::string& file);
            void bind();
        private:
            /**
             * Initialize texture parameters
             */
            void init();
        private:
            GLuint m_glTextureId;
            uint16_t m_width;
            uint16_t m_height;
            TextureFilterMode m_filter_min;
            TextureFilterMode m_filter_max;
            TextureWrapMode m_wrap_s;
            TextureWrapMode m_wrap_t;
            TextureFormat m_internalFormat;
            TextureFormat m_externalFormat;
            bool m_mipmapEnabled;
        };
    }
}
