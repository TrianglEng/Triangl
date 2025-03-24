#pragma once

#include "Core/LayerStack.h"
#include "Core/Window.h"

#include "Event/AppEvent.h"
#include "Misc/CommandLine.h"

namespace Triangl
{
	struct ApplicationSpecification
	{
		std::string Name = "Triangl Application";
		std::string WorkingDir;
		WindowProps MainWindowProps = { Name };
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification, const CommandLine& args);
		virtual ~Application();

		void Run();
		void Quit();
		[[noreturn]] void Exit(int exitcode);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		const CommandLine& GetArgs() const { return m_Args; }

		Window* GetWindow() const { return m_Window.get(); }
		const LayerStack& GetLayerStack() const { return m_LayerStack; }
		bool is_running() const { return m_Running; }

		static Application* Get() { return s_Instance; }
	private:
		void CleanUp();

		void OnEvent(Event& e);
		bool OnWindowClosed(WindowClosedEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
	private:
		ApplicationSpecification m_Specification;
		CommandLine m_Args;

		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		bool m_Running = false;
	private:
		inline static Application* s_Instance = nullptr;
	};

	Application* CreateApplication(const CommandLine& args);
}
