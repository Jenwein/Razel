#include "rzpch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>
namespace Razel
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);	// TODO:
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);

	}
	
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset /*= 0*/)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

}


