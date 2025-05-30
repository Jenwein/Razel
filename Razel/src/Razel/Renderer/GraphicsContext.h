#pragma once

namespace Razel
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual ~GraphicsContext() = default;
		static Scope<GraphicsContext> Create(void* window);
	};

}