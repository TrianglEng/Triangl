#ifndef TRIANGL_MISC_MSGDIALOG_HH
#define TRIANGL_MISC_MSGDIALOG_HH 1

#include <string_view>
#include <string>
#include <memory>

namespace triangl {

	enum class dialog_buttonset
	{
		none                = 0,
		abort_retry_ignore  = 2,
		cancel_try_continue = 6,
		help                = 16384,
		ok                  = 0,
		ok_cancel           = 1,
		retry_cancel        = 5,
		yes_no              = 4,
		yes_no_cancel       = 3
	};

	enum class dialog_icon
	{
		none     = 0,
		question = 32,
		info     = 64,
		warn     = 48,
		error    = 16
	};

	enum class dialog_result
	{
		creation_error = 0,

		ok        = 1,
		cancel    = 2,
		abort     = 3,
		retry     = 4,
		ignore    = 5,
		yes       = 6,
		no        = 7,
		try_again = 10,
		continue_ = 11
	};

	struct dialog_spec
	{
		std::string caption, content;
		dialog_buttonset buttonset = dialog_buttonset::none;
		dialog_icon icon = dialog_icon::none;
		int index_default_button = 0; // between range (inclusive) 0-3
	};

	class message_dialog
	{
	public:
		virtual ~message_dialog() = default;

		virtual dialog_result create_and_wait() const = 0;

		virtual void set_spec(const dialog_spec& spec) = 0;
		virtual void set_caption(std::string_view caption) = 0;
		virtual void set_content(std::string_view content) = 0;
		virtual void set_buttonset(dialog_buttonset buttonset) = 0;
		virtual void set_icon(dialog_icon icon) = 0;
		virtual void set_index_default_button(int index_default_button) = 0;

		virtual const dialog_spec& get_spec() const = 0;
		virtual const std::string& get_caption() const = 0;
		virtual const std::string& get_content() const = 0;
		virtual dialog_buttonset get_buttonset() const = 0;
		virtual dialog_icon get_icon() const = 0;
		virtual int get_index_default_button() const = 0;

		static std::unique_ptr<message_dialog> create(const dialog_spec& spec = {});
	};

}

#endif
