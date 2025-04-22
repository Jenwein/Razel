#pragma once
#include "Razel/Core/Base.h"
#include "Razel/Core/KeyCodes.h"
#include "Razel/Core/MouseCodes.h"

namespace Razel
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}