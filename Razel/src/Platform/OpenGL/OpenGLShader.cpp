#include "rzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Razel
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;

		RZ_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources= PreProcess(source);
		Compile(shaderSources);
	}


	OpenGLShader::OpenGLShader(const std::string vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;	// ������ɫ����Ƭ����ɫ��Դ��
		sources[GL_VERTEX_SHADER] = vertexSrc;				// ������ɫ��Դ��
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;			// Ƭ����ɫ��Դ��
		Compile(sources);						// ������ɫ��
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);			// ��λ���ļ�ĩβ
			result.resize(in.tellg());				// ���µ�����С�������ļ�
			in.seekg(0, std::ios::beg);			// ��λ���ļ���ͷ
			in.read(&result[0], result.size());	// ��ȡ�ļ����ַ���
			in.close();
		}
		else
		{
			RZ_CORE_ASSERT(false, "Could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);	// ��source�в���typeToken����0��ʼ

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);	// ��pos��ʼ���ҵ�һ�����з�
			RZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");	
			size_t begin = pos + typeTokenLength + 1;					// ��typeToken��ʼ
			std::string type = source.substr(begin, eol - begin);
			RZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);		// ����һ�п�ʼ����typeToken
			shaderSources[ShaderTypeFromString(type)] 
				= source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{

		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSources.size());

		for (auto& [type,source]:shaderSources)
		{

			// ����һ���ն�����ɫ��
			GLuint shader = glCreateShader(type);

			// ��������ɫ�����뷢�͸�GL
			// ��ע�⣬std::string �� .c_str ���� NULL �ַ���β�ġ�
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// ���붥����ɫ��
			glCompileShader(shader);

			GLint isCompiled = 0;
			// ��ȡ����״̬��Ϣ
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			// �������ʧ��
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				// ��ȡʧ����Ϣ
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// ��󳤶Ȱ���NULL
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// ����ʧ����ɾ������ɫ��
				glDeleteShader(shader);

				// ��ʾʧ����Ϣ
				RZ_CORE_ERROR("{0}", infoLog.data());
				RZ_CORE_ASSERT(false, "{0} shader compilation failure!",type);
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);

		}
		m_RendererID = program;
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
			for (auto& id:glShaderIDs)
			{
				glDeleteShader(id);
			}

			RZ_CORE_ERROR("{0}", infoLog.data());
			RZ_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id:glShaderIDs)
		{
			// �Ѿ������ڳ����У�������Ҫ��ɫ��
			glDetachShader(program, id);
		}

		


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