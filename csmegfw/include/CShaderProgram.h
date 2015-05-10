#ifndef CSHADERPROGRAM_H
#define CSHADERPROGRAM_H

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

namespace csmeg
{
    namespace renderer
    {
        class CShader;

        class CShaderProgram
        {
        public:
            CShaderProgram();
            virtual ~CShaderProgram();

            bool add(std::unique_ptr<CShader> shader);
            void link();
            void use();
            bool isReady() const { return m_isLinked; }

            // Set uniform values in the shader program
            void setUniform(const std::string& variable, float value); // single float
            void setUniform(const std::string& variable, const glm::vec4& vVector); // single vec4

        protected:
        private:
            GLuint m_programId;
            std::vector<std::unique_ptr<CShader>> m_shaders;
            bool m_isLinked;
        };
    } // namespace renderer
} // namespace csmeg

#endif // CSHADERPROGRAM_H
