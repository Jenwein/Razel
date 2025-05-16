	project "Razel"			--项目名称
		kind "StaticLib"	--设置项目或配置创建的二进制对象的类型，例如控制台或窗口应用程序，或共享或静态库
		language "C++"		--语言
		cppdialect "C++17"
		staticruntime "on"

		--设置编译的二进制目标文件的目标目录
		targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
		objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
		
		pchheader "rzpch.h"					--指定预编译头文件名的#include 形式
		pchsource "src/rzpch.cpp"		--指定控制头文件编译的 C/C++ 源代码文件

		--将文件添加到项目中
		files
		{
			"src/**.h",
			"src/**.cpp",
			"vendor/stb_image/**.h",
			"vendor/stb_image/**.cpp",
			"vendor/glm/glm/**.hpp",
			"vendor/glm/glm/**.inl",
			"vendor/ImGuizmo/ImGuizmo.h",
			"vendor/ImGuizmo/ImGuizmo.cpp"
		}
		
		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE",
			"YAML_CPP_STATIC_DEFINE"
		}
		--指定编译器的包含文件搜索路径
		includedirs
		{
			"src",
			"vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.entt}",
			"%{IncludeDir.yaml_cpp}",
			"%{IncludeDir.ImGuizmo}",

		}

		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"yaml-cpp",
			"opengl32.lib"
		}

		filter "files:vendor/ImGuizmo/**.cpp"
			flags { "NoPCH" }

		--限制后续构建设置到特定环境
		filter "system:windows"
			systemversion "latest"

			--添加预处理器或编译器符号到项目中
			defines
			{

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
