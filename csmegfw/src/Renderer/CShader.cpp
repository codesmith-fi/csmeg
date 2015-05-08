#include "CShader.h"
#include "CSmegException.h"

using namespace csmeg::renderer;

namespace {
    GLuint evaluateShaderType(CShader::SHADER_TYPE type)
    {
        GLuint glType(GL_VERTEX_SHADER);

        switch(type) {
		case CShader::SHADER_TYPE::Fragment:
            {
                glType = GL_FRAGMENT_SHADER;
                break;
            }
		case CShader::SHADER_TYPE::Geometry:
            {
                glType = GL_GEOMETRY_SHADER;
                break;
            }
		case CShader::SHADER_TYPE::TesselationControl:
            {
                glType = GL_TESS_CONTROL_SHADER;
                break;
            }
		case CShader::SHADER_TYPE::TesselationEvaluation:
            {
                glType = GL_TESS_EVALUATION_SHADER;
                break;
            }
		case CShader::SHADER_TYPE::Vertex:
        default:
            {
                glType = GL_VERTEX_SHADER;
                break;
            }
        }
        return glType;
    }
}

CShader::CShader(SHADER_TYPE type) 
	: m_type(type), m_shader(0), m_compiled(false)
{
    m_shader = glCreateShader(evaluateShaderType(type));
    if(m_shader == 0 || m_shader == GL_INVALID_ENUM) {
        throw CSmegException("Unable to create a shader");
    }
}

CShader::~CShader()
{
	if (m_shader) {
		glDeleteShader(m_shader);
	}
}

void CShader::setSource(const std::string& source)
{
	const GLchar* shaderSource = const_cast<GLchar*>(source.c_str());
    glShaderSource( m_shader, 1, &shaderSource, nullptr );
}

void CShader::setFromFile(const std::string& fileName)
{
    throw CSmegException("Not implemented");
}

void CShader::compile()
{
	if (!m_compiled) {
		glCompileShader(m_shader);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv( m_shader, GL_COMPILE_STATUS, &vShaderCompiled );
		if( vShaderCompiled != GL_TRUE ) {
			throw CSmegException("Unable to compile a shader");
		}
		m_compiled = true;
	}
}
