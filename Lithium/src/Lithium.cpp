#include <Lithe.h>
#include <Lithe/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Lithe {

	class Lithium : public Application
	{
	public:
		Lithium(ApplicationSpecification appSpec)
			: Application(appSpec)
		{
#ifndef LI_DEBUG
			Application::Get().GetWindow().SetVSync(false);
#endif
			PushLayer(new EditorLayer());
		}

		~Lithium()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Lithium";
		spec.CommandLineArgs = args;
		return new Lithium(spec);
	}

}
