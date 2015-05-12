#pragma once

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <memory>

namespace csmeg
{
    namespace renderer
    {
        class CShaderProgram;

        class CQuadRenderer        
        {
        private: 
            enum QuadRendererConstants
            {
                QR_VBO_VERTEXPOS = 0,
                QR_VBO_TEXCOORD = 1,
                QR_VBO_COUNT = 2
            };

        public:
            CQuadRenderer(CShaderProgram& shader);
            virtual ~CQuadRenderer();

            void init();
            void render(const glm::vec2& pos, const glm::vec2& size, float rot, const glm::vec3& color);
        private:
            CShaderProgram& m_shader;
            GLuint m_vao;
            GLuint m_vbo[QR_VBO_COUNT];
        };
    }
}

