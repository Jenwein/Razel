workspace "Razel"
	architecture "x64"
	startproject "Sandbox"
	--ָ������������Ŀ�Ĺ������ü������硰���ԡ��͡�������
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

	--���λ��	eg: build-Windows-x64
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
	--���Ҳ�ִ����һ���ű��ļ���Ҳ���ǲ���·���µ�premake�ļ��������ݿ������˴�(���֮ǰ��δ���й�)
group "Dependencies"
	include "Razel/vendor/GLFW"
	include "Razel/vendor/Glad"
	include "Razel/vendor/imgui"

group ""

	project "Razel"			--��Ŀ����
		location"Razel"		--��ĿĿ¼
		kind "StaticLib"	--������Ŀ�����ô����Ķ����ƶ�������ͣ��������̨�򴰿�Ӧ�ó��򣬻����̬��
		language "C++"		--����
		cppdialect "C++17"
		staticruntime "on"

		--���ñ���Ķ�����Ŀ���ļ���Ŀ��Ŀ¼
		targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

		
		pchheader "rzpch.h"					--ָ��Ԥ����ͷ�ļ�����#include ��ʽ
		pchsource "Razel/src/rzpch.cpp"		--ָ������ͷ�ļ������ C/C++ Դ�����ļ�

		--���ļ���ӵ���Ŀ��
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
		--ָ���������İ����ļ�����·��
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

		--���ƺ����������õ��ض�����
		filter "system:windows"
			systemversion "latest"

			--���Ԥ����������������ŵ���Ŀ��
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