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

	--输出位置	eg: build-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Razel/vendor/GLFW/include"
	IncludeDir["Glad"] = "Razel/vendor/Glad/include"
	IncludeDir["ImGui"] = "Razel/vendor/imgui"


	filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {}
	
	--查找并执行另一个脚本文件，也就是查找路径下的premake文件并将内容拷贝到此处(如果之前尚未运行过)
	include "Razel/vendor/GLFW"
	include "Razel/vendor/Glad"
	include "Razel/vendor/imgui"

	project "Razel"			--项目名称
		location"Razel"		--项目目录
		kind "SharedLib"	--设置项目或配置创建的二进制对象的类型，例如控制台或窗口应用程序，或共享或静态库
		language "C++"		--语言

		--设置编译的二进制目标文件的目标目录
		targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

		
		pchheader "rzpch.h"					--指定预编译头文件名的#include 形式
		pchsource "Razel/src/rzpch.cpp"		--指定控制头文件编译的 C/C++ 源代码文件

		--将文件添加到项目中
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}
		
		--指定编译器的包含文件搜索路径
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

		--限制后续构建设置到特定环境
		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"
			--添加预处理器或编译器符号到项目中
			defines
			{
				"RZ_PLATFORM_WINDOWS;",
				"RZ_BUILD_DLL;",
				"GLFW_INCLUDE_NONE"
			}

			--指定构建完成后要运行的 shell 命令
			postbuildcommands
			{
				("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}
		
		filter "configurations:Debug"
			defines "RZ_DEBUG"
			buildoptions "/MDd"
			symbols "On"
		
		filter "configurations:Release"
			defines "RZ_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "RZ_DIST"
			buildoptions "/MD"
			optimize "On"


	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language"C++"

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
			"Razel/src"
		}

		links
		{
			"Razel"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"RZ_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "RZ_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "RZ_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "RZ_DIST"
			buildoptions "/MD"
			optimize "On"

