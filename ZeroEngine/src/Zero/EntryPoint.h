#pragma once

#ifdef ZERO_PLATFORM_WINDOWS

extern Zero::Application* Zero::CreateApplication();

int main(int argc, char** argv)
{
	Zero::Log::Init();
	ZERO_CORE_WARN("Initialized log!");
	ZERO_CLIENT_INFO("Hello");
	
	auto app = Zero::CreateApplication();
	app->Run();
	delete app;
	//return 0;
}

#endif // ZERO_PLATFORM_WINDOWS
