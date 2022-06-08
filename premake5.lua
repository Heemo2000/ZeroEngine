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

IncludeDir = {}
IncludeDir["GLFW"] = "ZeroEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "ZeroEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "ZeroEngine/vendor/imgui"

include "ZeroEngine/vendor/GLFW"
include "ZeroEngine/vendor/GLAD"
include "ZeroEngine/vendor/imgui"

project "ZeroEngine"
	location "ZeroEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "zeropch.h"
	pchsource "ZeroEngine/src/zeropch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZERO_PLATFORM_WINDOWS",
			"ZERO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "ZERO_DEBUG"
			optimize "On"
			buildoptions "/MDd"

		filter "configurations:Release"
			defines "ZERO_RELEASE"
			optimize "On"	
			buildoptions "/MD"

		filter "configurations:Dist"
			defines "ZERO_DIST"
			optimize "On"
			buildoptions "/MD"

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
			buildoptions "/MDd"

		filter "configurations:Release"
			defines "ZERO_RELEASE"
			optimize "On"	
			buildoptions "/MD"

		filter "configurations:Dist"
			defines "ZERO_DIST"
			optimize "On"
			buildoptions "/MD"