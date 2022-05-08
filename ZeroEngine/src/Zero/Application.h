#include "Core.h"
namespace Zero
{
	class ZERO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in client.
	Application* CreateApplication();
}


