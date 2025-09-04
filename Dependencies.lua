
-- Razel Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Razel/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Razel/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/Razel/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Razel/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Razel/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Razel/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Razel/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Razel/vendor/entt/include"
IncludeDir["Box2D"] = "%{wks.location}/Razel/vendor/Box2D/include"
IncludeDir["shaderc"] = "%{wks.location}/Razel/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Razel/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
