#include "TrianglPCH.h"
#include "WindowsMessageDialog.h"

namespace Triangl
{
	static inline long GetDefaultButtonIndexFlag(int index)
	{
		switch (index)
		{
		case 1: return 256;
		case 2: return 512;
		case 3: return 1024;
		}

		return 0;
	}

	WindowsMessageDialog::WindowsMessageDialog(const DialogSpecification& specification)
		: m_Specification(specification)
	{
	}

	DialogResult WindowsMessageDialog::CreateAndWait() const
	{
		return (DialogResult) MessageBoxA
		(
			NULL,
			m_Specification.Content.c_str(),
			m_Specification.Caption.c_str(),
			(UINT)((long) m_Specification.Buttonset | (long) m_Specification.Icon | GetDefaultButtonIndexFlag(m_Specification.DefaultButtonIndex))
		);
	}

	void WindowsMessageDialog::SetSpecification(const DialogSpecification& specification)
	{
		m_Specification = specification;
	}

	void WindowsMessageDialog::SetCaption(std::string_view caption)
	{
		m_Specification.Caption = caption;
	}

	void WindowsMessageDialog::SetContent(std::string_view content)
	{
		m_Specification.Content = content;
	}

	void WindowsMessageDialog::SetButtonset(DialogButtonset buttonset)
	{
		m_Specification.Buttonset = buttonset;
	}

	void WindowsMessageDialog::SetIcon(DialogIcon icon)
	{
		m_Specification.Icon = icon;
	}

	void WindowsMessageDialog::SetDefaultButtonIndex(int defaultButtonIndex)
	{
		m_Specification.DefaultButtonIndex = defaultButtonIndex;
	}
}
