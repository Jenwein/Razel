#include "rzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Razel {
	// 着色器数据类型与OpenGL基本类型映射
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Razel::ShaderDataType::Float:    return GL_FLOAT;
			case Razel::ShaderDataType::Float2:   return GL_FLOAT;
			case Razel::ShaderDataType::Float3:   return GL_FLOAT;
			case Razel::ShaderDataType::Float4:   return GL_FLOAT;
			case Razel::ShaderDataType::Mat3:     return GL_FLOAT;
			case Razel::ShaderDataType::Mat4:     return GL_FLOAT;
			case Razel::ShaderDataType::Int:      return GL_INT;
			case Razel::ShaderDataType::Int2:     return GL_INT;
			case Razel::ShaderDataType::Int3:     return GL_INT;
			case Razel::ShaderDataType::Int4:     return GL_INT;
			case Razel::ShaderDataType::Bool:     return GL_BOOL;
		}

		RZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	// 保存顶点缓冲布局
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	// 设置顶点索引状态
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}