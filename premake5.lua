workspace "Razel"
	architecture "x64"
	startproject "Sandbox"
	--指定工作区或项目的构建配置集，例如“调试”和“发布”
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	--输出位置	eg: build-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Razel/vendor/GLFW/include"
	IncludeDir["Glad"] = "Razel/vendor/Glad/include"
	IncludeDir["ImGui"] = "Razel/vendor/imgui"
	IncludeDir["glm"] = "Razel/vendor/glm"
	IncludeDir["stb_image"] = "Razel/vendor/stb_image"

	filter "action:vs*"
        buildoptions { "/utf-8" , "/wd4828" }
    filter {}
	externalwarnings "Off"
	--查找并执行另一个脚本文件，也就是查找路径下的premake文件并将内容拷贝到此处(如果之前尚未运行过)
group "Dependencies"
	include "Razel/vendor/GLFW"
	include "Razel/vendor/Glad"
	include "Razel/vendor/imgui"

group ""

	project "Razel"			--项目名称
		location"Razel"		--项目目录
		kind "StaticLib"	--设置项目或配置创建的二进制对象的类型，例如控制台或窗口应用程序，或共享或静态库
		language "C++"		--语言
		cppdialect "C++17"
		staticruntime "on"

		--设置编译的二进制目标文件的目标目录
		targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

		
		pchheader "rzpch.h"					--指定预编译头文件名的#include 形式
		pchsource "Razel/src/rzpch.cpp"		--指定控制头文件编译的 C/C++ 源代码文件

		--将文件添加到项目中
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb_image/**.h",
			"%{prj.name}/vendor/stb_image/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
		}
		
		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}
		--指定编译器的包含文件搜索路径
		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"

		}

		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		--限制后续构建设置到特定环境
		filter "system:windows"
			systemversion "latest"

			--添加预处理器或编译器符号到项目中
			defines
			{
				"RZ_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}
		
		filter "configurations:Debug"
			defines "RZ_DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "RZ_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "RZ_DIST"
			runtime "Release"
			optimize "on"


	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language"C++"
		cppdialect "C++17"
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
			"Razel/vendor/spdlog/include",
			"Razel/src",
			"Razel/vendor",
			"%{IncludeDir.glm}"

		}

		links
		{
			"Razel"
		}

		filter "system:windows"
			systemversion "latest"

		filter "configurations:Debug"
			defines "RZ_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "RZ_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "RZ_DIST"
			runtime "Release"
			optimize "on"