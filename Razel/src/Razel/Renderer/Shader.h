#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Razel
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const  = 0;
		virtual void UnBind()const = 0;

		virtual const std::string& GetName()const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc);

	};
	
	// 管理存储Shader
	class ShaderLibrary
	{
	public:
		// 添加着色器
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		// 从文件加载shader
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		// 按名称检索shader
		Ref<Shader> Get(const std::string& name);

		bool Exist(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>>m_Shader;
	};
}





