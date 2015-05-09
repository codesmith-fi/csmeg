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
            bool isReady() const { return m_isLinked; }
        protected:
        private:
            GLuint m_programId;
            std::vector<std::unique_ptr<CShader>> m_shaders;
            bool m_isLinked;
        };
    } // namespace renderer
} // namespace csmeg

#endif // CSHADERPROGRAM_H
