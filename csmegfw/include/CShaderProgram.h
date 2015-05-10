#ifndef CSHADERPROGRAM_H
#define CSHADERPROGRAM_H

#include <GL/glew.h>
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
            void setUniform(const std::string& variable, float value);

        protected:
        private:
            GLuint m_programId;
            std::vector<std::unique_ptr<CShader>> m_shaders;
            bool m_isLinked;
        };
    } // namespace renderer
} // namespace csmeg

#endif // CSHADERPROGRAM_H
