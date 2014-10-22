#include "CShader.h"
#include "CSmegException.h"

using namespace csmeg::renderer;

namespace {
    GLuint evaluateShaderType(SHADER_TYPE type)
    {
        GLuint glType(GL_VERTEX_SHADER);

        switch(type) {
        case SHADER_TYPE::Fragment:
            {
                glType = GL_FRAGMENT_SHADER;
                break;
            }
        case SHADER_TYPE::Geometry:
            {
                glType = GL_GEOMETRY_SHADER;
                break;
            }
        case SHADER_TYPE::TesselationControl:
            {
                glType = GL_TESS_CONTROL_SHADER;
                break;
            }
        case SHADER_TYPE::TesselationEvaluation:
            {
                glType = GL_TESS_EVALUATION_SHADER;
                break;
            }
        case SHADER_TYPE::Vertex:
        default:
            {
                glType = GL_VERTEX_SHADER;
                break;
            }
        }
        return glType;
    }
}

CShader::CShader(SHADER_TYPE type) : m_type(type), m_shader(0)
{
    m_shader = glCreateShader(evaluateShaderType(type));
    if(m_shader == 0 || m_shader == GL_INVALID_ENUM) {
        throw CSmegException("Unable to create a shader");
    }
}

CShader::~CShader()
{
    //dtor
}

void CShader::setSource(const std::string& source)
{
    const GLchar* shaderSources[] =
    {
        source.c_str()
    };

    glShaderSource( m_shader, 1, shaderSources, nullptr );
}

void CShader::setFromFile(const std::string& fileName)
{
    throw CSmegException("Not implemented");
}

void CShader::compile()
{
    glCompileShader(m_shader);

    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv( m_shader, GL_COMPILE_STATUS, &vShaderCompiled );
    if( vShaderCompiled != GL_TRUE ) {
        throw CSmegException("Unable to compile a shader");
    }
}

/*
 void printShaderLog( GLuint shader ) { //Make sure name is shader if( glIsShader( shader ) ) { //Shader log length int infoLogLength = 0; int maxLength = infoLogLength; //Get info string length glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength ); //Allocate string char* infoLog = new char[ maxLength ]; //Get info log glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog ); if( infoLogLength > 0 ) { //Print Log printf( "%s\n", infoLog ); } //Deallocate string delete[] infoLog; } else { printf( "Name %d is not a shader\n", shader ); } }
 */
