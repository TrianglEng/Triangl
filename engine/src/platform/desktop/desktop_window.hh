#ifndef TRIANGL_PLATFORM_DESKTOP_WINDOW_HH
#define TRIANGL_PLATFORM_DESKTOP_WINDOW_HH 1

#include "core/window.hh"
#include "render/context.hh"

struct GLFWwindow;

namespace triangl {

	class desktop_window : public window
	{
	public:
		desktop_window(const window_props& props = {});
		virtual ~desktop_window() override;

		virtual bool init() override;
		virtual bool is_open() const override;
		virtual void update() override;
		virtual bool destroy() override;

		virtual void set_title(std::string_view title) override;
		virtual void set_size(int width, int height) override;
		virtual void set_width(int width) override;
		virtual void set_height(int height) override;
		virtual void set_vsync(bool vsync) override;
		virtual void set_event_callback(event_callback_fn fn) override;

		virtual void iconify() override;
		virtual void maximize() override;
		virtual void focus() override;
		virtual void request_attention() override;

		virtual const std::string& get_title() const override { return m_data.title; }
		virtual int get_width() const override { return m_data.width; }
		virtual int get_height() const override { return m_data.height; }
		virtual bool is_fullscreen() const override { return m_data.fullscreen; }
		virtual bool is_resizable() const override { return m_data.resizable; }
		virtual bool is_vsync() const override { return m_data.vsync; }
		virtual bool is_iconified() const override;
		virtual bool is_maximized() const override;
		virtual bool is_focused() const override;
		virtual void* get_native_window_handle() const override { return m_handle; }
	private:
		struct window_data
		{
			std::string title;
			int width, height;
			bool fullscreen, resizable, vsync;
			event_callback_fn event_callback;


			sig_window_closed         &window_closed;
			sig_window_resized        &window_resized;
			sig_window_focused        &window_focused;
			sig_window_lost_focus     &window_lost_focus;
			sig_key_pressed           &key_pressed;
			sig_key_typed             &key_typed;
			sig_key_released          &key_released;
			sig_mouse_moved           &mouse_moved;
			sig_mouse_scrolled        &mouse_scrolled;
			sig_mouse_button_pressed  &mouse_button_pressed;
			sig_mouse_button_released &mouse_button_released;

			void callback(event& e)
			{
				if (event_callback)
				{
					event_callback(e);
				}
			}
		} m_data;

		std::unique_ptr<graphics_context> m_context;
		GLFWwindow* m_handle = nullptr;
	};

}

#endif
