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
				enum class SHADER_TYPE {
					Vertex,
					Fragment,
					Geometry,
					TesselationControl,
					TesselationEvaluation
				};
		
			public:
                CShader(SHADER_TYPE type);
                virtual ~CShader();

            public: // New methods
                void setSource(const std::string& sourceCode);
                void setFromFile(const std::string& fileName);
                void compile();
				bool isCompiled() { return m_compiled; }

            protected:
				CShader() {};
            private:
                SHADER_TYPE m_type;
                GLuint m_shader;
				bool m_compiled;
        };
    } // namespace renderer
} // namespace csmeg

#endif // CSHADER_H
