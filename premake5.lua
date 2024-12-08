workspace "PathTracer"
	architecture "x86_64"
	configurations {
		"Debug", "Release"
	}

project "Renderer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir "%{wks.location}/bin/%{cfg.name}"
	objdir    "%{wks.location}/obj/%{cfg.name}"

	files 
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs 
	{
	}

	optimize "speed"

filter "configurations:Debug"
	runtime "debug"
	defines {
		"DEBUG",
	}
	symbols "on"

filter "configurations:Release"
	runtime "release"
	defines {
		"NDEBUG"
	}
