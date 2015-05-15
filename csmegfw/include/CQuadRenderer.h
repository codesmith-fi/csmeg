#pragma once

#include <CShaderProgram.h>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <map>
#include <memory>

namespace csmeg
{
    class TRectangle;

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

            void render(Texture2D& texture, const TRectangle& rect, float rot, const glm::vec3& color);
            void render(RenderMethod method, Texture2D& texture, const TRectangle& rect, float rot, const glm::vec3& color);
            void setCurrentRenderMethod(RenderMethod method);

            void initRenderMethod(RenderMethod method, ShaderProgramPtr shaderPtr);

        private:
            // Initializes the quad renderer internal state
            void init();

            CQuadRenderer(const CQuadRenderer&); // not implemented
            CQuadRenderer& operator=(const CQuadRenderer&); // not implemented

        private:
            std::map<RenderMethod, ShaderProgramPtr> m_methods;
            GLuint m_vbo[QR_VBO_COUNT];
            GLuint m_vao;
            ShaderProgramPtr m_currentMethodShader;
            RenderMethod m_currentMethod;
        };
    }
}

