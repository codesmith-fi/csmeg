#include "CShader.h"
#include "CSmegException.h"
#include "CDebug.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace csmeg::renderer;

namespace fs = boost::filesystem;

namespace
{
    static boost::filesystem::path g_shaderPath = "./shaders/";

    std::string getShaderInfoLog(GLuint shaderID)
    {
        if(shaderID) {
            const int buffersize = 256;
            GLchar buf[buffersize];
            GLsizei size;
            glGetShaderInfoLog(shaderID, buffersize - 1, &size, buf);
            return std::string(buf);
        }
        else {
            return std::string("getShaderInfoLog: Defined shader id == 0");
        }
    }

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

CShader::CShader(SHADER_TYPE type, const std::string& shaderFile)
    : m_type(type), m_shader(0), m_compiled(false), m_shaderFile("")
{
    m_shader = glCreateShader(evaluateShaderType(type));
    if(m_shader == 0 || m_shader == GL_INVALID_ENUM) {
        throw CSmegException("Unable to create a shader");
    }

    setFromFile(shaderFile);
}

CShader::~CShader()
{
    if(m_shader) {
        glDeleteShader(m_shader);
    }
}

void CShader::setSource(const std::string& source)
{
    if(!m_shaderFile.length()) {
        m_shaderFile = std::string("Shader source: ") + source;
    }
    const GLchar* shaderSource = const_cast<GLchar*>(source.c_str());
    glShaderSource(m_shader, 1, &shaderSource, nullptr);
}

void CShader::setFromFile(const std::string& shaderFile)
{
    m_shaderFile = shaderFile;
    if(!shaderFile.length()) {
        throw CSmegException("Supplied shader filename is nil");
    }
    fs::path fn(fs::initial_path<fs::path()>());
    fn /= "shaders";
    fn /= shaderFile;
    LOG_INFO() << "CShader::setFromFile : " << fn;
    
    fs::ifstream s(fn, std::ifstream::in);
    std::string line;
    if(s.is_open()) {
        std::stringstream strStream;
        strStream << s.rdbuf();
        setSource(strStream.str());
    }
    else {
        std::string err("Unable to open shader: ");
        err += fn.string();
        throw CSmegException(err);
    }
}

void CShader::compile()
{
    if(!m_compiled) {
        glCompileShader(m_shader);

        //Check vertex shader for errors
        GLint vShaderCompiled = GL_FALSE;
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &vShaderCompiled);
        if(vShaderCompiled != GL_TRUE) {
            std::string log(getShaderInfoLog(m_shader));
            LOG_ERROR() << "While compiling shader: " << m_shaderFile;
            LOG_ERROR() << log;
            throw CSmegException("Unable to compile a shader (" + m_shaderFile + ")" );
        }
        m_compiled = true;
    }
}
