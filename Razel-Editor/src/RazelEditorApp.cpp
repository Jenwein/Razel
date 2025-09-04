#include <Razel.h>
#include <Razel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Razel {

	class RazelEditor : public Application
	{
	public:
		RazelEditor(ApplicationCommandLineArgs args)
			: Application("Razel Editor",args)
		{
			PushLayer(new EditorLayer());
		}

		~RazelEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new RazelEditor(args);
	}

}