#pragma once
#include "Razel/Renderer/Shader.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Razel
{
	class OpenGLShader :public Shader
	{
	public:
		
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind()const;
		void UnBind()const;

		// 上传UniformMat4
		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);								// 读取着色器源码
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);	// 预处理着色器
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);		// 编译着色器

	private:
		uint32_t m_RendererID;
	};
}

