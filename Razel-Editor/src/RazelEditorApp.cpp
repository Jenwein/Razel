#include <Razel.h>
#include <Razel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Razel {

	class RazelEditor : public Application
	{
	public:
		RazelEditor()
			: Application("Razel Editor")
		{
			PushLayer(new EditorLayer());
		}

		~RazelEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new RazelEditor();
	}

}