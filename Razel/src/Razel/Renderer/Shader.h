#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Razel
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const  = 0;
		virtual void UnBind()const = 0;

		static Shader* Shader::Create(const std::string vertexSrc, const std::string& fragmentSrc);

	};
}


