#pragma once

#ifdef ZERO_PLATFORM_WINDOWS
	#ifdef ZERO_BUILD_DLL
		#define ZERO_API __declspec(dllexport)
	#else
		#define ZERO_API __declspec(dllimport)
	#endif
#else
	#error Zero only supports Windows!

#endif

//Left shifted for easy comparing.
#define BIT(x) (1<<x)
