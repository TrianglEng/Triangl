#include "TrianglPCH.h"
#include "LinuxMessageDialog.h"

namespace Triangl
{
	LinuxMessageDialog::LinuxMessageDialog(const DialogSpecification& specification)
		: m_Specification(specification)
	{
	}

	DialogResult LinuxMessageDialog::CreateAndWait() const
	{
		// Not yet implemented nor supported for Linux.
		return DialogResult::CreationError;
	}

	void LinuxMessageDialog::SetSpecification(const DialogSpecification& specification)
	{
		m_Specification = specification;
	}

	void LinuxMessageDialog::SetCaption(std::string_view caption)
	{
		m_Specification.Caption = caption;
	}

	void LinuxMessageDialog::SetContent(std::string_view content)
	{
		m_Specification.Content = content;
	}

	void LinuxMessageDialog::SetButtonset(DialogButtonset buttonset)
	{
		m_Specification.Buttonset = buttonset;
	}

	void LinuxMessageDialog::SetIcon(DialogIcon icon)
	{
		m_Specification.Icon = icon;
	}

	void LinuxMessageDialog::SetDefaultButtonIndex(int defaultButtonIndex)
	{
		m_Specification.DefaultButtonIndex = defaultButtonIndex;
	}
}
