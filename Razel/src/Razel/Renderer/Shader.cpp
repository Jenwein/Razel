#include "rzpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Razel
{
	
	Shader::Shader(const std::string vertexSrc, const std::string& fragmentSrc)
	{
		// 创建一个空顶点着色器
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// 将顶点着色器代码发送给GL
		// 请注意，std::string 的 .c_str 是以 NULL 字符结尾的。
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// 编译顶点着色器
		glCompileShader(vertexShader);


		GLint isCompiled = 0;
		// 获取编译状态信息
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		// 如果编译失败
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			// 获取失败信息
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// 最大长度包含NULL
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// 编译失败则删除该着色器
			glDeleteShader(vertexShader);

			// 显示失败信息
			RZ_CORE_ERROR("{0}", infoLog.data());
			RZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// 创建空片段着色器
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// 将顶点着色器代码发送给GL
		// 请注意，std::string 的 .c_str 是以 NULL 字符结尾的。
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// 编译顶点着色器
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

		// 顶点着色器和片段着色器成功编译
		// 将着色器链接到程序
		// 创建程序.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// 附加着色器到程序上
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// 链接程序
		glLinkProgram(program);

		// 获取程序链接信息
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		// 如果链接失败
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

		// 已经链接在程序中，不再需要着色器，
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

}