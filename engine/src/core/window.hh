#ifndef TRIANGL_CORE_WINDOW_HH
#define TRIANGL_CORE_WINDOW_HH 1

#include "input/keycodes.hh"
#include "input/mousecodes.hh"

#include "event/event.hh"
#include "event/signal.hh"

namespace triangl {

	DECLARE_SIGNAL(window_closed);
	DECLARE_SIGNAL(window_resized, int /*width*/, int /*height*/);
	DECLARE_SIGNAL(window_focused);
	DECLARE_SIGNAL(window_lost_focus);
	DECLARE_SIGNAL(key_pressed, keycode /*key*/, bool /*repeat*/);
	DECLARE_SIGNAL(key_typed, keycode /*key*/);
	DECLARE_SIGNAL(key_released, keycode /*key*/);
	DECLARE_SIGNAL(mouse_moved, float /*xpos*/, float /*ypos*/);
	DECLARE_SIGNAL(mouse_scrolled, float /*xoff*/, float /*yoff*/);
	DECLARE_SIGNAL(mouse_button_pressed, mousecode /*button*/);
	DECLARE_SIGNAL(mouse_button_released, mousecode /*button*/);

	struct window_props
	{
		std::string title;
		int width, height;
		bool fullscreen, resizable, vsync;

		window_props(std::string_view title = "Triangl Window",
					 int width = 1600, int height = 900,
					 bool fullscreen = false,
					 bool resizable  = true,
					 bool vsync		 = true)
			: title(title), width(width), height(height), fullscreen(fullscreen), resizable(resizable), vsync(vsync) {}
	};

	class window
	{
	public:
		typedef std::function<void(event&)> event_callback_fn;
	public:
		sig_window_closed         window_closed;
		sig_window_resized        window_resized;
		sig_window_focused        window_focused;
		sig_window_lost_focus     window_lost_focus;
		sig_key_pressed           key_pressed;
		sig_key_typed             key_typed;
		sig_key_released          key_released;
		sig_mouse_moved           mouse_moved;
		sig_mouse_scrolled        mouse_scrolled;
		sig_mouse_button_pressed  mouse_button_pressed;
		sig_mouse_button_released mouse_button_released;
	public:
		virtual ~window() = default;

		virtual bool init() = 0;
		virtual bool is_open() const = 0;
		virtual void update() = 0;
		virtual bool destroy() = 0;

		virtual void set_title(std::string_view title) = 0;
		virtual void set_size(int width, int height) = 0;
		virtual void set_width(int width) = 0;
		virtual void set_height(int height) = 0;
		virtual void set_vsync(bool vsync) = 0;
		virtual void set_event_callback(event_callback_fn fn) = 0;

		virtual void iconify() = 0;
		virtual void maximize() = 0;
		virtual void focus() = 0;
		virtual void request_attention() = 0;

		virtual const std::string& get_title() const = 0;
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;
		virtual bool is_fullscreen() const = 0;
		virtual bool is_resizable() const = 0;
		virtual bool is_vsync() const = 0;
		virtual bool is_iconified() const = 0;
		virtual bool is_maximized() const = 0;
		virtual bool is_focused() const = 0;
		virtual void* get_native_window_handle() const = 0;

		static std::unique_ptr<window> create(const window_props& props = {});
	};

}

#endif
