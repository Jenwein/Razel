	project "Razel3DShow"
		kind "ConsoleApp"
		language"C++"
		cppdialect "C++17"
		staticruntime "on"

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
			"%{IncludeDir.ImGuizmo}",
			"%{IncludeDir.assimp}"

		}

		links
		{
			"Razel"
		}

		filter "system:windows"
			systemversion "latest"

			postbuildcommands
			{
				("{COPY} \"%{wks.location}/Razel/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll\" \"%{cfg.targetdir}\""),
				("{COPY} \"%{wks.location}/Razel/vendor/assimp/bin/Release/assimp-vc143-mt.dll\" \"%{cfg.targetdir}\"")
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