#include "TrianglPCH.h"
#include "Application.h"

#include "Input/Input.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

#include "Utils/FileUtils.h"
#include "Utils/PlatformUtils.h"

namespace Triangl
{
	Application::Application(const ApplicationSpecification& specification, const CommandLine& args)
		: m_Specification(specification), m_Args(args)
	{
		TL_CORE_ASSERT(!s_Instance, "Another application instance already exists!");
		s_Instance = this;

		Log::Init();
		TL_CORE_INFO("Initialized logging.");

		TL_CORE_INFO("Engine build info:");
		TL_CORE_INFO("  Compiled by Compiler: {} ({})", c_CompilerInfo.Name, c_CompilerInfo.Abbreviation);
		TL_CORE_INFO("  Compilation at Date: {}", __DATE__);
		TL_CORE_INFO("  Compilation at Time: {}", __TIME__);
		TL_CORE_INFO("  Build Configuration: {}", BuildConfigToString(c_BuildCfg));
		TL_CORE_INFO("  System/Platform: {} ({})", PlatformToString(c_Platform), ArchitectureToString(c_Arch));

		if (!specification.WorkingDir.empty())
		{
			std::string requested = FileUtils::Abs(specification.WorkingDir);
			std::string currentwd = FileUtils::GetWorkingDir();

			if (requested != currentwd)
			{
				TL_CORE_TRACE("The application specified a different working directory than the current one:");
				TL_CORE_TRACE("  Current Working Dir: {}", currentwd);
				TL_CORE_TRACE("  Specifeied Working Dir: {}", requested);

				if (FileUtils::SetWorkingDir(requested))
				{
					TL_CORE_INFO("Successfully changed the working directory to the requested one.");
				}
				else
				{
					TL_CORE_WARN("Working directory change error!");

					DialogSpecification spec =
					{
						"Triangl Engine Application - Working Directory Change Error",

						fmt::vformat
						(
						"The application had requested the working directory to be set to one different than the current one. "
						"The application specified the path '{}' to be set as the current directory, but FileUtils::SetWorkingDir returned false, "
						"which means that the working directory couldn't be set.\n\n"
						"This will most likely result in the application not functioning at all, because it probably depends on that specified "
						"working directory to load every resource it needs to. Would you still like to continue executing the application?",
						fmt::make_format_args(requested)),

						DialogButtonset::YesNo,
						DialogIcon::Error
					};

					Scope<MessageDialog> dialog = MessageDialog::New(spec);
					DialogResult result = dialog->CreateAndWait();

					switch (result)
					{
					case DialogResult::Yes:
					{
						break;
					}
					case DialogResult::No:
					{
						Exit(EXIT_FAILURE);
					}
					}
				}
			}
			else
			{
				TL_CORE_TRACE
				(
					"The application specified the request to change the working dir to '{}' (absolute: '{}'), but the specified path is already the working dir, no effect done.",
					specification.WorkingDir, requested
				);
			}
		}
		else
		{
			TL_CORE_TRACE("The application didn't specify a custom working dir (string is empty), no effect done.");
		}

		m_Window = Window::New(m_Specification.MainWindowProps);
		if (!m_Window || !m_Window->Init())
		{
			TL_CORE_FATAL("Main application window creation failure!");
		}
		m_Window->SetEventCallback(TL_BIND_METHOD(this, Application::OnEvent));

		Input::Init();
		TL_CORE_INFO("Initialized main window Input object.");

		Renderer::Init();
		TL_CORE_INFO("Initialized the Renderer (using API -> {}).", GraphicsAPIToString(RendererAPI::GetAPI()));
	}

	Application::~Application()
	{
		if (this == s_Instance)
		{
			s_Instance = nullptr;
		}
	}

	void Application::Run()
	{
		if (m_Running)
		{
			TL_CORE_WARN("Application::Run() was called, but the application is already running, discarding call...");
			return;
		}

		m_Running = true;
		while (m_Running)
		{
			float time = PlatformUtils::GetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(ts);
			}

			for (Layer* layer : m_LayerStack)
			{
				layer->OnRender();
			}

			m_Window->Update();
		}

		CleanUp();
	}

	void Application::CleanUp()
	{
		m_LayerStack.PopAll();

		if (m_Window->IsOpen())
		{
			m_Window->Destroy();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(TL_BIND_METHOD(this, Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(TL_BIND_METHOD(this, Application::OnWindowResized));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
			{
				break;
			}

			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		TL_CORE_TRACE("Application instance received window closed event, sending quit request...");

		Quit();
		return true; // event handled
	}

	bool Application::OnWindowResized(WindowResizedEvent& e)
	{
		// TODO: report to renderer
		return false; // event not handled
	}

	void Application::Quit()
	{
		if (!m_Running)
		{
			TL_CORE_WARN("Application::Quit() was called, but the application isn't running, discarding call...");
			return;
		}

		m_Running = false;
		TL_CORE_WARN("Application::Quit() was called, m_Running is now set to false and the application will quit the next frame with proper cleaning-up.");
	}

	void Application::Exit(int exitcode)
	{
		std::exit(exitcode);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
	}
}
