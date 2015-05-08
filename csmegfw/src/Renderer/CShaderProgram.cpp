#include "CShaderProgram.h"
#include "CShader.h"
#include "CSmegException.h"

using namespace csmeg::renderer;

namespace {
}

CShaderProgram::CShaderProgram() : m_programId(0), m_isLinked(false)
{
	m_programId = glCreateProgram();
}

CShaderProgram::~CShaderProgram()
{
	if (m_programId != 0) {
		glDeleteProgram(m_programId);
	}
}

bool CShaderProgram::add(std::unique_ptr<CShader> shader)
{
//	shader->compile();
	m_shaders.push_back(std::move(shader));
	return false;
}

void CShaderProgram::link()
{
	glLinkProgram(m_programId);
	GLint linkStatus;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		throw CSmegException("Unable to link shader program");
	}
}
