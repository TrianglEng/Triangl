#include "TrianglPCH.h"
#include "MessageDialog.h"

#include "Misc/BuildInfo.h"

#include "Platform/Windows/WindowsMessageDialog.h"
#include "Platform/Linux/LinuxMessageDialog.h"

namespace Triangl
{
	Scope<MessageDialog> MessageDialog::New(const DialogSpecification& specification)
	{
		return std::make_unique<TL_MAKE_PLATFORM_TYPE(MessageDialog)>(specification);
	}
}
