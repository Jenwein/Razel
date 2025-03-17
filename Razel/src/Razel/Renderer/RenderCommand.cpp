#include "rzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Razel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

