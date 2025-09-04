include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Razel"
	architecture "x86_64"
	startproject "Razel-Editor"
	--指定工作区或项目的构建配置集，例如“调试”和“发布”
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

	--输出位置	eg: build-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	filter "action:vs*"
        buildoptions { "/utf-8" , "/wd4828" }
    filter {}
	externalwarnings "Off"
	--查找并执行另一个脚本文件，也就是查找路径下的premake文件并将内容拷贝到此处(如果之前尚未运行过)
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


