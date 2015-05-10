#ifndef CSHADER_H
#define CSHADER_H

#include <GL/glew.h>
#include <string>

namespace csmeg
{
    namespace renderer
    {
        class CShader
        {
        public: // enums
            enum class SHADER_TYPE
            {
                Vertex,
                Fragment,
                Geometry,
                TesselationControl,
                TesselationEvaluation
            };

        public:
            CShader(SHADER_TYPE type, const std::string& shaderFile);
            virtual ~CShader();

        public: // New methods
            void setSource(const std::string& sourceCode);
            void setFromFile(const std::string& shaderFile);
            void compile();
            bool isCompiled() { return m_compiled; }
            GLuint getID() const { return m_shader; }
        protected:
            CShader() {};
        private:
            SHADER_TYPE m_type;
            GLuint m_shader;
            bool m_compiled;
            std::string m_shaderFile;
        };
    } // namespace renderer
} // namespace csmeg

#endif // CSHADER_H
