#pragma once

#include "Core/Base.h"

namespace Triangl
{
	enum class SystemTheme
	{
		Light,
		Dark
	};

	class NativePlatformUtils
	{
	public:
		virtual ~NativePlatformUtils() = default;
		
		virtual float GetTime() const = 0;
		virtual SystemTheme GetSystemTheme() const = 0;
	};

	class PlatformUtils
	{
	public:
		static float GetTime()
		{
			return s_Instance->GetTime();
		}

		static SystemTheme GetSystemTheme()
		{
			return s_Instance->GetSystemTheme();
		}
	private:
		static Scope<NativePlatformUtils> s_Instance;
	};
}
