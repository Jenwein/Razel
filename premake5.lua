include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Razel"
	architecture "x86_64"
	startproject "Razel-Editor"
	--ָ������������Ŀ�Ĺ������ü������硰���ԡ��͡�������
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	--���λ��	eg: build-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "%{wks.location}/Razel/vendor/GLFW/include"
	IncludeDir["Glad"] = "%{wks.location}/Razel/vendor/Glad/include"
	IncludeDir["ImGui"] = "%{wks.location}/Razel/vendor/imgui"
	IncludeDir["glm"] = "%{wks.location}/Razel/vendor/glm"
	IncludeDir["stb_image"] = "%{wks.location}/Razel/vendor/stb_image"
	IncludeDir["entt"] = "%{wks.location}/Razel/vendor/entt/include"
	IncludeDir["yaml_cpp"] = "%{wks.location}/Razel/vendor/yaml-cpp/include"
	IncludeDir["ImGuizmo"] = "%{wks.location}/Razel/vendor/ImGuizmo"
	IncludeDir["Box2D"] = "%{wks.location}/Razel/vendor/Box2D/include"
	filter "action:vs*"
        buildoptions { "/utf-8" , "/wd4828" }
    filter {}
	externalwarnings "Off"
	--���Ҳ�ִ����һ���ű��ļ���Ҳ���ǲ���·���µ�premake�ļ��������ݿ������˴�(���֮ǰ��δ���й�)
group "Dependencies"
	include "vendor/premake"
	include "Razel/vendor/Box2D"
	include "Razel/vendor/GLFW"
	include "Razel/vendor/Glad"
	include "Razel/vendor/imgui"
	include "Razel/vendor/yaml-cpp"

group ""

include "Razel"
include "Sandbox"
include "Razel-Editor"


