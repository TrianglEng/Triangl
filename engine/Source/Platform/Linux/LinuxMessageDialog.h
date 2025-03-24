#pragma once

#include "Misc/MessageDialog.h"

namespace Triangl
{
	class LinuxMessageDialog : public MessageDialog
	{
	public:
		LinuxMessageDialog(const DialogSpecification& specification = {});

		virtual DialogResult CreateAndWait() const override;

		virtual void SetSpecification(const DialogSpecification& specification) override;
		virtual void SetCaption(std::string_view caption) override;
		virtual void SetContent(std::string_view content) override;
		virtual void SetButtonset(DialogButtonset buttonset) override;
		virtual void SetIcon(DialogIcon icon) override;
		virtual void SetDefaultButtonIndex(int defaultButtonIndex) override;

		virtual const DialogSpecification& GetSpecification() const override { return m_Specification; }
		virtual const std::string& GetCaption() const override { return m_Specification.Caption; }
		virtual const std::string& GetContent() const override { return m_Specification.Content; }
		virtual DialogButtonset GetButtonset() const override { return m_Specification.Buttonset; }
		virtual DialogIcon GetIcon() const override { return m_Specification.Icon; }
		virtual int GetDefaultButtonIndex() const override { return m_Specification.DefaultButtonIndex; }
	private:
		DialogSpecification m_Specification;
	};
}
