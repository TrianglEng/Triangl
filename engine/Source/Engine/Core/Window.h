#pragma once

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include "Event/Event.h"
#include "Event/Signal.h"

namespace Triangl
{
	DECLARE_SIGNAL(WindowClosed);
	DECLARE_SIGNAL(WindowResized, int /*width*/, int /*height*/);
	DECLARE_SIGNAL(WindowFocused);
	DECLARE_SIGNAL(WindowLostFocus);
	DECLARE_SIGNAL(KeyPressed, KeyCode /*keycode*/, bool /*repeat*/);
	DECLARE_SIGNAL(KeyTyped, KeyCode /*keycode*/);
	DECLARE_SIGNAL(KeyReleased, KeyCode /*keycode*/);
	DECLARE_SIGNAL(MouseMoved, float /*xPos*/, float /*yPos*/);
	DECLARE_SIGNAL(MouseScrolled, float /*xOff*/, float /*yOff*/);
	DECLARE_SIGNAL(MouseButtonPressed, MouseCode /*button*/);
	DECLARE_SIGNAL(MouseButtonReleased, MouseCode /*button*/);

	struct WindowProps
	{
		std::string Title;
		int Width, Height;
		bool Fullscreen, Resizable, VSync;

		WindowProps(std::string_view title = "Triangl Window",
					 int width = 1600, int height = 900,
					 bool fullscreen = false,
					 bool resizable  = true,
					 bool vSync		 = true)
			: Title(title), Width(width), Height(height), Fullscreen(fullscreen), Resizable(resizable), VSync(vSync) {}
	};

	class Window
	{
	public:
		typedef std::function<void(Event&)> EventCallbackFn;
	public:
		SigWindowClosed        WindowClosed;
		SigWindowResized       WindowResized;
		SigWindowFocused       WindowFocused;
		SigWindowLostFocus     WindowLostFocus;
		SigKeyPressed          KeyPressed;
		SigKeyTyped            KeyTyped;
		SigKeyReleased         KeyReleased;
		SigMouseMoved          MouseMoved;
		SigMouseScrolled       MouseScrolled;
		SigMouseButtonReleased MouseButtonPressed;
		SigMouseButtonReleased MouseButtonReleased;
	public:
		virtual ~Window() = default;

		virtual bool Init() = 0;
		virtual bool IsOpen() const = 0;
		virtual void Update() = 0;
		virtual bool Destroy() = 0;

		virtual void SetTitle(std::string_view title) = 0;
		virtual void SetSize(int width, int height) = 0;
		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual void SetVSync(bool vSync) = 0;
		virtual void SetEventCallback(const EventCallbackFn& fn) = 0;

		virtual void Iconify() = 0;
		virtual void Maximize() = 0;
		virtual void Focus() = 0;
		virtual void RequestAttention() = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual bool IsFullscreen() const = 0;
		virtual bool IsResizable() const = 0;
		virtual bool IsVSync() const = 0;
		virtual bool IsIconified() const = 0;
		virtual bool IsMaximized() const = 0;
		virtual bool IsFocused() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> New(const WindowProps& props = {});
	};
}
