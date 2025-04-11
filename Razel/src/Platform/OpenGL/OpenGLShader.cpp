#include "rzpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
namespace Razel
{
	// 根据字符返回着色器类型
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
		RZ_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);	// 从文件中读取着色器代码
		auto shaderSources= PreProcess(source);		// 将着色器的type与source对应
		Compile(shaderSources);						// 编译着色器

		// 原始方法:从文件路径提取着色器名称
		//auto lastSlash = filepath.find_last_of("/\\");
		//lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		//auto lastDot = filepath.rfind(".");
		//auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		//m_Name = filepath.substr(lastSlash, count);

		// C++17:使用std::filesystem进行提取
		std::filesystem::path pathObj(filepath);
		m_Name = pathObj.stem().string();					//返回不带扩展名的文件名
	
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		RZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;	// 顶点着色器和片段着色器源码
		sources[GL_VERTEX_SHADER] = vertexSrc;				// 顶点着色器源码
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;			// 片段着色器源码
		Compile(sources);									// 编译着色器
	}


	OpenGLShader::~OpenGLShader()
	{
		RZ_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		RZ_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);				// 定位到文件末尾
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);				// 重新调整大小以容纳文件,tellg返回当前读取位置
				in.seekg(0, std::ios::beg);			// 定位到文件开头
				in.read(&result[0], size);			// 读取文件到字符串
				in.close();
			}
			else
			{
				RZ_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			RZ_CORE_ASSERT(false, "Could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		RZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);							// 在source中查找typeToken，从0开始

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);				// 从pos开始查找第一个换行符
			RZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");	
			size_t begin = pos + typeTokenLength + 1;					// 从typeToken后开始
			std::string type = source.substr(begin, eol - begin);
			RZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type({0}) specified",type);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);					// 从下一行开始查找typeToken
			shaderSources[ShaderTypeFromString(type)] 
				= source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		RZ_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		RZ_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
		
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDsIndex = 0;
		for (auto& [type,source]:shaderSources)
		{

			// 创建一个空顶点着色器
			GLuint shader = glCreateShader(type);

			// 将顶点着色器代码发送给GL
			// 请注意，std::string 的 .c_str 是以 NULL 字符结尾的。
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// 编译顶点着色器
			glCompileShader(shader);

			GLint isCompiled = 0;
			// 获取编译状态信息
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			// 如果编译失败
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				// 获取失败信息
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// 最大长度包含NULL
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// 编译失败则删除该着色器
				glDeleteShader(shader);

				// 显示失败信息
				RZ_CORE_ERROR("{0}", infoLog.data());
				RZ_CORE_ASSERT(false, "{0} shader compilation failure!",type);
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDsIndex++] = shader;

		}
		m_RendererID = program;
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
			// 已经链接在程序中，不再需要着色器
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}


	void OpenGLShader::Bind() const
	{
		RZ_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		RZ_PROFILE_FUNCTION();

		glUseProgram(0);
	}


	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		RZ_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}
	void OpenGLShader::SetIntArray(const std::string& name, int* value, uint32_t count)
	{
		RZ_PROFILE_FUNCTION();

		UploadUniformIntArray(name, value,count);
	}
	void OpenGLShader::SetFloat(const std::string& name,float value)
	{
		RZ_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		RZ_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		RZ_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		RZ_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);

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