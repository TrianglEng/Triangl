#include "tlpch.hh"
#include "linux_msgdialog.hh"

namespace triangl {

	linux_message_dialog::linux_message_dialog(const dialog_spec& spec)
		: m_spec(spec)
	{
	}

	dialog_result linux_message_dialog::create_and_wait() const
	{
		// Not yet implemented nor supported for Linux.
		return dialog_result::creation_error;
	}

	void linux_message_dialog::set_spec(const dialog_spec& spec)
	{
		m_spec = spec;
	}

	void linux_message_dialog::set_caption(std::string_view caption)
	{
		m_spec.caption = caption;
	}

	void linux_message_dialog::set_content(std::string_view content)
	{
		m_spec.content = content;
	}

	void linux_message_dialog::set_buttonset(dialog_buttonset buttonset)
	{
		m_spec.buttonset = buttonset;
	}

	void linux_message_dialog::set_icon(dialog_icon icon)
	{
		m_spec.icon = icon;
	}

	void linux_message_dialog::set_index_default_button(int index_default_button)
	{
		m_spec.index_default_button = index_default_button;
	}

}
