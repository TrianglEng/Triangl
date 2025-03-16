#ifndef TRIANGL_PLATFORM_LINUX_MSGDIALOG_HH
#define TRIANGL_PLATFORM_LINUX_MSGDIALOG_HH 1

#include "misc/msgdialog.hh"

namespace triangl {

	class linux_message_dialog : public message_dialog
	{
	public:
		linux_message_dialog(const dialog_spec& spec = {});

		virtual dialog_result create_and_wait() const override;

		virtual void set_spec(const dialog_spec& spec) override;
		virtual void set_caption(std::string_view caption) override;
		virtual void set_content(std::string_view content) override;
		virtual void set_buttonset(dialog_buttonset buttonset) override;
		virtual void set_icon(dialog_icon icon) override;
		virtual void set_index_default_button(int index_default_button) override;

		virtual const dialog_spec& get_spec() const override { return m_spec; }
		virtual const std::string& get_caption() const override { return m_spec.caption; }
		virtual const std::string& get_content() const override { return m_spec.content; }
		virtual dialog_buttonset get_buttonset() const override { return m_spec.buttonset; }
		virtual dialog_icon get_icon() const override { return m_spec.icon; }
		virtual int get_index_default_button() const override { return m_spec.index_default_button; }
	private:
		dialog_spec m_spec;
	};

}

#endif
