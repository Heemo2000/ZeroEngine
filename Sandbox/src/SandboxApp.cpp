#include <Zero.h>

class Sandbox : public Zero::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}

/*
int main(int argc, char** argv)
{
	auto app = Zero::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
*/
