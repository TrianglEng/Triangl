#pragma once

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Triangl
{
	class DesktopWindow : public Window
	{
	public:
		DesktopWindow(const WindowProps& props = {});
		virtual ~DesktopWindow() override;

		virtual bool Init() override;
		virtual bool IsOpen() const override;
		virtual void Update() override;
		virtual bool Destroy() override;

		virtual void SetTitle(std::string_view title) override;
		virtual void SetSize(int width, int height) override;
		virtual void SetWidth(int width) override;
		virtual void SetHeight(int height) override;
		virtual void SetVSync(bool vSync) override;
		virtual void SetEventCallback(const EventCallbackFn& fn) override;

		virtual void Iconify() override;
		virtual void Maximize() override;
		virtual void Focus() override;
		virtual void RequestAttention() override;

		virtual const std::string& GetTitle() const override { return m_Props.Title; }
		virtual int GetWidth() const override { return m_Props.Width; }
		virtual int GetHeight() const override { return m_Props.Height; }
		virtual bool IsFullscreen() const override { return m_Props.Fullscreen; }
		virtual bool IsResizable() const override { return m_Props.Resizable; }
		virtual bool IsVSync() const override { return m_Props.VSync; }
		virtual bool IsIconified() const override;
		virtual bool IsMaximized() const override;
		virtual bool IsFocused() const override;
		virtual void* GetNativeWindow() const override { return m_Handle; }
	protected:
		WindowProps m_Props;
		EventCallbackFn m_EventCallback;

		void PropagateEvent(Event& e)
		{
			if (m_EventCallback)
			{
				m_EventCallback(e);
			}
		}

		Scope<GraphicsContext> m_Context;
		GLFWwindow* m_Handle = nullptr;
	};
}
