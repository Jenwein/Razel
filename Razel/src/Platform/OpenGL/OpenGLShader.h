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
		OpenGLShader(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc);
		
		~OpenGLShader();

		void Bind()const;
		void UnBind()const;

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		virtual void SetFloat(const std::string& name,const float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

		virtual void SetMat4(const std::string& name,const glm::mat4& value)override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);								// 读取着色器源码
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);	// 预处理着色器
		
		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
	
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};
}

