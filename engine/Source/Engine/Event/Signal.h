#pragma once

#include <functional>

namespace Triangl
{
	template <typename T, typename... U>
	size_t AddressOfStdFunction(std::function<T(U...)> func)
	{
		typedef T(FuncType)(U...);
		FuncType** KeyEvent = func.template target<FuncType*>();
		return (size_t) *pFunc;
	}

	#define DECLARE_SIGNAL(name, ...) typedef ::Triangl::Signal<__VA_ARGS__> Sig##name

	template <typename... Params>
	class Signal
	{
	public:
		using BindingType = std::function<void(Params...)>;
	public:
		Signal() = default;
		Signal(const Signal&) = default;
		Signal& operator=(const Signal&) = default;
		
		Signal(std::initializer_list<BindingType> bindings)
			: m_Bindings(bindings) {}

		void Bind(const BindingType& binding)
		{
			m_Bindings.push_back(binding);
		}

		void Unbind(const BindingType& binding)
		{
			size_t i = Find(binding);
			if (i != std::numeric_limits<size_t>::max())
			{
				m_Bindings.erase(m_Bindings.begin() + i);
			}
		}

		void Send(Params... params)
		{
			for (const BindingType& binding : m_Bindings)
			{
				binding(params...);
			}
		}

		size_t Find(const BindingType& binding) const
		{
			for (size_t i = 0; i < m_Bindings.size(); ++i)
			{
				if (AddressOfStdFunction(m_Bindings[i]) == AddressOfStdFunction(binding))
				{
					return i;
				}
			}

			return std::numeric_limits<size_t>::max();
		}

		bool IsBound(const BindingType& binding) const
		{
			return Find(binding) != std::numeric_limits<size_t>::max();
		}

		const std::vector<BindingType>& GetBindings() const { return m_Bindings; }
	private:
		std::vector<BindingType> m_Bindings;
	};
}
