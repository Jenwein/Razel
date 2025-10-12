#include <Razel.h>
#include <Razel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Razel {

	class Razel3DShow : public Application
	{
	public:
		Razel3DShow()
			: Application("Razel3DShow")
		{
			PushLayer(new EditorLayer());
		}

		~Razel3DShow()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Razel3DShow();
	}

}