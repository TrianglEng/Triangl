#include "tlpch.hh"
#include "input.hh"

#include "core/application.hh"

#include "platform/windows/windows_input.hh"
#include "platform/linux/linux_input.hh"

namespace triangl {

	std::unique_ptr<native_input> input::s_inst = nullptr;

	std::unique_ptr<native_input> native_input::create(void* native_window_handle)
	{
		return std::make_unique<TL_MAKE_PLATFORM_TYPE(input)>(native_window_handle);
	}

	void input::init()
	{
		s_inst = native_input::create(application::inst()->get_window()->get_native_window_handle());
	}

}
