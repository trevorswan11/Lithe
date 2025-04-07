-- Lithe dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")
 
IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Lithe/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Lithe/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/Lithe/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Lithe/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Lithe/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Lithe/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Lithe/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Lithe/vendor/entt/include"
IncludeDir["Box2D"] = "%{wks.location}/Lithe/vendor/Box2D/include"
IncludeDir["shaderc"] = "%{wks.location}/Lithe/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Lithe/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["msdfgen"] = "%{wks.location}/Lithe/vendor/msdf-atlas-gen/msdfgen"
IncludeDir["msdf_atlas_gen"] = "%{wks.location}/Lithe/vendor/msdf-atlas-gen/msdf-atlas-gen"
IncludeDir["mono"] = "%{wks.location}/Lithe/vendor/mono/include"
IncludeDir["filewatch"] = "%{wks.location}/Lithe/vendor/filewatch"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/Lithe/vendor/VulkanSDK/Lib"
LibraryDir["mono"] = "%{wks.location}/Lithe/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"
