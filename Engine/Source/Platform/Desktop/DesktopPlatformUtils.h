#pragma once

#include "Utils/PlatformUtils.h"

namespace Triangl
{
	class DesktopPlatformUtils : public NativePlatformUtils
	{
	public:
		virtual float GetTime() const override;
	};
}
