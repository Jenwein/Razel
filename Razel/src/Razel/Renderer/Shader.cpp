#include "rzpch.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Razel/Renderer/Shader.h"
#include "Razel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Razel
{

	Razel::Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
			case RendererAPI::API::DirectX11: RZ_CORE_ASSERT(false, "RendererAPI::DirectX11 is currently not supported!"); return nullptr;
			default: break;
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;


	}

	Razel::Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name,vertexSrc,fragmentSrc);
			case RendererAPI::API::DirectX11: RZ_CORE_ASSERT(false, "RendererAPI::DirectX11 is currently not supported!"); return nullptr;
			default: break;
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}



	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		RZ_CORE_ASSERT(!Exists(name), "Shader alread exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Razel::Ref<Razel::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Razel::Ref<Razel::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Razel::Ref<Razel::Shader> ShaderLibrary::Get(const std::string& name)
	{
		RZ_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}