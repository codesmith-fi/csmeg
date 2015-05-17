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

            /**
             * Set uniform values in the shader program
             * Link() must have been done for the program atleast once
             */ 
            void set(const std::string& variable, float val); // single float
            void set(const std::string& variable, int32_t val); // single int
            void set(const std::string& variable, uint32_t val); // single unsigned int
            void set(const std::string& variable, float& values, uint16_t count); // multiple floats
            void set(const std::string& variable, int32_t& values, uint16_t count); // multiple ints
            void set(const std::string& variable, uint32_t& values, uint16_t count); // multiple unsigned ints
            void set(const std::string& variable, const glm::vec3& vec); // single vec3
            void set(const std::string& variable, const glm::vec4& vec); // single vec4
            void set(const std::string& variable, const glm::mat4& mat); // single mat4

        protected:
        private:
            GLuint m_programId;
            std::vector<std::unique_ptr<CShader>> m_shaders;
            bool m_isLinked;
        };

        typedef std::shared_ptr<CShaderProgram> ShaderProgramPtr;
    } // namespace renderer
} // namespace csmeg

#endif // CSHADERPROGRAM_H
