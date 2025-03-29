#include <Lithe.h>
#include <Lithe/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Lithe {

	class Lithium : public Application
	{
	public:
		Lithium()
			: Application("Lithium")
		{
			PushLayer(new EditorLayer());
		}

		~Lithium()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Lithium();
	}

}
