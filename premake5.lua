workspace "ZeroEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "ZeroEngine"
	location "ZeroEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZERO_PLATFORM_WINDOWS",
			"ZERO_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "ZERO_DEBUG"
			optimize "On"

		filter "configurations:Release"
			defines "ZERO_RELEASE"
			optimize "On"	

		filter "configurations:Dist"
			defines "ZERO_DIST"
			optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ZeroEngine/vendor/spdlog/include",
		"ZeroEngine/src"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZERO_PLATFORM_WINDOWS"
		}

		links
		{
			"ZeroEngine"
		}
		filter "configurations:Debug"
			defines "ZERO_DEBUG"
			optimize "On"

		filter "configurations:Release"
			defines "ZERO_RELEASE"
			optimize "On"	

		filter "configurations:Dist"
			defines "ZERO_DIST"
			optimize "On"