workspace " To-Do_List"
	configurations { "Debug", "Release" } 
	location ("premake")

project "Core"
	kind "StaticLib" 
	language "C++" 
	targetdir "build/%{cfg.buildcfg}" 

	files { "src/core/**.hpp", "src/core/**.cpp" } 
	includedirs { "src/core/**" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On" 
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On" 

project "Dependencies"
	kind "StaticLib"
	language "C++"
	targetdir "build/%{cfg.buildcfg}"

	files { "dependencies/**.hpp", "dependencies/**.cpp" }
	includedirs { "dependencies/**", "dependencies/catch2" }

	filter "configurations:Debug"
		defines { "DEBUG" }  
		symbols "On" 
	filter "configurations:Release"  
		defines { "NDEBUG" }    
		optimize "On" 

project "Headless"
	kind "ConsoleApp"
	language "C++" 
	targetdir "build/%{cfg.buildcfg}" 

	files { "src/headless/**.hpp", "src/headless/**.cpp" } 
	includedirs { "src/headless/**" }

	links { "Core" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On" 
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On" 

project "Graphical"
	kind "WindowedApp"
	language "C++" 
	targetdir "build/%{cfg.buildcfg}" 

	files { "src/ui/**.hpp", "src/ui/**.cpp" } 
	includedirs { "src/ui/**" }

	links { "Core", "Dependencies" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On" 
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On" 

project "Tests"
	kind "ConsoleApp"
	language "C++" 
	targetdir "build/%{cfg.buildcfg}" 

	files { "tests/**.hpp", "tests/**.cpp" } 
	includedirs { "tests/**" }

	links { "Core", "Dependencies" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On" 
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On" 