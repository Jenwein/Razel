	project "Razel-Editor"
		kind "ConsoleApp"
		language"C++"
		cppdialect "C++17"
		staticruntime "off"

		targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
		objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"src/**.h",
			"src/**.cpp"
		}

		includedirs
		{
			"%{wks.location}/Razel/vendor/spdlog/include",
			"%{wks.location}/Razel/src",
			"%{wks.location}/Razel/vendor",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}",
			"%{IncludeDir.ImGuizmo}"

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