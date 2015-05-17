#pragma once

#include <CShaderProgram.h>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <memory>

namespace csmeg
{
    class TRectangle;
    class Color;

    namespace renderer
    {
        class Texture2D;

        class CQuadRenderer        
        {
        public:
            // Predefined render methods, defines a shader for rendering
            enum class RenderMethod : uint8_t
            {
                FLATCOLOR = 0,
                TEXTURED,
                NOT_SET
            };

        private: 
            enum QuadRendererConstants
            {
                QR_VBO_VERTEXPOS = 0,
                QR_VBO_TEXCOORD = 1,
                QR_VBO_COUNT = 2
            };

        public:
            CQuadRenderer();
            virtual ~CQuadRenderer();

            void render(Texture2D& texture, const TRectangle& rect, float rot, const Color& color);
            void render(const TRectangle& rect, float rot, const Color& color);
            void render(Texture2D* texture, const TRectangle& rect, float rot, const Color& color, RenderMethod method = RenderMethod::FLATCOLOR);

            void setShaderProgram(ShaderProgramPtr shaderPtr);

            void setProjection(const glm::mat4& projection); // Projection matrix
            void setView(const glm::mat4& view); // view matrix

        private:
            // Initializes the quad renderer internal state
            void init();
            void setTexture(Texture2D* texture);

            CQuadRenderer(const CQuadRenderer&); // not implemented
            CQuadRenderer& operator=(const CQuadRenderer&); // not implemented

        private:
            GLuint m_vbo[QR_VBO_COUNT];
            GLuint m_vao;
            ShaderProgramPtr m_shaderProgram;
            glm::mat4 m_viewMatrix;
            glm::mat4 m_projectionMatrix;
            uint32_t m_boundTextureId;
        };
    }
}

