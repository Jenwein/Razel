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

	--���λ��	eg: build-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Razel/vendor/GLFW/include"
	IncludeDir["Glad"] = "Razel/vendor/Glad/include"
	IncludeDir["ImGui"] = "Razel/vendor/imgui"


	filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {}
	
	--���Ҳ�ִ����һ���ű��ļ���Ҳ���ǲ���·���µ�premake�ļ��������ݿ������˴�(���֮ǰ��δ���й�)
	include "Razel/vendor/GLFW"
	include "Razel/vendor/Glad"
	include "Razel/vendor/imgui"

	project "Razel"			--��Ŀ����
		location"Razel"		--��ĿĿ¼
		kind "SharedLib"	--������Ŀ�����ô����Ķ����ƶ�������ͣ��������̨�򴰿�Ӧ�ó��򣬻����̬��
		language "C++"		--����

		--���ñ���Ķ�����Ŀ���ļ���Ŀ��Ŀ¼
		targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

		
		pchheader "rzpch.h"					--ָ��Ԥ����ͷ�ļ�����#include ��ʽ
		pchsource "Razel/src/rzpch.cpp"		--ָ������ͷ�ļ������ C/C++ Դ�����ļ�

		--���ļ���ӵ���Ŀ��
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}
		
		--ָ���������İ����ļ�����·��
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

		--���ƺ����������õ��ض�����
		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"
			--���Ԥ����������������ŵ���Ŀ��
			defines
			{
				"RZ_PLATFORM_WINDOWS;",
				"RZ_BUILD_DLL;",
				"GLFW_INCLUDE_NONE"
			}

			--ָ��������ɺ�Ҫ���е� shell ����
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

