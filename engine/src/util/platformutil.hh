#ifndef TRIANGL_PLATFORMUTIL_HH
#define TRIANGL_PLATFORMUTIL_HH 1

#include "core/base.hh"

namespace triangl {

	enum class system_theme
	{
		light,
		dark
	};

	class native_platform_util
	{
	public:
		virtual ~native_platform_util() = default;
		
		virtual float get_time() const = 0;
		virtual system_theme get_system_theme() const = 0;
	};

	class platform_util
	{
	public:
		static float get_time()
		{
			return s_inst->get_time();
		}

		static system_theme get_system_theme()
		{
			return s_inst->get_system_theme();
		}
	private:
		static std::unique_ptr<native_platform_util> s_inst;
	};

}

#endif
