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
            void set(const std::string& variable, float val); // single float
            void set(const std::string& variable, const glm::vec3& vec); // single vec3
            void set(const std::string& variable, const glm::vec4& vec); // single vec4
            void set(const std::string& variable, const glm::mat4& mat); // single mat4

        protected:
        private:
            GLuint m_programId;
            std::vector<std::unique_ptr<CShader>> m_shaders;
            bool m_isLinked;
        };
    } // namespace renderer
} // namespace csmeg

#endif // CSHADERPROGRAM_H
