	project "Razel"			--��Ŀ����
		kind "StaticLib"	--������Ŀ�����ô����Ķ����ƶ�������ͣ��������̨�򴰿�Ӧ�ó��򣬻����̬��
		language "C++"		--����
		cppdialect "C++17"
		staticruntime "on"

		--���ñ���Ķ�����Ŀ���ļ���Ŀ��Ŀ¼
		targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
		objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
		
		pchheader "rzpch.h"					--ָ��Ԥ����ͷ�ļ�����#include ��ʽ
		pchsource "src/rzpch.cpp"		--ָ������ͷ�ļ������ C/C++ Դ�����ļ�

		--���ļ���ӵ���Ŀ��
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
		--ָ���������İ����ļ�����·��
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

		--���ƺ����������õ��ض�����
		filter "system:windows"
			systemversion "latest"

			--���Ԥ����������������ŵ���Ŀ��
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
