#pragma once

#include "Platform/Desktop/DesktopPlatformUtils.h"

namespace Triangl
{
	class WindowsPlatformUtils : public DesktopPlatformUtils
	{
	public:
		virtual SystemTheme GetSystemTheme() const override;
	};
}
