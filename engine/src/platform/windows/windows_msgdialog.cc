#include "tlpch.hh"
#include "windows_msgdialog.hh"

namespace triangl {

	static inline long calculate_default_button(int index)
	{
		switch (index)
		{
		case 1: return 256;
		case 2: return 512;
		case 3: return 1024;
		}

		return 0;
	}

	windows_message_dialog::windows_message_dialog(const dialog_spec& spec)
		: m_spec(spec)
	{
	}

	dialog_result windows_message_dialog::create_and_wait() const
	{
		return (dialog_result) MessageBoxA(
			NULL,
			m_spec.content.c_str(),
			m_spec.caption.c_str(),
			(UINT)((long) m_spec.buttonset | (long) m_spec.icon | calculate_default_button(m_spec.index_default_button))
		);
	}

	void windows_message_dialog::set_spec(const dialog_spec& spec)
	{
		m_spec = spec;
	}

	void windows_message_dialog::set_caption(std::string_view caption)
	{
		m_spec.caption = caption;
	}

	void windows_message_dialog::set_content(std::string_view content)
	{
		m_spec.content = content;
	}

	void windows_message_dialog::set_buttonset(dialog_buttonset buttonset)
	{
		m_spec.buttonset = buttonset;
	}

	void windows_message_dialog::set_icon(dialog_icon icon)
	{
		m_spec.icon = icon;
	}

	void windows_message_dialog::set_index_default_button(int index_default_button)
	{
		m_spec.index_default_button = index_default_button;
	}

}
