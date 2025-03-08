#pragma once

// For use by Lithe applications

#include "Lithe/Core/Application.h"
#include "Lithe/Core/Layer.h"
#include "Lithe/Core/Log.h"

#include "Lithe/Core/Timestep.h"

// You need to change keycodes if NOT using glfw
#include "Lithe/Core/Input.h"
#include "Lithe/Core/MouseButtonCodes.h"
#include "Lithe/Core/KeyCodes.h"

#include "Lithe/ImGui/ImGuiLayer.h"

// ---Rendering---
#include "Lithe/Renderer/Renderer.h"
#include "Lithe/Renderer/RenderCommand.h"

#include "Lithe/Renderer/Shader.h"
#include "Lithe/Renderer/Texture.h"
#include "Lithe/Renderer/Buffer.h"
#include "Lithe/Renderer/VertexArray.h"

#include "Lithe/Renderer/OrthographicCamera.h"
#include "Lithe/Renderer/OrthographicCameraController.h"
// -----------------

// ---Entry Point---
#include "Lithe/Core/EntryPoint.h"
// -----------------