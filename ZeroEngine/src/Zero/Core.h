#pragma once
#include<memory>

#ifdef ZERO_PLATFORM_WINDOWS
	#define ZERO_API
	
#else
	#error Zero only supports Windows!

#endif

#ifdef ZERO_DEBUG
	#define ZERO_ENABLE_ASSERTS
#endif


#ifdef ZERO_ENABLE_ASSERTS
	#define ZERO_ASSERT(x,...) { if(!(x)) { ZERO_CLIENT_ERROR("Assertion failed : {0}",__VA_ARGS__); __debugbreak();}}
	#define ZERO_CORE_ASSERT(x,...) { if(!(x)) { ZERO_CORE_ERROR("Assertion failed : {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define ZERO_ASSERT(x,...)
	#define ZERO_CORE_ASSERT(x,...)
#endif

//Left shifted for easy comparing.
#define BIT(x) (1<<x)

#define ZERO_BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

namespace Zero
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}