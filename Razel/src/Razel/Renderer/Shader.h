#pragma once

#include <string>
namespace Razel
{
	class Shader
	{
	public:
		Shader(const std::string vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind()const;
		void UnBind()const;

	private:
		uint32_t m_RendererID;
	};
}


