#pragma once

#include "Misc/PointerTypes.h"

#include <string_view>
#include <string>

namespace Triangl
{
	enum class DialogButtonset
	{
		None              = 0,
		AbortRetryIgnore  = 2,
		CancelTryContinue = 6,
		Help              = 16384,
		Ok                = 0,
		OkCancel          = 1,
		RetryCancel       = 5,
		YesNo             = 4,
		YesNoCancel       = 3
	};

	enum class DialogIcon
	{
		None     = 0,
		Question = 32,
		Info     = 64,
		Warn     = 48,
		Error    = 16
	};

	enum class DialogResult
	{
		CreationError = 0,

		Ok       = 1,
		Cancel   = 2,
		Abort    = 3,
		Retry    = 4,
		Ignore   = 5,
		Yes      = 6,
		No       = 7,
		TryAgain = 10,
		Continue = 11
	};

	struct DialogSpecification
	{
		std::string Caption, Content;
		DialogButtonset Buttonset = DialogButtonset::None;
		DialogIcon Icon = DialogIcon::None;
		int DefaultButtonIndex = 0; // Between inclusive range 0-3
	};

	class MessageDialog
	{
	public:
		virtual ~MessageDialog() = default;

		virtual DialogResult CreateAndWait() const = 0;

		virtual void SetSpecification(const DialogSpecification& specification) = 0;
		virtual void SetCaption(std::string_view caption) = 0;
		virtual void SetContent(std::string_view content) = 0;
		virtual void SetButtonset(DialogButtonset buttonset) = 0;
		virtual void SetIcon(DialogIcon icon) = 0;
		virtual void SetDefaultButtonIndex(int defaultButtonIndex) = 0;

		virtual const DialogSpecification& GetSpecification() const = 0;
		virtual const std::string& GetCaption() const = 0;
		virtual const std::string& GetContent() const = 0;
		virtual DialogButtonset GetButtonset() const = 0;
		virtual DialogIcon GetIcon() const = 0;
		virtual int GetDefaultButtonIndex() const = 0;

		static Scope<MessageDialog> New(const DialogSpecification& specification = {});
	};
}
