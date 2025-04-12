#include "TrianglPCH.h"
#include "DesktopWindow.h"

#include "Event/AppEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

namespace Triangl
{
	static uint16_t s_WindowCount = 0;

	static void GLFWErrorCallback
	(
		int code,
		const char* msg
	)
	{
		TL_CORE_ERROR("GLFW Error ({}): {}", code, msg);
	}

	DesktopWindow::DesktopWindow(const WindowProps& props)
		: m_Props(props)
	{
	}

	DesktopWindow::~DesktopWindow()
	{
		if (IsOpen())
		{
			Destroy();
		}
	}

	bool DesktopWindow::Init()
	{
		if (IsOpen())
		{
			TL_CORE_WARN("Tried to initialize window but the window is already open, discarding request.");
			return false;
		}

		TL_CORE_INFO("Creating window '{}' ({}x{})", m_Props.Title, m_Props.Width, m_Props.Height);

		if (s_WindowCount == 0)
		{
			TL_CORE_TRACE("First window getting created, initializing GLFW...");
			if (!glfwInit())
			{
				const char* msg{};
				int code = glfwGetError(&msg);

				TL_CORE_ERROR("Failed to initialize GLFW! GLFW Error ({}): {}", code, msg);
				return false;
			}
			TL_CORE_INFO("GLFW initialized successfully.");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		else
		{
			TL_CORE_TRACE("GLFW already initialized, skipping...");
		}

		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		#ifdef TL_TEST_BUILD
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif
			break;
		}
		}
		glfwWindowHint(GLFW_RESIZABLE, m_Props.Resizable);

		auto CleanUp = [this]()
		{
			if (s_WindowCount == 0)
			{
				glfwTerminate();
			}

			if (m_Handle)
			{
				glfwDestroyWindow(m_Handle);
			}
		};

		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		GLFWmonitor* monitor = m_Props.Fullscreen ? primaryMonitor : nullptr;

		m_Handle = glfwCreateWindow(
			m_Props.Width,
			m_Props.Height,
			m_Props.Title.c_str(),
			monitor,
			nullptr
		);
		
		if (!m_Handle)
		{
			TL_CORE_ERROR("Failed to create the GLFW window, glfwCreateWindow returned NULL!");
			CleanUp();
			return false;
		}

		if (!m_Props.Fullscreen)
		{
			const GLFWvidmode* vidmode = glfwGetVideoMode(primaryMonitor);
			glfwSetWindowPos
			(
				m_Handle,
				(vidmode->width / 2) - (m_Props.Width / 2),
				(vidmode->height / 2) - (m_Props.Height / 2)
			);
		}

		m_Context = GraphicsContext::New(m_Handle);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Handle, this);
		SetVSync(m_Props.VSync); // set flag

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);
			
			WindowClosedEvent e;
			wnd->PropagateEvent(e);

			wnd->WindowClosed.Send();
		});
		
		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);
			
			wnd->m_Props.Width = width;
			wnd->m_Props.Height = height;

			WindowResizedEvent e(width, height);
			wnd->PropagateEvent(e);

			wnd->WindowResized.Send(width, height);
		});

		glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow* window, int focused)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);

			if (focused)
			{
				WindowFocusedEvent e;
				wnd->PropagateEvent(e);

				wnd->WindowFocused.Send();
			}
			else
			{
				WindowLostFocusEvent e;
				wnd->PropagateEvent(e);
				
				wnd->WindowLostFocus.Send();
			}
		});
		
		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int keycode, int scancode, int action, int mods)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);

			bool repeat = false;
			switch (action)
			{
			case GLFW_REPEAT:
			{
				repeat = true;
			}
			case GLFW_PRESS:
			{
				KeyPressedEvent e((KeyCode) keycode, repeat);
				wnd->PropagateEvent(e);
				
				wnd->KeyPressed.Send((KeyCode) keycode, repeat);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e((KeyCode) keycode);
				wnd->PropagateEvent(e);
				
				wnd->KeyReleased.Send((KeyCode) keycode);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int keycode)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);

			KeyTypedEvent e((KeyCode) keycode);
			wnd->PropagateEvent(e);

			wnd->KeyTyped.Send((KeyCode) keycode);
		});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float) xPos, (float) yPos);
			wnd->PropagateEvent(e);

			wnd->MouseMoved.Send((float) xPos, (float) yPos);
		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOff, double yOff)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float) xOff, (float) yOff);
			wnd->PropagateEvent(e);

			wnd->MouseScrolled.Send((float) xOff, (float) yOff);
		});
		
		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			DesktopWindow* wnd = (DesktopWindow*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e((MouseCode) button);
				wnd->PropagateEvent(e);

				wnd->MouseButtonPressed.Send((MouseCode) button);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e((MouseCode) button);
				wnd->PropagateEvent(e);

				wnd->MouseButtonReleased.Send((MouseCode) button);
				break;
			}
			}
		});
		
		s_WindowCount++;
		return true;
	}

	bool DesktopWindow::IsOpen() const
	{
		return m_Handle && !glfwWindowShouldClose(m_Handle);
	}

	void DesktopWindow::Update()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	bool DesktopWindow::Destroy()
	{
		if (!IsOpen())
		{
			TL_CORE_WARN("Window got Destroy() called, but already isn't open, ignoring request.");
			return false;
		}

		glfwDestroyWindow(m_Handle);
		m_Handle = nullptr;

		if (--s_WindowCount == 0)
		{
			TL_CORE_TRACE("All windows have been destroyed, terminating GLFW...");
			glfwTerminate();
			TL_CORE_INFO("Terminated glfw.");
		}

		return true;
	}

	void DesktopWindow::SetTitle(std::string_view title)
	{
		m_Props.Title = title;
		glfwSetWindowTitle(m_Handle, title.data());
	}

	void DesktopWindow::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_Handle, width, height);
	}

	void DesktopWindow::SetWidth(int width)
	{
		SetSize(width, m_Props.Height);
	}

	void DesktopWindow::SetHeight(int height)
	{
		SetSize(m_Props.Width, height);
	}

	void DesktopWindow::SetVSync(bool vSync)
	{
		m_Props.VSync = vSync;
		glfwSwapInterval(vSync ? 1 : 0);
	}

	void DesktopWindow::SetEventCallback(const EventCallbackFn& fn)
	{
		m_EventCallback = fn;
	}

	void DesktopWindow::Iconify()
	{
		glfwIconifyWindow(m_Handle);
	}

	void DesktopWindow::Maximize()
	{
		glfwMaximizeWindow(m_Handle);
	}

	void DesktopWindow::Focus()
	{
		glfwFocusWindow(m_Handle);
	}

	void DesktopWindow::RequestAttention()
	{
		glfwRequestWindowAttention(m_Handle);
	}

	bool DesktopWindow::IsIconified() const
	{
		return glfwGetWindowAttrib(m_Handle, GLFW_ICONIFIED);
	}

	bool DesktopWindow::IsMaximized() const
	{
		return glfwGetWindowAttrib(m_Handle, GLFW_MAXIMIZED);
	}

	bool DesktopWindow::IsFocused() const
	{
		return glfwGetWindowAttrib(m_Handle, GLFW_FOCUSED);
	}
}
