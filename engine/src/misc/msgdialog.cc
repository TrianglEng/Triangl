#include "tlpch.hh"
#include "msgdialog.hh"

#include "misc/buildinfo.hh"

#include "platform/windows/windows_msgdialog.hh"
#include "platform/linux/linux_msgdialog.hh"

namespace triangl {

	std::unique_ptr<message_dialog> message_dialog::create(const dialog_spec& spec)
	{
		return std::make_unique<TL_MAKE_PLATFORM_TYPE(message_dialog)>(spec);
	}

}
