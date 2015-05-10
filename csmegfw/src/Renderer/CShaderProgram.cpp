#include "CShaderProgram.h"
#include "CShader.h"
#include "CSmegException.h"
#include <memory>

using namespace csmeg::renderer;

namespace
{
    std::string getProgramInfoLog(GLuint programID)
    {
        if(programID) {
            GLsizei logMaxLength;
            GLsizei logLen;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logMaxLength);
            std::unique_ptr<GLchar> bufPtr(new GLchar[logMaxLength]);
            glGetProgramInfoLog(programID, logMaxLength, &logLen, bufPtr.get());
            std::string log(bufPtr.get());
            return log;
        }
        else {
            return std::string("getProgramInfoLog: Defined shader id == 0");
        }
    }

}

CShaderProgram::CShaderProgram() : m_programId(0), m_isLinked(false)
{
    m_programId = glCreateProgram();
    if(!m_programId) {
        throw CSmegException("Unable to create a shader program");
    }
}

CShaderProgram::~CShaderProgram()
{
    if(m_programId != 0) {
        glDeleteProgram(m_programId);
    }
}

bool CShaderProgram::add(std::unique_ptr<CShader> shader)
{
    // Compile the given shader if not already done so
    shader->compile();
    glAttachShader(m_programId, shader->getID());
    m_shaders.push_back(std::move(shader));
    return false;
}

void CShaderProgram::link()
{
    if(!m_isLinked) {
        glLinkProgram(m_programId);
        GLint linkStatus;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
        if(linkStatus != GL_TRUE) {
            std::string l(getProgramInfoLog(m_programId));
            throw CSmegException("Unable to link shader program");
        }
        m_isLinked = true;
    }
}

void CShaderProgram::use()
{
    if(m_isLinked) {
        glUseProgram(m_programId);
    }
    else {
        throw CSmegException("Trying to use unlinked shader program - link() not called");
    }
}

void CShaderProgram::setUniform(const std::string& variable, float value)
{
    GLint loc = glGetUniformLocation(m_programId, variable.c_str());
    if(loc >= 0) {
        glUniform1fv(loc, 1, &value);
    }
    else {
        throw CSmegException(__FILE__ ": Uniform float variable (" + variable + ") does not exist");
    }
}
