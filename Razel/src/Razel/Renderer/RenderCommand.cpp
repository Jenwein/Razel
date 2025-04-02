#include "rzpch.h"
#include "Razel/Renderer/RenderCommand.h"

namespace Razel
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}

