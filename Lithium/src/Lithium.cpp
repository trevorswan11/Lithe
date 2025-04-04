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
			PushLayer(new EditorLayer());
		}

		~Lithium()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Hazelnut";
		spec.CommandLineArgs = args;
		return new Lithium(spec);
	}

}
