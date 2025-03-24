#pragma once

#include "Core/Base.h"

namespace Triangl
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	};
}
