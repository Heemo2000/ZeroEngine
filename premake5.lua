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
IncludeDir["GLM"] = "ZeroEngine/vendor/GLM"

include "ZeroEngine/vendor/GLFW"
include "ZeroEngine/vendor/GLAD"
include "ZeroEngine/vendor/imgui"

project "ZeroEngine"
	location "ZeroEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "zeropch.h"
	pchsource "ZeroEngine/src/zeropch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZERO_PLATFORM_WINDOWS",
			"ZERO_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}


		filter "configurations:Debug"
			defines "ZERO_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "ZERO_RELEASE"	
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "ZERO_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

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
		"ZeroEngine/src",
		"%{IncludeDir.GLM}",
		"ZeroEngine/vendor/imgui"
	}
	filter "system:windows"
		--staticruntime "Off"
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
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "ZERO_RELEASE"
			runtime "Release"
			optimize "on"	


		filter "configurations:Dist"
			defines "ZERO_DIST"
			runtime "Release"
			optimize "on"

