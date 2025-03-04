workspace "Razel"
	architecture "x64"

	--ָ������������Ŀ�Ĺ������ü������硰���ԡ��͡�������
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	--���λ��	eg: build-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {}

	startproject "Sandbox"

	project "Razel"			--��Ŀ����
		location"Razel"		--��ĿĿ¼
		kind "SharedLib"	--������Ŀ�����ô����Ķ����ƶ�������ͣ��������̨�򴰿�Ӧ�ó��򣬻����̬��
		language "C++"		--����

		--���ñ���Ķ�����Ŀ���ļ���Ŀ��Ŀ¼
		targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

		--���ļ���ӵ���Ŀ��
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}
		
		--ָ���������İ����ļ�����·��
		includedirs
		{
			"%{prj.name}/vendor/spdlog/include"
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
				"RZ_BUILD_DLL;"
			}

			--ָ��������ɺ�Ҫ���е� shell ����
			postbuildcommands
			{
				("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}
		
		filter "configurations:Debug"
			defines "RZ_DEBUG"
			symbols "On"
		
		filter "configurations:Release"
			defines "RZ_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "RZ_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "RZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RZ_DIST"
		optimize "On"








