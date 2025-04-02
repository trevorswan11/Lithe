#include <Lithe.h>
#include <Lithe/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Lithe {

	class Lithium : public Application
	{
	public:
		Lithium(ApplicationCommandLineArgs args)
			: Application("Lithium", args)
		{
			PushLayer(new EditorLayer());
		}

		~Lithium()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Lithium(args);
	}

}
