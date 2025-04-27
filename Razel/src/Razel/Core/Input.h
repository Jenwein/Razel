#pragma once
#include <glm/glm.hpp>

#include "Razel/Core/KeyCodes.h"
#include "Razel/Core/MouseCodes.h"

namespace Razel
{
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode keycode);
		static bool IsMouseButtonPressed(const MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}