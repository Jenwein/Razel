#include "rzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Razel
{

	OpenGLShader::OpenGLShader(const std::string vertexSrc, const std::string& fragmentSrc)
	{
		// ����һ���ն�����ɫ��
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// ��������ɫ�����뷢�͸�GL
		// ��ע�⣬std::string �� .c_str ���� NULL �ַ���β�ġ�
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// ���붥����ɫ��
		glCompileShader(vertexShader);


		GLint isCompiled = 0;
		// ��ȡ����״̬��Ϣ
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		// �������ʧ��
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			// ��ȡʧ����Ϣ
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// ��󳤶Ȱ���NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// ����ʧ����ɾ������ɫ��
			glDeleteShader(vertexShader);

			// ��ʾʧ����Ϣ
			RZ_CORE_ERROR("{0}", infoLog.data());
			RZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// ������Ƭ����ɫ��
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// ��������ɫ�����뷢�͸�GL
		// ��ע�⣬std::string �� .c_str ���� NULL �ַ���β�ġ�
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// ���붥����ɫ��
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			RZ_CORE_ERROR("{0}", infoLog.data());
			RZ_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// ������ɫ����Ƭ����ɫ���ɹ�����
		// ����ɫ�����ӵ�����
		// ��������.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// ������ɫ����������
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// ���ӳ���
		glLinkProgram(program);

		// ��ȡ����������Ϣ
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		// �������ʧ��
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RZ_CORE_ERROR("{0}", infoLog.data());
			RZ_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// �Ѿ������ڳ����У�������Ҫ��ɫ����
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location,value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location,value.x,value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}