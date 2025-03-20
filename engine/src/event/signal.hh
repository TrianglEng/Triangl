#ifndef TRIANGL_EVENT_SIGNAL_HH
#define TRIANGL_EVENT_SIGNAL_HH 1

#include <functional>

namespace triangl {

	template <typename T, typename... U>
	size_t stdf_addr(std::function<T(U...)> f)
	{
		typedef T(fn_type)(U...);
		fn_type** fnp = f.template target<fn_type*>();
		return (size_t) *fnp;
	}

	#define DECLARE_SIGNAL(name, ...) typedef ::triangl::signal<__VA_ARGS__> sig_##name

	template <typename... Params>
	class signal
	{
	public:
		using binding_type = std::function<void(Params...)>;
	public:
		signal() = default;
		signal(const signal&) = default;
		signal& operator=(const signal&) = default;
		
		signal(std::initializer_list<binding_type> bindings)
			: m_bindings(bindings) {}

		void bind(const binding_type& binding)
		{
			m_bindings.push_back(binding);
		}

		void unbind(const binding_type& binding)
		{
			size_t i = find(binding);
			if (i != std::numeric_limits<size_t>::max())
			{
				m_bindings.erase(m_bindings.begin() + i);
			}
		}

		void send(Params... params)
		{
			for (const binding_type& binding : m_bindings)
			{
				binding(params...);
			}
		}

		size_t find(const binding_type& binding) const
		{
			for (size_t i = 0; i < m_bindings.size(); ++i)
			{
				if (stdf_addr(m_bindings[i]) == stdf_addr(binding))
				{
					return i;
				}
			}

			return std::numeric_limits<size_t>::max();
		}

		bool is_bound(const binding_type& binding) const
		{
			return find(binding) != std::numeric_limits<size_t>::max();
		}

		const std::vector<binding_type>& get_bindings() const { return m_bindings; }
	private:
		std::vector<binding_type> m_bindings;
	};

}

#endif
